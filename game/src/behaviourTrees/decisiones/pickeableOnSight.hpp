#pragma once

#include "../treeTask.hpp"

class blackboard;
struct pickeableOnSight : public treeTask {

   

public:
/*
   Comprueba si el enemigo objetivo está en el rango de visión
*/
   virtual bool run(blackboard *data) override;
};