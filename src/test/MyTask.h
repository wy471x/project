#pragma once
#include"MyDict.h"
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<queue>
#include<set>
#include<map>
#include<string>
using namespace std;
struct MyResult{
    string _word;//候选词
    int _iFreq;//词频
    int _iDist;//与查询词的最小编辑距离
};

struct MyCompare{
    bool operator()(const MyResult& lhs,const MyResult& rhs)const{
        if(lhs._iDist != rhs._iDist){
            return lhs._iDist > rhs._iDist;
        }else if( lhs._iFreq != rhs._iFreq ){
            return lhs._iFreq < rhs._iFreq;
        }else if(lhs._word != rhs._word)
                  return lhs._word > rhs._word;
    }
};
class MyTask
{
public:
    MyTask(const string& qWord,int peerFd);
    void execute();
    ~MyTask() {}
    //struct MyResult{
    //    string _word;//候选词
    //    int _iFreq;//词频
    //    int _iDist;//与查询词的最小编辑距离
    //};
    void show_resque();
private:
    void queryIndexTable();//查询索引
    void statistic(set<int>& iset);//进行计算
    int distance(const string& rhs);//计算最小编辑距离
    void reponse();//响应客户端请求
    priority_queue<MyResult,vector<MyResult>,MyCompare> _resultQue;
    string _queryWord;
    int _peerFd;
    MyDict& _mydict;
};

