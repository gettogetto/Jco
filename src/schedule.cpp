#include "schedule.h"
#include"coroutine.h"
#include<assert.h>
#include<string.h>

void mainfunc(uint32_t low32,uint32_t high32)
{
    uintptr_t ptr=(uintptr_t)low32|((uintptr_t)high32<<32);
    Schedule* s = reinterpret_cast<Schedule*>(ptr);
    int id = s->_cur_run_id;
    std::shared_ptr<Coroutine> c = s->_map[id];
    c->runFunc();
}

Schedule::Schedule():
    _co_cur_num(0),_co_max_num(_MAX_CO_NUM),_cur_run_id(-1)
{

}
Schedule::~Schedule()
{

}



void Schedule::add(std::shared_ptr<Coroutine> coroutine)
{
    assert(_co_cur_num<_co_max_num);
    _map[coroutine->getId()]=coroutine;

}

void Schedule::remove(int coroutine_id)
{
    assert(_map.find(coroutine_id)!=_map.end());
    if(coroutine_id==_cur_run_id){
        _cur_run_id=-1;
    }
    _map[coroutine_id]->setStatus(Coroutine::DEAD);
    _map.erase(coroutine_id);

}

void Schedule::resume(int coroutine_id)
{
    assert(this->_cur_run_id==-1);
    if(_map.find(coroutine_id)==_map.end()) return;
    std::shared_ptr<Coroutine> coroutine = _map[coroutine_id];
    int status = getStatus(coroutine_id);
    switch(status){
        case Coroutine::READY:{
            getcontext(&coroutine->_context);
            coroutine->_context.uc_stack.ss_sp=_stack;
            coroutine->_context.uc_stack.ss_size=_STACKSIZE;
            coroutine->_context.uc_link = &_nextContext;

            _cur_run_id=coroutine_id;
            coroutine->setStatus(Coroutine::RUNNING);
            uintptr_t pt = reinterpret_cast<uintptr_t>(this);
            makecontext(&coroutine->_context,reinterpret_cast<void(*)()>(&mainfunc),2,(uint32_t)pt,(uint32_t)(pt>>32));
            swapcontext(&this->_nextContext,&coroutine->_context);


            break;
        }
        case Coroutine::SUSPEND:{

            memcpy(_stack+_STACKSIZE-coroutine->_stack_cur_size,coroutine->_stack,coroutine->_stack_cur_size);
            _cur_run_id = coroutine_id;
            coroutine->setStatus(Coroutine::RUNNING);
            swapcontext(&_nextContext,&coroutine->_context);
            break;
        }
        default:
            assert(0);

    }//switch

}//resume

void Schedule::yield()
{
    int id = _cur_run_id;
    assert(id!=-1);
    std::shared_ptr<Coroutine> c = _map[id];
    assert(reinterpret_cast<char*>(&c) > _stack);
    c->_save_stack(_stack+_STACKSIZE);
    c->setStatus(Coroutine::SUSPEND);
    _cur_run_id = -1;
    swapcontext(&c->_context,&_nextContext);
}



int Schedule::getStatus(int coroutine_id)
{
    return _map[coroutine_id]->getStatus();
}


