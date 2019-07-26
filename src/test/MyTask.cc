#include"MyTask.h"
//获取一个字节高位开头为1的个数
size_t nBytesCode(const char ch){
    if(ch & (1 << 7)){
        int nBytes = 1;
        for(int idx = 0; idx != 6;++idx){
            if(ch & (1<<(6 - idx))){
                ++nBytes;
            }else{
                break;
            }
        }
        return nBytes;
    }
    return 1;
}
//长度
size_t length(const string& str){
    size_t ilen = 0;
    for(size_t idx = 0; idx != str.size(); ++idx){
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}
int triple_min(const int& a,const int& b,const int& c){
    return a < b ?(a < c ? a : c) : (b < c ? b : c);
}
int editDistance(const string& lhs,const string& rhs){
   size_t lhs_len = length(lhs);
   size_t rhs_len = length(rhs);
   int editDist[lhs_len + 1][rhs_len + 1];
   for(size_t idx = 0; idx <= lhs_len; ++idx){
       editDist[idx][0] = idx;
   }
   for(size_t idx = 0; idx <= rhs_len;++idx){
       editDist[0][idx] = idx;
   }
   string sublhs,subrhs;
   for(size_t dist_i = 1,lhs_idx = 0;dist_i <= lhs_len;++dist_i,++lhs_idx){
       size_t nBytes = nBytesCode(lhs[lhs_idx]);
       sublhs = lhs.substr(lhs_idx,nBytes);
       lhs_idx += (nBytes - 1);
       for(size_t dist_j = 1,rhs_idx = 0;dist_j <= rhs_len;++dist_j,++rhs_idx){
           nBytes = nBytesCode(rhs[rhs_idx]);
           subrhs = rhs.substr(rhs_idx,nBytes);
           rhs_idx += (nBytes - 1);
           if(sublhs == subrhs){
               editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j - 1];
           }else{
               editDist[dist_i][dist_j] = triple_min(
                    editDist[dist_i][dist_j - 1] + 1,
                    editDist[dist_i - 1][dist_j] + 1,
                    editDist[dist_i - 1][dist_j - 1] + 1);
           }
       }
   }
   return editDist[lhs_len][rhs_len];
}
MyTask::MyTask(const string& qWord,int peerFd):_mydict(*MyDict::createInstance()){
    _queryWord = qWord;
    _peerFd = peerFd;
    _mydict.init("/home/dunk/spellCorrect/data/Dict/dict_en","/home/dunk/spellCorrect/data/Dict/dict_cn","/home/dunk/spellCorrect/data/Index/index");
}
//执行查询
void MyTask::execute(){
   queryIndexTable();
}
//进行计算
void MyTask::statistic(set<int>& iset){
    MyResult res;
    for(auto it = iset.begin(); it != iset.end(); ++it){
        res._word = _mydict.getDict()[(*it) - 1].first;
        res._iFreq = _mydict.getDict()[(*it) - 1].second;
        res._iDist = distance(_mydict.getDict()[(*it) - 1].first);
        _resultQue.push(res);
    }
}
//查询索引
void MyTask::queryIndexTable(){
    wstring tempquery =  s2Ws(_queryWord);
    wstring recordstr;
    map<string,set<int>>& tempindex = _mydict.getIndexTable();  
    for(auto it = tempquery.begin(); it != tempquery.end(); ++it){
        if(!recordstr.empty()){
            if(recordstr.find(*it) == string::npos){
                wstring wstr;
                wstr.push_back(*it);
                string str = ws2S(wstr);
                statistic(tempindex[str]);
                recordstr.push_back(*it);
            }
        }else{
            wstring  wstr ;
            wstr.push_back(*it);
            string str = ws2S(wstr);
            statistic(tempindex[str]);
            recordstr.push_back(*it);
        }
    }
}
//计算最小编辑距离
int MyTask::distance(const string& rhs){
    return editDistance(_queryWord,rhs);
}
//测试
void MyTask::show_resque(){
    size_t size = _resultQue.size();
    cout<<size<<endl;
    for(size_t i = 0; i < size; ++i){
        cout<<_resultQue.top()._word<<" "<<_resultQue.top()._iFreq<<" "<<_resultQue.top()._iDist<<endl;
        _resultQue.pop();
     }
}
