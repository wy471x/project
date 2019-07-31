#pragma once
#include"LRUCache.h"
#include<ctime>
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class CacheManager
{
public:
    /* CacheManager(const string& filename,int&& num) */
    /* :_filename(filename) */
    /* ,_num(num) */
    /* {} */
    CacheManager()
    {}
     static void initCache()//从磁盘读取缓存信息
     {
        cout<<"cachelist size:"<<_cachelist.size()<<endl;
        cout<<"cache file : "<<_filename<<endl;
         int i = 0;
         while(i < _num){
            LRUCache lrucache(10);
            lrucache.readFromfile(_filename);
            cout<<"LRUCache "<<i<<" contents :"<<endl;
            for(auto& i : lrucache.gethashmap()){
                cout<<i.first<<" ";
                istringstream istr(i.second->value);
                string j;
                while(istr>>j){
                  cout<<j<<" ";
                }
                cout<<endl;
            } 
            _cachelist.push_back(lrucache);
            ++i;
         }
     }
     static LRUCache& getCache(size_t idx)//获取某个缓存,静态成员函数无法访问类中成员相当于全局函数
     {
         
         return _cachelist[idx];
     }
     static void periodicUpdateCaches()//定时更新所有缓存
     {
         time_t nowtime = time(NULL);
         cout<<"CacheManager periodupdate time : "<<nowtime<<endl;
         cout<<"periodupdate all cache"<<endl;
       // cout<<"cache filename : "<<_filename<<endl;
        for(size_t i = 1;i < _cachelist.size(); ++i){
       //    cout<<"cache "<<i<<" contents :"<<endl;
       //    for(auto& it : _cachelist[i].gethashmap()){
       //        cout<<it.first<<" ";
       //        for(auto& j : (*it.second).value)
       //            cout<<j<<" ";
       //        cout<<endl;
       //    }
       //    cout<<endl;
             cout<<" updata cache[0]"<<endl; 
            _cachelist[0].update(_cachelist[i]);
         }
         for(size_t i = 1;i < _cachelist.size(); ++i){
             cout<<" updata cache ["<<i<<"]"<<endl;
             _cachelist[i].update(_cachelist[0]);
         }
       // cout<<"after update cache 0 contents :"<<endl;
       // auto _map = _cachelist[0].gethashmap();
       // for(auto& i : _map){
       //    cout<<i.first<<" :";
       //    for(auto& j : i.second->value)
       //        cout<<j<<" ";
       //    cout<<endl;
       // }
        //cout<<endl;
           _cachelist[0].writeTofile(_filename);//将零号缓存写入缓存文件作为备份
    }
private:
     static vector<LRUCache> _cachelist;//缓存的数量与线程个数一致
     static string _filename ;//cache文件名
     static int _num ;//缓存个数
};

