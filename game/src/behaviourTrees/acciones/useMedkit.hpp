#pragma once

#include "../treeTask.hpp"

class blackboard;
struct useMedkit : public treeTask {

   //Acción de curarse los bots
   virtual bool run(blackboard *data) override;
    
};