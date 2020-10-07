#pragma once

#include "../treeTask.hpp"

class blackboard;
struct hasMedkit : public treeTask {

public:
/*
   Comprueba si el bot tiene un kit de vida.
*/
   virtual bool run(blackboard *data) override;
};