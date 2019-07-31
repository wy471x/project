 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-04 09:51:40
 ///
 

#include "Thread.h"
#include <iostream>
#include<functional>
using std::cout;
using std::endl;
using std::function;
namespace wd
{
namespace current_thread
{
 __thread int threadnum;
}
struct ThreadData{
    using ThreadCallback = function<void()>;
    ThreadData(const int& num,ThreadCallback&& cb)
    :_num(num)
     ,_cb(std::move(cb))
    {}
    int _num;
    ThreadCallback _cb;
    void runInThread(){
        current_thread::threadnum = _num;
        if(_cb)
            _cb();
    }
};
//子线程创建函数
Thread::Thread(ThreadCallback && cb,const int& num)
: _pthid(0)
, _cb(std::move(cb))
, _isRunning(false)
,_num(num)
{
	cout << "sub Thread()" << endl;
}
//时钟线程创建函数
Thread::Thread(ThreadCallback && cb)
:_pthid(0)
,_cb(std::move(cb))
,_isRunning(false)
{  std::cout<<"TimerThread"<<std::endl; }
void Thread::start()
{
    ThreadData* threadData = new ThreadData(_num,std::move(_cb));
	pthread_create(&_pthid, NULL, threadFunc, threadData);	
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
    ThreadData* threadData = static_cast<ThreadData*>(arg);
	if(threadData)
		threadData->runInThread();

	delete threadData;
    return nullptr;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, NULL);
}

Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);	
	}
	cout << "~Thread()" << endl;
}

}//end of namespace wd
