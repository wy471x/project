#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<set>
#include<fstream>
#include<memory>
using namespace std;
class Mydict
{
public:
    static Mydict* createInstance();
    void init(const char* dictEnPath,const char* dictCnPath);//通过中文和英文词典文件路径初始化词典
    vector<pair<string,int>>& getDict();//获取词典
    map<string,set<int>>& getIndexTable();//获取索引表
    void produce_indextable();//生成索引表
    void store_index_file(const string& file);//存储索引表
    void show_dict();
private:
    Mydict() {}
    ~Mydict() {}
private:
   vector<pair<string,int>> _dict;//词典
   map<string,set<int>> _index_table;//索引表
   static Mydict* _instance;
};

