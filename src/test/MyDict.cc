#include"MyDict.h"
wstring s2Ws(const string& str){
    if(str.empty()){
        return L"";
    }
    unsigned len = str.size() + 1;
    setlocale(LC_CTYPE,"en_US.UTF-8");
    unique_ptr<wchar_t[]> p(new wchar_t[len]);
    mbstowcs(p.get(),str.c_str(),len);
    wstring w_str(p.get());
    return w_str;
}
string ws2S(const wstring& wstr){
    if(wstr.empty())
        return "";
    unsigned len = wstr.size() * 4 + 1;
    setlocale(LC_CTYPE,"en_US.UTF-8");
    unique_ptr<char[]> p(new char[len]);
    wcstombs(p.get(),wstr.c_str(),len);
    string str(p.get());
    return str;
}
//单例模式创建一个实例
//创建实例
MyDict* MyDict::createInstance(){
   if(_instance == NULL)
       _instance = new MyDict();
   return _instance;
}
//初始化词典
void MyDict::init(const char* dictEnPath,const char* dictCnPath,const char* indexPath){
      ifstream ifs_en(dictEnPath);
      string word;
      int num;
      while(ifs_en>>word>>num){
             _dict.push_back(make_pair(word,num));
      }
      ifstream ifs_cn(dictCnPath);
      string chinese;
      int cnt;
      while(ifs_cn>>chinese>>cnt){
          _dict.push_back(make_pair(chinese,cnt));
      }
      ifstream ifs_index(indexPath);
      string line;
      while(getline(ifs_index,line)){
          pair<string,set<int>> temppair;
          istringstream istr(line);
          istr>>temppair.first;
          int num;
          while(istr>>num){
              temppair.second.insert(num);
          }
          _index_table.insert(temppair);
      }
}
//获取词典
vector<pair<string,int>>& MyDict::getDict(){
    return _dict;
}
//获取索引表
map<string,set<int>>& MyDict::getIndexTable(){
    return _index_table;
}
//测试索引
//void Mydict::showIndex(){
//    for(auto& i : _index_table)
//    {
//        cout<<i.first<<" ";
//        for(auto& j : i.second)
//            cout<<j<<" ";
//        cout<<endl;
//        exit(0);
//    }
//}
