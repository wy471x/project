#include"Configuration.h"
//获取配置文件
Configuration::Configuration(const string& filepath){
   _filepath = filepath;
}
//获取配置文件中内容
map<string,string>& Configuration::getConfigMap(){
    ifstream ifs(_filepath);
    string str1,str2;
    while(ifs>>str1>>str2){
        _configMap.insert(make_pair(str1,str2));
    }
   return _configMap; 
}
