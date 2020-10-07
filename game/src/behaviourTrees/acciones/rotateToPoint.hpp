#pragma once

#include "../treeTask.hpp"

class blackboard;
struct rotateToPoint : public treeTask {


   virtual bool run(blackboard *data) override;
    
};