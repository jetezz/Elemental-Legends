
#include "hayWaypoint.hpp"
#include "../blackboard.hpp"



bool hayWaypoint::run(blackboard *data){
   // cout << "haswaypoint "<< data->b_bot->hasWaypointToMove() << endl;
    
    return data->b_bot->hasWaypointToMove();

}
