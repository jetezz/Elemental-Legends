
#include "generarWaypoint.hpp"
#include "../blackboard.hpp"
#include "../../CONSTANTES.hpp"

bool generarWaypoint::run(blackboard *data){

    data->wayPoint.X = data->b_bot->getposition().X + rand() % rangoNextwaypoint*2-1 + (-rangoNextwaypoint);
    data->wayPoint.Z = data->b_bot->getposition().Z + rand() % rangoNextwaypoint*2-1 + (-rangoNextwaypoint);
    data->b_bot->setWaypoint();
    
    //cout << "generando waypoint " <<endl;
    //cout << "wayx:" << data->wayPoint.X << endl;
    //cout << "wayzw:" << data->wayPoint.Z << endl;
    return true;
}
