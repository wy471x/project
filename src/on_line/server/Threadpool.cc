 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-06 11:32:31
 ///
 
#include "Threadpool.h"
#include "Thread.h"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd 
{

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _que(_queSize) 
, _isExit(false)
{
	_threads.reserve(_threadNum);
}


void Threadpool::start()
{
	for(size_t idx = 0; idx != _threadNum; ++idx) {
		unique_ptr<Thread> thread(new Thread(
			std::bind(&Threadpool::threadFunc, this)
		));
		_threads.push_back(std::move(thread));
	}

	for(auto & thread : _threads) {
		thread->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit) {
		//先将任务队列中的任务执行完毕
		while(!_que.empty()) {
			::sleep(1);
		}

		_isExit = true;
		cout << ">>> _isExit = true " << endl;

		_que.wakeup();  //任务执行速度过快，每一个线程陷于阻塞态，需要将所有线程唤醒

		for(auto & thread : _threads) {//将线程资源进行回收
			thread->join();
		}
	}
}

void Threadpool::addTask(Task && task)
{
	_que.push(task);
}

Task Threadpool::getTask()
{
	return _que.pop();
}

//每一个子线程运行
void Threadpool::threadFunc()
{
	while(!_isExit) {
		Task task = getTask();
		if(task) {
			task();//任务执行速度过快，在还没将isExit设置为true之前，
			//每一个子线程已经阻塞在了getTask()方法之上
		}
	}
}


}//end of namespace wd
