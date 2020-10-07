#pragma once

#include "../treeTask.hpp"

class blackboard;
struct hasAmmo : public treeTask {

public:
/*
   Comprueba si el bot tiene munición suficiente para atacar.
*/
   virtual bool run(blackboard *data) override;
};