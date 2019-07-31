#include"Cache.h"
//Cache::Cache(const Cache& cache){
//   this->update(cache);
//}
void Cache::addElement(const string&key , const vector<string>& value){
     _hashmap[key] = value;
}
//从文件读取缓存信息
void Cache::readFromFile(const string& filename){
   /// cout<<"readFromfile :"<<endl;
    ifstream ifs_cache(filename,ifstream::in);
    string line,word;
    while(getline(ifs_cache,line)){
        pair<string,vector<string>> ssp;//该声明放在循环体内部，防止被篡改
        istringstream istr(line);
        istr>>ssp.first;
       // cout<<ssp.first<<" ";
        while(istr>>word){
            ssp.second.push_back(word);
      //      cout<<word<<" ";
        }
     //   cout<<endl;
        _hashmap.insert(ssp);
    }
   // for(auto& i: _hashmap){
   //     cout<<i.first<<" ";
   //     for(auto& j : i.second)
   //         cout<<j<<" ";
   //     cout<<endl;
   // }  
}
//将缓存写入文件
void Cache::writeToFile(const string& filename){
 //   cout<<"111"<<endl;  
    ofstream ofs_cache(filename,ios::trunc);
       for(auto& i : _hashmap){
          // cout<<i.first<<" ";
           ofs_cache<<i.first<<" ";
           for(auto& j : i.second ){
          //     cout<<j<<endl;
               ofs_cache<<j<<" ";
           }
         //  cout<<endl;
           ofs_cache<<endl;  
        }
       //ofs_cache<<endl;
}
//更新缓存信息,将其他的cache内容添加到本cache
void Cache::update(const Cache& rhs){
    for(auto& i : rhs._hashmap){ 
        _hashmap.insert(i);
    }
}
//获取本cache的内容
unordered_map<string,vector<string>> Cache::gethashmap(){
    return _hashmap;
}
