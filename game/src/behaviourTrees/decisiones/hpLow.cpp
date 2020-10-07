
#include "hpLow.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"

/*
*Comprueba si el bot tien poca vida
*
*/
bool hpLow::run(blackboard *data){

    if(data->b_bot->getlife()<data->b_bot->getvidatotal()){
        return true;
    }

    return false;
}
