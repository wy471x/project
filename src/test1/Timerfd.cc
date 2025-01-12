 ///
 /// @file    Timerfd.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-19 10:21:40
 ///
 
#include "Timerfd.h"

#include <unistd.h>
#include <poll.h>
#include <sys/timerfd.h>

#include <iostream>
using std::cout;
using std::endl;
 
namespace wd
{

Timerfd::Timerfd(int initialTime, int intervalTime, TimerCallback && cb)
: _fd(createTimerfd())
, _initialTime(initialTime)
, _intervalTime(intervalTime)
, _cb(std::move(cb))
, _isStarted(false)
{}

void Timerfd::start()//时钟开启
{
	_isStarted = true;

	struct pollfd pfd;
	pfd.fd = _fd;
	pfd.events = POLLIN;

	setTimerfd(_initialTime, _intervalTime);

	while(_isStarted) {
		int nready = ::poll(&pfd, 1, 0);//1为数组元素个数，5000为等待时间数	
		if(nready == -1 && errno == EINTR)
			continue;
		else if(nready == -1)
			return;
		else if(nready == 0)//
		/*printf(">> poll timeout!!\n")*/;
		else {//大于0 文件描述符个数 nready = 1
//			cout<<nready<<endl;
            if(pfd.revents & POLLIN) {
				handleRead();
				if(_cb)
					_cb();
			}
		}
	}
}

void Timerfd::stop()//时钟停止
{
	if(_isStarted) {
		_isStarted = false;
		setTimerfd(0, 0);
	}
}

int Timerfd::createTimerfd()//创建时钟
{
	int fd = ::timerfd_create(CLOCK_REALTIME, 0);
	if(fd == -1) {
		perror(">> timerfd_create");
	}
	return fd;
}
	
void Timerfd::setTimerfd(int initialTime, int intervalTime)//设置时钟参数
{
	struct itimerspec value;
	value.it_value.tv_sec = initialTime;//定时器距离定时器刚刚生成时到真正记录超时的时间
	value.it_value.tv_nsec = 1;
	value.it_interval.tv_sec = intervalTime;//间隔时间为超时记录时间
	value.it_interval.tv_nsec = 0;

	int ret = ::timerfd_settime(_fd, 0, &value, nullptr);
	if(ret == -1) {
		perror(">> timerfd_settime");
	}
}


void Timerfd::handleRead()//超时次数
{
	uint64_t howmany;
	int ret = ::read(_fd, &howmany, sizeof(uint64_t));//_fd为 timerfd
//	cout<<ret<<endl;
    if(ret != sizeof(howmany)) {
		perror(">> read");
	}
}
}//end of namespace wd
