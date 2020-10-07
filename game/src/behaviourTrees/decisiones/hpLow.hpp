#pragma once

#include "../treeTask.hpp"

class blackboard;
struct hpLow : public treeTask {

public:
/*
   Comprueba si el bot tiene poca vida.
*/
   virtual bool run(blackboard *data) override;
};