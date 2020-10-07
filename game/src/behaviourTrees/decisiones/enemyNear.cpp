
#include "enemyNear.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"


bool enemyNear::run(blackboard *data){
    


        float botx = data->b_bot->getposition().X;
        float boty = data->b_bot->getposition().Y;
        float botz = data->b_bot->getposition().Z;
    
    ////////////////
    //Hay objetivo//
    ////////////////

    //Si ya hay un objetivo, y el objetivo está vivo aun, no vamos a cambiar el objetivo, aunque haya alguno más cerca.
    if(data->atacando && data->b_closestEnemyInRange->isAlive()) {

            auto pos = data->b_closestEnemyInRange->getposition();
            auto dx = botx-pos.X;
            auto dy = boty-pos.Y;
            auto dz = botz-pos.Z;
            auto distancia = sqrt(dx*dx+dy*dy+dz*dz);

        data->closestEnemyDistance = distancia;
        //Cambiamos la distancia del objetivo actual, para olvidarlo si se aleja lo sufciente
        if(distancia<=distanciaVision){
            return true;
        }
       
       data->atacando = false;
       return false;
        
    }
  
    
    ///////////////////
    //No hay objetivo//
    ///////////////////

    bool result = false;
    entity *target = nullptr;
    float distanciaMascorta {};
    data->atacando = false;
    
    for (std::vector<std::unique_ptr<bala>>::size_type i=0;i<data->entidades->size();i++){
        if(data->entidades->at(i).get()!=data->b_bot && data->entidades->at(i)->getTipo()!=muerto){

            auto pos = data->entidades->at(i)->getposition();
            auto dx = botx-pos.X;
            auto dy = boty-pos.Y;
            auto dz = botz-pos.Z;
            auto distancia = sqrt(dx*dx+dy*dy+dz*dz);

            if(distancia<=distanciaVision){
                result = true;

                if(!target){
                    target = data->entidades->at(i).get();
                    distanciaMascorta = distancia;
                }else if(distancia<distanciaMascorta){
                    target = data->entidades->at(i).get();
                    distanciaMascorta = distancia;
                }

            }
           // cout << "ndistancia calculada"<<distancia<< endl;
            //cout << "ndistancia closest"<<data->closestEnemyDistance<< endl;

        
        }
        
    }

        data->b_closestEnemyInRange = std::move(target);
        data->closestEnemyDistance = distanciaMascorta;

   
  
   //cout << "ENemigo cerca?"<< result << endl;
    
    return result;
}
