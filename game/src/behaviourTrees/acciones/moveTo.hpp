#pragma once

#include "../treeTask.hpp"

class blackboard;
struct moveTo : public treeTask {

   //Pone el punto al que se va a mover con las fisicas
   virtual bool run(blackboard *data) override;
    
};