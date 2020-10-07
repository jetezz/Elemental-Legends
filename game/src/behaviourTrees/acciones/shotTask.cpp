
#include "shotTask.hpp"
#include "../blackboard.hpp"

bool shotTask::run(blackboard *data){

    if(data->Acercarse || data->Alejarse) return true;
    //Dispara y pone el estado en atacando
    
    data->b_bot->disparar(*blackboard::balas);
    data->atacando = true;
    return true;
}
