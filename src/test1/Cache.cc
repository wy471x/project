#include"Cache.h"
Cache::Cache(const Cache& cache){
   _hashmap = cache._hashmap;
}
void Cache::addElement(const string&key , const string& value){
    _hashmap[key] = value;
}
//从文件读取缓存信息
void Cache::readFromFile(const string& filename){
    ifstream ifs_cache(filename);
    string str1,str2;
    while(ifs_cache>>str1>>str2){
         _hashmap[str1] = str2;
    }
}
//将缓存写入文件
void Cache::writeToFile(const string& filename){
       ofstream ofs_cache(filename);
       for(auto& i : _hashmap)
           ofs_cache<<i.first<<" "<<i.second<<endl;
}
//更新缓存信息
void Cache::update(const Cache& rhs){
    for(auto& i : rhs._hashmap)
         _hashmap.insert(i);
}
