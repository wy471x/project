#pragma once
#include"SplitTool.h"
#include<cstdlib>
#include<memory>
#include<regex>
#include<dirent.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<iostream>
#include<set>
using namespace std;
class DictProducer
{
public:
    DictProducer(const string& dir);//英文处理
    DictProducer(const string& dir,SplitTool* splitTool);//中文处理
    ~DictProducer() {}
    void build_en_dict();//英文词典创建
    void build_cn_dict();//中文词典创建
    void store_dict(const char* filepath);//将词典写入文件
    void show_files()const;//查看文件路径，测试
    void show_dict()const;//查看词典，测试
    void show_stopwords()const;//查看停用词
private:
    void text_deal(const string& file,ifstream& ifs);//文本文件处理
    void get_files();//获取文件路径
    void push_dict(const string& word);//存储某个单词
    void get_stopwords(const string& file);
    string _dir;  //语料库文件路径
   vector<string> _files; //语料库下文件集合
   map<string,int> _dict; //配置文件内容
   set<string> stop_words;
   SplitTool* _splittool;//分词工具
};

