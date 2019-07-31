#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>
#include<vector>
#include<sstream>
#include<utility>
using namespace std;
class Cache
{
public:
    Cache(){};
    //Cache(const Cache& cache);
    void addElement(const string& key,const vector<string>& value);//往缓存中添加数据
    void readFromFile(const string& filename);//从文件中读取缓存信息
    void writeToFile(const string& filename);//将缓存信息写入到文件中
    void update(const Cache& rhs);//更新缓存信息
    unordered_map<string,vector<string>> gethashmap();//获得本cache的缓存内容
    ~Cache() {}
private:
   unordered_map<string,vector<string>> _hashmap;//hashtable进行缓存
};

