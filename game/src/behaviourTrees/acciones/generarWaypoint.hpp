#pragma once

#include "../treeTask.hpp"

class blackboard;
struct generarWaypoint : public treeTask {

   //Genera un waypoint aleatorio
   virtual bool run(blackboard *data) override;
    
};