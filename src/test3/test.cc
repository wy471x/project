#include"SpellcorrectServer.h"
MyDict* MyDict::_instance = NULL;
void test0(){
    MyConf myconf("/home/dunk/spellCorrect/conf/config");
    map<string,string> configmap = myconf.getConfigMap();
    Threadpool threadpool(stoi(configmap["threadnum"]),stoi(configmap["queuesize"]));
    TcpServer server(configmap["ip"],stoi(configmap["port"]));
    /* CacheManager cachemanager(configmap["cachefile"],stoi(configmap["cachenum"])); */
    CacheManager cachemanager;
    cachemanager.initCache();
    
    SpellcorrectServer spellcorrectserver(myconf,server,threadpool,cachemanager);   
    spellcorrectserver.start();
}
int main()
{
    test0();
    return 0;
}

