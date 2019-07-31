#pragma once
#include<iostream>
#include<unordered_map>
#include<vector>
#include<list>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
class LRUCache
{
    struct CacheNode{
        CacheNode(string k,vector<string> v)
        :key(k)
        ,value(v)
        {}
        string key;
        vector<string> value;
    };
public:
    LRUCache(int capacity) 
    :_capacity(capacity)
    {}
    void put(string key,vector<string> value);//往缓存中放入新的数据
    vector<string> get(string key);//获取缓存中对应查询词的内容
    ~LRUCache() {}
    void readFromfile(const string& filename);//从缓存备份文件读入数据
    void writeTofile(const string& filename);//将缓存信息写入文件
    void update(const LRUCache& rhs);//更新缓存信息
    unordered_map<string,list<CacheNode>::iterator> gethashmap(); 
private:
    int _capacity;//cache容量
    list<CacheNode> _nodes;//cache最新的结点信息
    unordered_map<string,list<CacheNode>::iterator> _keys;//cache的内容
};

