
#include "treeTask.hpp"

void treeTask::addChild(std::shared_ptr<treeTask> child){
   children.emplace_back(child);
}