
#include "rotateToPoint.hpp"
#include "../blackboard.hpp"

bool rotateToPoint::run(blackboard *data){
   
   //Rota al punto objetivo
    data->b_bot->setRotation(data->rotacionaPuntoaMirar); 

    return true;
}
