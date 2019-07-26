#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<set>
#include<fstream>
#include<memory>
#include<sstream>
using namespace std;
//想要多个文件包含，只需要在头文件声明即可，不需要在头文件定义
wstring s2Ws(const string& str);
string ws2S(const wstring& wstr);
class MyDict
{
public:
    static MyDict* createInstance();
    void init(const char* dictEnPath,const char* dictCnPath,const char* indexPath);//通过中文和英文词典文件路径初始化词典
    vector<pair<string,int>>& getDict();//获取词典
    map<string,set<int>>& getIndexTable();//获取索引表
    //void showIndex();//测试索引
private:
    MyDict() {}
    ~MyDict() {}
private:
   vector<pair<string,int>> _dict;//词典
   map<string,set<int>> _index_table;//索引表
   static MyDict* _instance;
};
