#include"DictProducer.h"
#include"SplitTool.h"
//string -> wstring
wstring s2Ws(const string& str){
    if(str.empty())
        return L"";
    unsigned len = str.size() + 1;
    setlocale(LC_CTYPE,"en_US.UTF-8");
    unique_ptr<wchar_t[]> p(new wchar_t[len]);
    mbstowcs(p.get(),str.c_str(),len);
    wstring w_str(p.get());
    return w_str;
}
//wstring -> string
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

DictProducer::DictProducer(const string& dir){
    _dir = dir;
}
DictProducer::DictProducer(const string& dir,SplitTool* splittool){
    _dir = dir;
    _splittool = splittool;
}
//英文处理
void DictProducer::build_en_dict(){
    get_files();
    get_stopwords("../data/Stop_words/stop_words_eng.txt");
    for(auto it = _files.begin();it != _files.end();++it){
        ifstream ifs(*it);
        text_deal(*it,ifs);
    }
    for(auto it = _files.begin();it != _files.end(); ++it){
        ifstream ifs(*it);
        string word;
        while(ifs>>word){
            if(stop_words.find(word) == stop_words.end())
                 push_dict(word);
        }
    }
}
//中文处理
void DictProducer::build_cn_dict(){
   get_files();
   _splittool = new SplitToolCppJieba();
   get_stopwords("../data/Stop_words/stop_words_zh.txt");
//  for(auto& it : _files)
//       cout<<it<<endl;
   for(auto it = _files.begin(); it != _files.end(); ++it){
       ifstream ifs(*it);
       string sentence;
       vector<string> word ; 
       while(ifs>>sentence){
           wstring wstr = s2Ws(sentence);
           wregex wreg(L"[^\u4E00-\u9FA5]");
           wstr = regex_replace(wstr,wreg, L" ");
           sentence = ws2S(wstr);
           word = _splittool->cut(sentence); 
           for(auto it = word.begin(); it != word.end(); ++it){
               if(stop_words.find(*it) == stop_words.end()&& (*it) != " "){
                   push_dict(*it);
               }
           }
       }
   }
   delete _splittool;
}
//将词典写入文件
void DictProducer::store_dict(const char* filepath){
     ofstream ofs(filepath);
     for(auto it = _dict.begin(); it != _dict.end();++it){
        ofs<<(*it).first<<" "<<(*it).second<<endl;
     }
}
//获取文件路径
void DictProducer::get_files(){
   DIR* dir;
   struct dirent* ptr;
   if((dir = opendir(_dir.c_str())) == NULL){
       perror("Open dir error!");
       exit(1);
   }
   while((ptr = readdir(dir))!= NULL){
       if(strcmp(ptr->d_name,".") == 0 || strcmp(ptr->d_name,"..") == 0)
           continue;
       else if(ptr->d_type == 8){
           string str = _dir +"/"+ ptr->d_name;
           _files.push_back(str);
           
       }
       else{
           continue;
       }
   }
   closedir(dir);
}
//停用词处理
void DictProducer::get_stopwords(const string& file){
    ifstream ifs(file);
    string word;
    while(ifs>>word){
        stop_words.insert(word);
    }
}
//文件内容预先处理
void DictProducer::text_deal(const string& file,ifstream& ifs){
    string line;
    vector<string> tempfile;
         
    while(getline(ifs,line)){
        tempfile.push_back(line);
    }
    for(auto i = tempfile.begin(); i != tempfile.end();++i){
       for(auto j = (*i).begin(); j != (*i).end();++j) 
        if(!isalpha(*j)){
            (*j) = ' ';
        }
    }
    ofstream ofs(file);
    for(auto it = tempfile.begin(); it != tempfile.end(); ++it){
      for(auto& i : (*it))
             i = tolower(i);
      ofs<<(*it)<<endl;
    }
}
//存储单词
void  DictProducer::push_dict(const string& word){
    
    _dict[word]++;
}
//查看文件路径
void DictProducer::show_files()const{
    for(auto it = _files.begin(); it != _files.end();++it){
        cout<<*it<<endl;
    }
}
//查看词典
void DictProducer::show_dict()const{
    for(auto& t : _dict)
        cout<<t.first<<" "<<t.second<<endl;
}
//查看停用词
void DictProducer::show_stopwords()const{
    for(auto& t : stop_words)
        cout<<t<<endl;
}
