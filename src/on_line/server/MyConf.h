#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
using namespace std;
class MyConf
{
public:
    MyConf(const string& _filepath);
    map<string,string>& getConfigMap();
    ~MyConf() {}
private:
   string _filepath;
   map<string,string> _configMap;
};

