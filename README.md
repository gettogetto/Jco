# Jcoroutine

A simple coroutine library based on C++11.

Schedule::add() adds a coroutine to the schedule.

Schedule::remove() removes a coroutine in the schedule.

Schedule::resume() continue a coroutinue. 

Schedule::yield() suspends a coroutine.


##Example:

#include"schedule.h"

#include"coroutine.h"

#include<iostream>

using namespace JC;

using namespace std;

void func1(std::shared_ptr<Schedule> s){

    cout<<"1"<<endl;

    cout<<"2"<<endl;

    s->yield();

    cout<<"3"<<endl;

    s->yield();

}

void func2(std::shared_ptr<Schedule> s){

    cout<<"a"<<endl;

    s->yield();

    cout<<"b"<<endl;

    cout<<"c"<<endl;

    s->yield();

}

void func3(std::shared_ptr<Schedule> s){

    cout<<"x"<<endl;

    s->yield();

    cout<<"y"<<endl;

    cout<<"z"<<endl;

    s->yield();

}

int co_num = 3;

int id1=0,id2=1,id3=2;

std::shared_ptr<Schedule> s(new Schedule(co_num));

std::shared_ptr<Coroutine> co1(new Coroutine(s,std::bind(&func1,s),id1));

std::shared_ptr<Coroutine> co2(new Coroutine(s,std::bind(&func2,s),id2));

std::shared_ptr<Coroutine> co3(new Coroutine(s,std::bind(&func3,s),id3));

int main(){

   s->add(co1);

   s->add(co2);

   s->add(co3);

   s->resume(id1);

   s->resume(id2);

   s->resume(id3);

   s->resume(id1);

   s->resume(id2);

   s->resume(id3);

}

##Output:

1

2

a

x

3

b

c

y

z


