#ifndef SCHEDULE_H
#define SCHEDULE_H

#include<ucontext.h>
#include<unordered_map>
#include<memory>
#include<functional>
namespace JC{
    class Coroutine;
	class Schedule
	{
	public:
	    using CoMap = std::unordered_map<int,std::shared_ptr<Coroutine>>;
	    enum{_STACKSIZE = 1024*1024,_MAX_CO_NUM = 10};
	   // enum{DEAD,READY,RUNNING,SUSPEND};
	    Schedule(int num=10);
	    ~Schedule();

	    void add(std::shared_ptr<Coroutine> coroutine);
	    void remove(int coroutine_id);
	    void resume(int coroutine_id);
	    void yield();

	    int getStatus(int coroutine_id);
	    int getCurCoroutineId(){return _cur_run_id;}
	private:
	    //void _save_stack(void *top);
	    char _stack[_STACKSIZE];
	    ucontext_t _nextContext;
	    int _co_cur_num;
	    int _co_max_num;
	    int _cur_run_id;
	    CoMap _map;


	    friend  void funcGate(uint32_t low32,uint32_t high32);
	    //friend  void funcGate(void *ptr);
	};
}
#endif // SCHEDULE_H
