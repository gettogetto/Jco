#ifndef COROUTINE_H
#define COROUTINE_H
#include<ucontext.h>
#include<memory>
#include<cstddef>
#include"schedule.h"
namespace JC{
	class Coroutine
	{
	public:
	    enum{DEAD,READY,RUNNING,SUSPEND};
	    using CoFunc = std::function<void()>;
	    Coroutine();
	    Coroutine(std::shared_ptr<Schedule> s,CoFunc func,int id);
	    int getId();
	    int getStatus();
	    void setStatus(int status);
	    ~Coroutine();
	    void runFunc();
	private:
	    CoFunc _func;
	    void _save_stack(void* top);


	    int _id;
	    ucontext_t _context;
	    std::shared_ptr<Schedule> _schedule;
	    std::ptrdiff_t _stack_max_size;
	    std::ptrdiff_t _stack_cur_size;
	    int _status;
	    char *_stack;

	    friend class Schedule;
	};
}
#endif // COROUTINE_H
