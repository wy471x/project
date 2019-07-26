#include"SplitTool.h"
vector<string> SplitToolCppJieba::cut(const string& sentence){
    vector<string> words;
    jieba.Cut(sentence,words,true);
    return words;
}
