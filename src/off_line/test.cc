//#include"DictProducer.h"
#include"Indextable.h"
Indextable* Indextable::_instance = NULL;
//void test0(){
//    DictProducer dict("/home/dunk/spellCorrect/data/English");
//    dict.build_en_dict();
//    dict.show_files();
//   // dict.show_dict();
//   // dict.show_stopwords();
//    dict.store_dict("/home/dunk/spellCorrect/data/Dict/dict_en"); 
//}
//void test1(){
//    //SplitToolCppJieba*  tool (new SplitToolCppJieba());
//    DictProducer dict("/home/dunk/spellCorrect/data/Chinese"/*,(SplitTool*)tool*/);
//    dict.build_cn_dict();
//  //  dict.show_files();
//    //dict.show_dict();
//   // dict.show_stopwords();
//    dict.store_dict("/home/dunk/spellCorrect/data/Dict/dict_cn");
//}
void test2(){
    Indextable* pDict = Indextable::createInstance();
    pDict->init("/home/dunk/spellCorrect/data/Dict/dict_en","/home/dunk/spellCorrect/data/Dict/dict_cn");
    pDict->show_dict();
    pDict->produce_indextable();
    pDict->store_index_file("/home/dunk/spellCorrect/data/Index/index");
}
int main()
{
   // test0();
   // test1();
    test2();
    return 0;
}

