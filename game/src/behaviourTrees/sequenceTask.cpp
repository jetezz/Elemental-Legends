
#include "sequenceTask.hpp"
#include "blackboard.hpp"

bool sequenceTask::run(blackboard *data){
   for(std::shared_ptr<treeTask> child : children){
     // cout << "tirando sequencia"  << children.size() << endl;
      if(!child->run(data))
      return false;
   }
   return true;
}
