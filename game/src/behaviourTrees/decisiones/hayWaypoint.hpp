#pragma once

#include "../treeTask.hpp"

class blackboard;
struct hayWaypoint : public treeTask {

public:
/*
   Comprueba si el bot tiene un punto al que dirigirse.
   Esto sirve para que la siguiente acción genere un punto o no.
*/
   virtual bool run(blackboard *data) override;
};