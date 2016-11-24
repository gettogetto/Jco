#include <iostream>
#include"../src/schedule.h"
#include"../src/coroutine.h"
#include<memory>
using namespace std;
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
    std::shared_ptr<Schedule> s(new Schedule());
    std::shared_ptr<Coroutine> co1(new Coroutine(s,std::bind(&func,s,&arg1),0));
    std::shared_ptr<Coroutine> co2(new Coroutine(s,std::bind(&func,s,&arg2),1));

    s->add(co1);
    s->add(co2);
    int count = 0;
    while(co1->getStatus()||co2->getStatus()){
        if(count==5) s->remove(0);
        if(count==40) s->remove(1);
        s->resume(0);
        s->resume(1);
        count++;
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;

}
