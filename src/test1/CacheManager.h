#pragma once
#include"Cache.h"
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class CacheManager
{
public:
     static void initCache(size_t num, const string& filename)//从磁盘读取缓存信息
     {
         ifstream ifs_cachefile(filename);
         size_t i = 0;
         while(i < num){
             _cachelist[i].readFromFile(filename);
             ++i;
         }
     }
     static Cache& getCache(size_t idx)//获取某个缓存
     {
         return _cachelist[idx];
     }
     static void periodicUpdateCaches()//定时更新所有缓存
     {
         for(size_t i = 1;i < _cachelist.size(); ++i){
               _cachelist[0].update(_cachelist[i]);
         }
         for(size_t i = 1;i < _cachelist.size(); ++i){
             _cachelist[i].update(_cachelist[0]);
         }
     }
private:
     static vector<Cache> _cachelist;//缓存的数量与线程个数一致
};

