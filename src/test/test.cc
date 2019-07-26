#include"MyTask.h"
MyDict* MyDict::_instance = NULL;
void test0(){
  MyTask mytask("我我我",0);
  mytask.execute();
  mytask.show_resque();
}
int main()
{
    test0();
    return 0;
}

