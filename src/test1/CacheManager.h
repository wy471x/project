#pragma once
#include"Cache.h"
#include<ctime>
#include<iostream>
#include<vector>
#include<string>
using namespace std;
class CacheManager
{
public:
    CacheManager(const string& filename,int&& num)
    :_filename(filename)
    ,_num(num)
    {}
      void initCache()//从磁盘读取缓存信息
     {
        // cout<<"cachelist size:"<<_cachelist.size()<<endl;
        // cout<<"cache file : "<<_filename<<endl;
         int i = 0;
         while(i < _num){
            Cache cache;
            cache.readFromFile(_filename);
           // cout<<"init cache "<<i<<" contents :"<<endl;
           //  for(auto& i : cache.gethashmap()){
           //     cout<<i.first<<" :";
           //     for(auto& j : i.second)
           //         cout<<j<<" ";
           //     cout<<endl;
           //  }
             _cachelist.push_back(cache);
             ++i;
         }
       //  for(auto& it : _cachelist){
       //     for(auto& i: it.gethashmap()){
       //         cout<<i.first<<" ";
       //         for(auto& j : i.second) 
       //             cout<<j<<" ";
       //         cout<<endl;
       //     }
       //  }
       //  cout<<"init cachelist size:"<<_cachelist.size()<<endl;
     }
     static Cache& getCache(size_t idx)//获取某个缓存,静态成员函数无法访问类中成员相当于全局函数
     {
         
         return _cachelist[idx];
     }
     void periodicUpdateCaches()//定时更新所有缓存
     {
         time_t nowtime = time(NULL);
         cout<<"CacheManager periodupdate time : "<<nowtime<<endl;
         cout<<"periodupdate all cache"<<endl;
       //  cout<<"cache filename : "<<_filename<<endl;
           for(size_t i = 1;i < _cachelist.size(); ++i){
       //    cout<<"cache "<<i<<" contents :"<<endl;
       //    for(auto& it : _cachelist[i].gethashmap()){
       //        cout<<it.first<<" :";
       //        for(auto& j : it.second)
       //            cout<<j<<" ";
       //        cout<<endl;
       //    }
       //    cout<<endl;
             _cachelist[0].update(_cachelist[i]);
         }
         for(size_t i = 1;i < _cachelist.size(); ++i){
               _cachelist[i].update(_cachelist[0]);
         }
  //       cout<<"after update cache 0 contents :"<<endl;
  //       auto _map = _cachelist[0].gethashmap();
  //       for(auto& i : _map){
  //          cout<<i.first<<" :";
  //          for(auto& j : i.second)
  //              cout<<j<<" ";
  //          cout<<endl;
  //       }
  //       cout<<endl;
         _cachelist[0].writeToFile(_filename);//将零号缓存写入缓存文件作为备份
    }
private:
     static vector<Cache> _cachelist;//缓存的数量与线程个数一致
     string _filename;//cache文件名
     int _num;//缓存个数
};

