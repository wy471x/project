#include "SpellcorrectServer.h"
//连接回调函数
Threadpool* gThreadpool = NULL;
void SpellcorrectServer::onConnection(const TcpConnectionPtr& conn){
    cout<<conn->toString()<<" has connected!"<<endl;
    Train connectMessage;
    memset(&connectMessage,0,sizeof(Train));
    strcat(connectMessage.buff,"Welcome to SpellcorrectServer!");
    connectMessage.len = strlen(connectMessage.buff);
    conn->send(connectMessage);
}
//消息处理回调函数
void SpellcorrectServer::onMessage(const TcpConnectionPtr& conn){
    cout<<"onMessage..."<<endl;
    string msg = conn->receive();
    cout<<"receive message from client: "<<endl;
    cout<<msg<<endl;
    MyTask task(msg,conn);
    gThreadpool->addTask(bind(&MyTask::execute,task));
}
//关闭回调函数
void SpellcorrectServer::onClose(const TcpConnectionPtr& conn){
    cout<<"onClose..."<<endl;
    cout<<conn->toString()<<" has closed!"<<endl;
}
//业务处理函数
void SpellcorrectServer::start(){
    _threadpool.start();//
    gThreadpool = & _threadpool;
    //_cachemanager.initCache();
    time_t nowtime = time(NULL);
    cout<<"SpellcorrectServer start time : "<<nowtime<<endl;
    TimerThread timer(10,10,std::bind(&CacheManager::periodicUpdateCaches));//静态成员函数可以直接绑定，非静态成员函数需要传入该类对象进去才行
    timer.start();//服务器开启即开始计时
    //第一个参数为计时器刚生成时记录超时记录开始的时间段，
    //第二个参数为每次超记录的间隔时间
    _tcpserver.setConnectionCallback(onConnection);
    _tcpserver.setMessageCallback(onMessage);
    _tcpserver.setCloseCallback(onClose);
    _tcpserver.start();
}
