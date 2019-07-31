#pragma once
#include"TcpServer.h"
#include"Threadpool.h"
#include"MyTask.h"
#include"MyConf.h"
#include"TimerThread.h"
#include"CacheManager.h"
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<string>
#include<functional>
using namespace std;
using namespace wd;
class SpellcorrectServer
{
public:
    SpellcorrectServer(MyConf& conf,TcpServer& tcpserver,Threadpool& threadpool,CacheManager& cachemanager)
    :_conf(conf)
    ,_tcpserver(tcpserver)
    ,_threadpool(threadpool)
     ,_cachemanager(cachemanager)
    {}//构造函数

    void start();//开始使用
    static void onConnection(const TcpConnectionPtr& conn);//被注册回调函数，提供给TcpServer使用
    static void onMessage(const TcpConnectionPtr& conn);//被注册回调函数，提供给TcpServer使用
    static void onClose(const TcpConnectionPtr& conn);//被注册回调函数，提供给TcpServer使用
    ~SpellcorrectServer() {}

private:
   MyConf& _conf;   //配置文件对象
   TcpServer& _tcpserver;//网络编程对象
   Threadpool& _threadpool;//线程池 
   CacheManager& _cachemanager;//缓存管理器
};

