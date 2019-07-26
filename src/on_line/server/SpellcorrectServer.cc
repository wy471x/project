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
    _threadpool.start();
    gThreadpool = & _threadpool;
    _tcpserver.setConnectionCallback(onConnection);
    _tcpserver.setMessageCallback(onMessage);
    _tcpserver.setCloseCallback(onClose);
    _tcpserver.start();
}
