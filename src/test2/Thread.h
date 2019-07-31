 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-04 09:49:30
 ///
 
#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include "Noncopyable.h"

#include <pthread.h>
#include <functional>

namespace wd
{
namespace current_thread
{
   extern __thread int threadnum;
}//end of namespace current_thread
class Thread
: Noncopyable
{
public:
	using ThreadCallback = std::function<void()>;
	Thread(ThreadCallback && cb,const int& num);
    Thread(ThreadCallback&& cb);
	void start();
	void join();

	~Thread();

private:
	static void * threadFunc(void *);

private:
	pthread_t _pthid;
	ThreadCallback _cb;
	bool _isRunning; 
    int _num;
};

}//end of namespace wd

#endif
