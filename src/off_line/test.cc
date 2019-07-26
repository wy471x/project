//#include"DictProducer.h"
#include"Mydict.h"
Mydict* Mydict::_instance = NULL;
//void test0(){
//    DictProducer dict("/home/dunk/spellCorrect/data/English");
//    dict.build_en_dict();
//    dict.show_files();
//   // dict.show_dict();
//   // dict.show_stopwords();
//    dict.store_dict("/home/dunk/spellCorrect/data/Dict/dict_en"); 
//}
//void test1(){
//    DictProducer dict("/home/dunk/spellCorrect/data/Chinese");
//    dict.build_cn_dict();
//  //  dict.show_files();
//    //dict.show_dict();
//   // dict.show_stopwords();
//    dict.store_dict("/home/dunk/spellCorrect/data/Dict/dict_cn");
//}
void test2(){
    Mydict* pDict = Mydict::createInstance();
    pDict->init("/home/dunk/spellCorrect/data/Dict/dict_en","/home/dunk/spellCorrect/data/Dict/dict_cn");
    pDict->show_dict();
    pDict->produce_indextable();
    pDict->store_index_file("/home/dunk/spellCorrect/data/Index/index");
}
int main()
{
   // test0();
    //test1();
    test2();
    return 0;
}

