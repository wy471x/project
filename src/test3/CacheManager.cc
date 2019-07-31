#include"CacheManager.h"
vector<LRUCache> CacheManager::_cachelist;
string CacheManager::_filename = "/home/dunk/spellCorrect/data/Cache/cache";//cache文件名
int CacheManager::_num = 4;//缓存个数
