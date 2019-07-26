#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>
using namespace std;
class Cache
{
public:
    //Cache(int num = 10);
    Cache(const Cache& cache);
    void addElement(const string& key,const string& value);//往缓存中添加数据
    void readFromFile(const string& filename);//从文件中读取缓存信息
    void writeToFile(const string& filename);//将缓存信息写入到文件中
    void update(const Cache& rhs);//更新缓存信息
    ~Cache() {}
private:
   unordered_map<string,string> _hashmap;//hashtable进行缓存
};

