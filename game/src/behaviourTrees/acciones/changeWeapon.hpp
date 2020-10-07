#pragma once

#include "../treeTask.hpp"
/*
*Cambia el arma a la más atractiva disponible
*/

class blackboard;
struct changeWeapon : public treeTask {


   virtual bool run(blackboard *data) override;
    
};