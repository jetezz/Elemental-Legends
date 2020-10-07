
#include "hasAmmo.hpp"
#include "../blackboard.hpp"


/*
*Comprueba si hay munición suficiente en el arma actual
*
*/
bool hasAmmo::run(blackboard *data){
    
    int tipo = data->b_bot->getArma().gettipo();

    if(data->b_bot->getArma().getMunicion().at(tipo)>0) return true;

    return false;

}
