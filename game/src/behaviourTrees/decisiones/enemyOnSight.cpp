
#include "enemyOnSight.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"


bool enemyOnSight::run(blackboard *data){
     
    //std::cout << "Rotando al enemigo más cercano" << std::endl;
    auto target = data->b_closestEnemyInRange;
    if(target==nullptr) {
        std::cout << "ERROR:: NO HAY ENEMIGO TARGET" << std::endl;
        return false;
    }
     
    auto vec = target->getposition();
    float dx = vec.X - data->b_bot->getposition().X;
	float dy = vec.Y - data->b_bot->getposition().Y;
	float dz = vec.Z - data->b_bot->getposition().Z;
	float xzdistance = sqrtf(dx*dx+dz*dz);

	auto rotacion = vector3d(-atan2f(dy,xzdistance)*180/PI,-atan2f(-dx,dz)*180/PI,0);
    if(rotacion.Y<=0) rotacion.Y += 360;
    data->rotacionaPuntoaMirar = rotacion;
    data->anguloClosestEnemy = rotacion.Y;
    
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
        if(data->anguloClosestEnemy>=angMin && data->anguloClosestEnemy<=angMax){
            data->b_bot->removeWaypoint();
            return true;
        }   
    }else{
        if(data->anguloClosestEnemy>=angMin || data->anguloClosestEnemy<=angMax){
            data->b_bot->removeWaypoint();
            return true;
        }
    }
    
    //Si la distancia al enemigo es menos de 20 lo detecta direcctamente
    if(data->closestEnemyDistance<=distanciaDeteccionMinima) return true;
    
    return false;
}
