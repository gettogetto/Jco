# Jcoroutine

A simple coroutine library based on C++11.

Schedule::add() adds a coroutine to the schedule.

Schedule::remove() removes a coroutine in the schedule.

Schedule::resume() continue a coroutinue. 

Schedule::yield() suspends a coroutine.


##Get Start:

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

##Output:

	coroutine 0 1

	coroutine 1 101

	coroutine 0 2

	coroutine 1 102

	coroutine 0 3

	coroutine 1 103

	coroutine 0 4

	coroutine 1 104

	coroutine 0 5

	coroutine 1 105

	coroutine 1 106

	coroutine 1 107

	coroutine 1 108

	coroutine 1 109

	coroutine 1 110

	coroutine 1 111

	coroutine 1 112

	coroutine 1 113

	coroutine 1 114

	coroutine 1 115

	coroutine 1 116

	coroutine 1 117

	coroutine 1 118

	coroutine 1 119

	coroutine 1 120

	coroutine 1 121

	coroutine 1 122

	coroutine 1 123

	coroutine 1 124

	coroutine 1 125

	coroutine 1 126

	coroutine 1 127

	coroutine 1 128

	coroutine 1 129

	coroutine 1 130

	coroutine 1 131

	coroutine 1 132

	coroutine 1 133

	coroutine 1 134

	coroutine 1 135

	coroutine 1 136

	coroutine 1 137

	coroutine 1 138

	coroutine 1 139

	coroutine 1 140

