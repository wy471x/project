#pragma once
#include "../include/cppjieba/Jieba.hpp"
#include<string>
#include<vector>
using namespace std; 

const char* const DICT_PATH = "../data/Cppjieba_dict/jieba.dict.utf8";
const char* const HMM_PATH = "../data/Cppjieba_dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../data/Cppjieba_dict/user.dict.utf8";
const char* const IDF_PATH = "../data/Cppjieba_dict/idf.utf8";
const char* const STOP_PATH = "../data/Cppjieba_dict/stop_words.utf8";

class SplitTool
{
public:
    SplitTool() {}
    virtual  ~SplitTool() {}
    virtual vector<string> cut(const string& sentence) = 0;
};
class SplitToolCppJieba : public SplitTool
{
public:
    SplitToolCppJieba():jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_PATH) {} ;
    ~SplitToolCppJieba(){}
    vector<string> cut(const string &sentence);
private:
   cppjieba::Jieba jieba;
};
