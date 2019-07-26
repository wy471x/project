#include"SpellcorrectServer.h"
MyDict* MyDict::_instance = NULL;
void test0(){
    MyConf myconf("/home/dunk/spellCorrect/conf/config");
    map<string,string> configmap = myconf.getConfigMap();
    Threadpool threadpool(stoi(configmap["threadnum"]),stoi(configmap["queuesize"]));
    TcpServer server(configmap["ip"],stoi(configmap["port"]));
    SpellcorrectServer spellcorrectserver(myconf,server,threadpool);   
    spellcorrectserver.start();
}
int main()
{
    test0();
    return 0;
}

