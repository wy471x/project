#pragma once
#include<iostream>
#include<string>
#include<map>
#include<fstream>
using namespace std;
class Configuration
{
public:
    Configuration(const string& _filepath);
    map<string,string>& getConfigMap();
    ~Configuration() {}

private:
   string _filepath;
   map<string,string> _configMap;
};

