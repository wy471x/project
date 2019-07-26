#include"Mydict.h"
//单例模式创建一个实例
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
Mydict* Mydict::createInstance(){
   if(_instance == NULL)
       _instance = new Mydict();
   return _instance;
}
//初始化词典
void Mydict::init(const char* dictEnPath,const char* dictCnPath){
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
}
//获取词典
vector<pair<string,int>>& Mydict::getDict(){
    return _dict;
}
//获取索引表
map<string,set<int>>& Mydict::getIndexTable(){
    return _index_table;
}
//生成索引表
void Mydict::produce_indextable(){
    for(size_t i = 0; i != _dict.size(); ++i){
        wstring tempwstr = s2Ws(_dict[i].first);
        for(auto j = tempwstr.begin(); j != tempwstr.end(); ++j){
            wstring wstr;
            wstr.push_back(*j);
            _index_table[ws2S(wstr)].insert(i + 1);
        }
    }
}
//存储索引表
void Mydict::store_index_file(const string& file){
   ofstream ofs(file);
   for(auto& i : _index_table){
       ofs<<i.first<<" ";
       for(auto it = i.second.begin(); it != i.second.end(); ++it)
           ofs<<(*it)<<" ";
       ofs<<endl;
   }
}
//测试，词典
void Mydict::show_dict(){
    vector<pair<string,int>> pv = getDict();
    for(auto& it : pv)
        cout<<it.first<<" "<<it.second<<endl;
}
