
#include "pickeableOnSight.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"


bool pickeableOnSight::run(blackboard *data){
    
    //Si la lista de objetivos pickeables está vacia no hacemos nada
    if(data->pickeables->empty()) {
        return false;
    }
    //Posición del bot actual
    float posX = data->b_bot->getposition().X;
    float posY = data->b_bot->getposition().Y;
    float posZ = data->b_bot->getposition().Z;
    float distanciaMascorta {9999};

    vector3d rotacion {};
    gameObject *target {nullptr};

    float dx {};
    float dy {};
    float dz {};

    //Conseguir el objetivo más cercano
    for (std::vector<std::unique_ptr<gameObject>>::size_type i=0;i<data->pickeables->size();i++){   
	if(data->pickeables->at(i).get()){

        auto pickeable = data->pickeables->at(i).get();
            if(pickeable->isPickeable()){ //Si el objeto es pickeable hacemos las cosas, es decir, si se puede recoger
                auto posPickeable = pickeable->getposition();
                
                dx = posPickeable.X - posX;
                dy = posPickeable.Y - posY;
                dz = posPickeable.Z - posZ;
                float xzdistance = sqrtf(dx*dx+dz*dz);
                //Calculamos la distancia euclidea y nos quedamos con el objeto más cercano
                if(xzdistance<=distanciaVision){
                    if(xzdistance<distanciaMascorta) {
                        distanciaMascorta = xzdistance;
                        target = pickeable;
                        
                            //Si la distancia al enemigo es menos de 20 lo detecta direcctamente
                            if(distanciaMascorta<=distanciaDeteccionMinima) {
                            
                                data->wayPoint = target->getposition();
                                data->b_bot->setWaypoint();
                                return true;
                                
                            }

                    }
                }
            }

        }
    }

    if(!target){
        return false;
    }

    dx = target->getposition().X - posX;
    dy = target->getposition().Y - posY;
    dz = target->getposition().Z - posZ;

    //Rotación al objetivo
    rotacion = vector3d(-atan2f(dy,distanciaMascorta)*180/PI,-atan2f(-dx,dz)*180/PI,0);

    //Normalizamos la rotación.
    if(rotacion.Y<=0) rotacion.Y += 360;

    //Conseguimos el angulo maximo y minimo de vision humana
    float angMin = data->b_bot->getRotation().Y-anguloVision;
    float angMax = data->b_bot->getRotation().Y+anguloVision;

    //Normalizar angulo de 0 a 360 para comparar mas facil
    if(angMin<0) angMin += 360;
    if(angMax<0) angMax += 360;
    if(angMin>=360) angMin -= 360;
    if(angMax>=360) angMax -= 360;

    // cout << "angMin" << angMin  << endl;
    // cout << "angMax" << angMax  << endl;
	// cout << "rotacion" << data->anguloClosestEnemy  << endl;
    
   
    //Si ver si el enemigo está en el angulo de vision de 0 a 360 si el angulo esta entre 350 a 20 por ejemplo la comparacion es distinta
    if(angMin<angMax){
        if(rotacion.Y>=angMin && rotacion.Y<=angMax){
            data->wayPoint = target->getposition();
            data->b_bot->setWaypoint();
            return true;
        }   
    }else{
        if(rotacion.Y>=angMin || rotacion.Y<=angMax){
            data->wayPoint = target->getposition();
            data->b_bot->setWaypoint();
            return true;
        }
    }
    
   

    return false;
}
