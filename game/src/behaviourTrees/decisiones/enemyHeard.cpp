
#include "enemyHeard.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"


bool enemyHeard::run(blackboard *data){
    


       
    
    ////////////////
    //Hay objetivo//
    ////////////////

    
       if(data->atacando) return true;
        
    
    float botx = data->b_bot->getposition().X;
    float boty = data->b_bot->getposition().Y;
    float botz = data->b_bot->getposition().Z;
    
    ///////////////////
    //No hay objetivo//
    ///////////////////
    //cout << "numEscu:" << data->PuntosEscuchados->size() << endl;

    for (std::vector<vector3d>::size_type i=0;i<data->PuntosEscuchados->size();i++){

        auto pos = data->PuntosEscuchados->at(i);
        auto dx = botx-pos.X;
        auto dy = boty-pos.Y;
        auto dz = botz-pos.Z;
        auto distancia = sqrt(dx*dx+dy*dy+dz*dz);

        if(distancia<=distanciaEscucha){
            data->wayPoint = pos;
            data->b_bot->setWaypoint();
            return false;
        }
        
    }
  
  return false;
}
