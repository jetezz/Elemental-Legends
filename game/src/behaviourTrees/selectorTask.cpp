
#include "selectorTask.hpp"
#include "blackboard.hpp"

bool selectorTask::run(blackboard *data){
 //  cout << "selecting " << endl;
   for(std::shared_ptr<treeTask> child : children){
      if(child->run(data))
      return true;
   }
   return false;
}
