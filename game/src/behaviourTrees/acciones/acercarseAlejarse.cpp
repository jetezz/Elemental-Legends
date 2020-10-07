
#include "acercarseAlejarse.hpp"
#include "../blackboard.hpp"

    static const std::vector<int> maxRango {50,20,50,70,100};
    static const std::vector<int> minRango {10,10,10,52,20};

    
/*
*Comprueba si el bot está en el rango correcto para atacar con el arma que tiene
*Si es asi cambia la información de movimiento
*/
bool acercarseAlejarse::run(blackboard *data){
    
    int Arma = data->b_bot->getArma().gettipo();
    if(!data->b_closestEnemyInRange){
        cout << "ERROR:: NO HAY ENEMIGO ACERCARSEALEJARSE" << endl;
        return true;
    }
    if(Arma==PowerCura){
        return true;
    }
   
    if(data->closestEnemyDistance>maxRango.at(Arma)) 
    {
        data->Acercarse=true;
        return true;
    }
    if(data->closestEnemyDistance<minRango.at(Arma)) 
    {
        data->Alejarse=true;
        return true;
    }

    data->Alejarse=false;
    data->Acercarse=false;
    return true;
}
