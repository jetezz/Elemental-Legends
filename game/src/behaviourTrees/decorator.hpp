#pragma once



#include "treeTask.hpp"


struct decorator : public treeTask{
   
   public:

   std::shared_ptr<treeTask> child;
};