#pragma once

#include "../treeTask.hpp"

class blackboard;
struct shotTask : public treeTask {


   virtual bool run(blackboard *data) override;
    
};