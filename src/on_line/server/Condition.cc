 ///
 /// @file    Condition.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-04-15 15:06:07
 ///
 
#include "Condition.h"
#include "MutexLock.h"  //在Condtion的实现文件里面加载MutexLock的头文件

#include <stdio.h>
#include <errno.h>

namespace wd
{

Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
	if(pthread_cond_init(&_cond, NULL)) {
		perror("pthread_cond_init");
	}
}

Condition::~Condition()
{
	if(pthread_cond_destroy(&_cond)) {
		perror("pthread_cond_destroy");
	}
}

void Condition::wait()
{
	if(pthread_cond_wait(&_cond, _mutex.getMutexLockPtr())) {
		perror("pthread_cond_wait");
	}
}

void Condition::notify()
{
	if(pthread_cond_signal(&_cond)) {  //激活一个等待该条件的线程，如果有多个线程等待，则按照入队顺序进行激活
		perror("pthread_cond_signal");
	}
}

void Condition::notifyAll()
{
	if(pthread_cond_broadcast(&_cond)) {  //激活所有等待的线程
		perror("pthread_cond_broadcast");
	}
}

}//end of namespace wd
