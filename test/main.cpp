#include <iostream>
#include"../src/schedule.h"
#include"../src/coroutine.h"
#include<memory>
using namespace JC;
struct args{
    int n;
};

void func(std::shared_ptr<Schedule> s,void *ud){
    struct args* arg = (args*)ud;
    int start = arg->n;
    for(int i=0;i<50;i++){
        std::cout<<"coroutine "<<s->getCurCoroutineId()<<" "<<start+i<<std::endl;
        s->yield();
    }
}
void test(){
    args arg1{1};
    args arg2{101};
    int co_num = 2;
    std::shared_ptr<Schedule> s(new Schedule(co_num));
    int id1=0,id2=1;
    std::shared_ptr<Coroutine> co1(new Coroutine(s,std::bind(&func,s,&arg1),id1));
    std::shared_ptr<Coroutine> co2(new Coroutine(s,std::bind(&func,s,&arg2),id2));

    s->add(co1);
    s->add(co2);
    int count = 0;
    while(co1->getStatus()||co2->getStatus()){
        if(count==5) s->remove(id1);
        if(count==40) s->remove(id2);
        s->resume(id1);
        s->resume(id2);
        count++;
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;

}
