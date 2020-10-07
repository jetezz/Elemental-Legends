
#include "useMedkit.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"
bool useMedkit::run(blackboard *data){
   //Accion de curarse los bots
   auto armaAnterior = data->b_bot->getArma().gettipo();

   data->b_bot->getArma().setTipo(PowerCura);
   data->b_bot->disparar(*blackboard::balas);
   data->b_bot->setVida(data->b_bot->getlife()+curacionMedikit);

   data->b_bot->getArma().setTipo(armaAnterior);

    return true;
}
