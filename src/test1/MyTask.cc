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
MyTask::MyTask(const string& qWord,const TcpConnectionPtr& conn)
    :_conn(conn)
    ,_mydict(*MyDict::createInstance())
{
    _queryWord = qWord;
    _mydict.init("/home/dunk/spellCorrect/data/Dict/dict_en","/home/dunk/spellCorrect/data/Dict/dict_cn","/home/dunk/spellCorrect/data/Index/index");
}
//执行查询
void MyTask::execute(){
    if(!queryCache())
    {
         queryIndexTable();
         //读取查询结果，用小火车返回给客户端
         priority_queue<MyResult,vector<MyResult>,MyCompare> tempqueue = _resultQue;
         response();
         if(!tempqueue.empty())
         {
             vector<string> elements;
             string key = _queryWord;
             size_t i = 5;
             if(tempqueue.size() <= i)
             {
             while(!tempqueue.empty())
             {
                 MyResult temp = tempqueue.top();
                 elements.push_back(temp._word);
                 tempqueue.pop();
             }
             cout<<" add elements to cachenum : "<<wd::current_thread::threadnum<<endl;
             CacheManager::getCache(wd::current_thread::threadnum).addElement(key,elements);
             }
             else
             {
                 size_t j = 0;
                 while(j < i)
                 {
                     MyResult temp = tempqueue.top();
                     elements.push_back(temp._word);
                     tempqueue.pop();
                     j++;
                 }
             cout<<" add elements to cachenum : "<<wd::current_thread::threadnum<<endl;
             CacheManager::getCache(wd::current_thread::threadnum).addElement(key,elements);
            } 
       }
  }
}
//进行计算
void MyTask::statistic(set<int>& iset,int bitmap[]){
    MyResult res;
    for(auto it = iset.begin(); it != iset.end(); ++it){
        if(bitmap[*it] == 0){
            res._word = _mydict.getDict()[(*it) - 1].first;
            res._iFreq = _mydict.getDict()[(*it) - 1].second;
            res._iDist = distance(_mydict.getDict()[(*it) - 1].first);
            _resultQue.push(res);
            bitmap[*it] = 1;
        }
    }
}
//缓存查询
bool MyTask::queryCache(){
    int threadnum = wd::current_thread::threadnum; 
    cout<<"query cachenum : "<<threadnum<<endl;
    Cache& cache = CacheManager::getCache(threadnum);  
 //   cout<<cache.gethashmap().size()<<endl; 
    if(!cache.gethashmap().empty()){
      if(cache.gethashmap().find(_queryWord)!= cache.gethashmap().end())
      {
         //切记for循环不要与迭代器混用 
         // for(auto& it : cache.gethashmap()){     
         //    cout<<it.first<<" ";
         //    for(auto& i : it.second)
         //        cout<<i<<" ";
         //    cout<<endl;
         //  } 
          Train cachedata;
          Value jsonstr;
          //此处若将迭代器与for循环进行混用会造成乱码现象，不知为何
          for(size_t i = 0; i < cache.gethashmap()[_queryWord].size(); ++i){
             //  cout<<cache.gethashmap()[_queryWord][i]<<" ";
              jsonstr[_queryWord].append(cache.gethashmap()[_queryWord][i]);
          }
         // cout<<endl;
          strcpy(cachedata.buff,jsonstr.toStyledString().c_str());       
  //        cout<<jsonstr.toStyledString().c_str()<<endl;
          cachedata.len = strlen(cachedata.buff);
          _conn->sendInLoop(cachedata);
          return true;
      }
    }
    return false;
}
//查询索引
void MyTask::queryIndexTable(){
    wstring tempquery =  s2Ws(_queryWord);
    map<string,set<int>>& tempindex = _mydict.getIndexTable();  
    int bitmap[100000] = {0};
    for(auto it = tempquery.begin(); it != tempquery.end(); ++it){
            wstring  wstr ;
            wstr.push_back(*it);
            string str = ws2S(wstr);
            statistic(tempindex[str],bitmap);
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
//响应客户端请求
void MyTask::response(){
   Train train;
   size_t key = 5;
   MyResult temp;
   Value jsonstr;
   
   if(_resultQue.size() >= key){
       while(key--){
          temp = _resultQue.top();
          jsonstr[_queryWord].append(temp._word);
          _resultQue.pop();
       }
   }else{
       while(!_resultQue.empty()){
           temp = _resultQue.top();
          // cout<<temp._word<<endl;
           jsonstr[_queryWord].append(temp._word);
           _resultQue.pop();
       }
   }
   strcpy(train.buff,jsonstr.toStyledString().c_str());//符合条件的查询结果
   train.len = strlen(train.buff);
   _conn->sendInLoop(train);
}
