
#include "hasMedkit.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"

/*
*Comprueba si el bot tiene un kit de vida
*
*/
bool hasMedkit::run(blackboard *data){

    if(data->b_bot->getArma().getMunicion().at(PowerCura)>0){
        return true;
    }
    
    return false;
}
