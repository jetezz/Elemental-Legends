#include "moveTo.hpp"
#include "../blackboard.hpp"
#include "../../motor_grafico/fachadaIrrlicht.hpp"

bool moveTo::run(blackboard *data){

   data->b_bot->moveTo(data->wayPoint);
  
     if(pointIntersectsNode(data->wayPoint, data->b_bot->getImage()))
        data->b_bot->removeWaypoint();
     
   // cout << "distancia al punto: " << dis << endl;
     
    return true;
}
