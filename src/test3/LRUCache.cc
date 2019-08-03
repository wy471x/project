#include "LRUCache.h"
//往缓冲区放入数据
void LRUCache::put(string key,string value){
    cout<<"in put func"<<endl;
    auto it = _keys.find(key);
    if(it == _keys.end()){//插入新元素
        if(_nodes.size() ==(size_t) _capacity){
            string deleteKey = _nodes.back().key;
            _nodes.pop_back();//链表尾删除一个结点
            _keys.erase(deleteKey);
        }
        //读文件时，没有的元素就会自动生成对应的结点
        CacheNode node(key,value);
        _nodes.push_front(node);
        _keys.insert(make_pair(key,_nodes.begin()));
        // == _keys[key] = _nodes.begin();
    }
    else{
   //    //更新值
        // it->second->value = value;
        _nodes.splice(_nodes.begin(),_nodes,it->second);
        //从一个list转移元素到另一个list
        cout<<" iterator change"<<endl;
        _keys[key] = _nodes.begin();
   }
}
//从缓冲区中获取数据
string LRUCache::get(string key){
    auto it = _keys.find(key);
    if(it == _keys.end()){
        cout<<"not found"<<endl;
        return string();
    }else{
        cout<<"found!"<<endl;
        istringstream istr(it->second->value);
        string word;
        while(istr>>word){
            cout<<word<<" ";
        }
        cout<<endl;
        string ret = it->second->value;
        cout<<"before splice"<<endl;
        _nodes.splice(_nodes.begin(),_nodes,it->second);//将链表中刚刚被获得元素插入到链表头部
        cout<<"after splice"<<endl;
        _keys[key] = _nodes.begin();
        return ret;
    }
}
//从缓存备份文件读入信息
void LRUCache::readFromfile(const string& filename){
     ifstream ifs_cache(filename);//默认以读方式打开
     string line,word;
     cout<<"read from file"<<endl;
     while(getline(ifs_cache,line)){//应当将key和value的声明放在循环内部
         string key;
         string value;
         istringstream istr(line);
         istr>>key;
         while(istr>>word){
             value += (word + " ");
         }
         put(key,value); 
        // cout<<"readf from file : "<<endl;
        // for(auto& i : _keys){
        //     cout<<i.first<<" ";
        //     for(auto& j : i.second->value)
        //         cout<<j<<" ";
        //     cout<<endl;
        // }
     }
     cout<<"read from file end..."<<endl;
}
//将缓存信息写入备份文件
void LRUCache::writeTofile(const string& filename){
        ofstream ofs_cache(filename);
        cout<<"write to file"<<endl;
       if(!_keys.empty()){ 
        for(auto& i : _keys){
            cout<<i.first<<" ";
            ofs_cache<<i.first<<" ";
            istringstream istr(i.second->value);  
            string j;
            while(istr>>j){
                 cout<<j<<" ";
                ofs_cache<<j<<" ";
            }
            cout<<endl;
            ofs_cache<<endl;
        }
      }
        cout<<"write to file end..."<<endl;
        ofs_cache.close();
}
//缓存更新
void LRUCache::update(const LRUCache& rhs){
    printf("%p\n",&rhs);
    if(!rhs._keys.empty()){
        cout<<" in update func"<<endl;
        cout<<"rhs size : "<<rhs._keys.size()<<endl;
        auto it = rhs._keys.begin();
        for(size_t i = 0; i < rhs._keys.size(); ++i){
            cout<<"key:"<<(*it).first<<" value:";
            istringstream istr((*it).second->value);   
            string word;
            while(istr>>word){
                cout<<word<<" ";
            }
            cout<<endl;
            put(it->first,it->second->value);//假设在一个缓存中有个元素处于链表尾的位置意味着
               //此元素为冷元素，如果在将其插入其他cache应当是无影响的
            ++it;
        }
    }
}
//获取缓存内容
unordered_map<string,list<LRUCache::CacheNode>::iterator> LRUCache::gethashmap(){
          return _keys;
}
