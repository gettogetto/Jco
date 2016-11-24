#include "coroutine.h"
#include<assert.h>
#include<string.h>
namespace JC{
	Coroutine::Coroutine()
	{

	}
	Coroutine::Coroutine(std::shared_ptr<Schedule> s,CoFunc func,int id)
	    :_func(func),_id(id),_schedule(s),
	      _stack_max_size(0),_stack_cur_size(0),_status(READY),_stack(0)
	{

	}
	Coroutine::~Coroutine()
	{
	    delete []_stack;

	}

	int Coroutine::getId()
	{
	    return _id;
	}

	int Coroutine::getStatus()
	{
	    return _status;
	}

	void Coroutine::setStatus(int status)
	{
	    _status=status;
	}

	void Coroutine::runFunc()
	{
	    _func();
	}
	void Coroutine::_save_stack(void *top)
	{
	    char dummy = 0;
	    assert((char*)top-&dummy<=Schedule::_STACKSIZE);
	    if(_stack_max_size<(char*)top-&dummy){
		delete []_stack;
		_stack_max_size=(char*)top-&dummy;
		_stack=new char[_stack_max_size];
	    }
	    _stack_cur_size=(char*)top-&dummy;
	    memcpy(_stack,&dummy,_stack_cur_size);
	}
}
