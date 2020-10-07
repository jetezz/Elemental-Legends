
#include "playOnce.hpp"
#include "blackboard.hpp"

bool playOnce::run(blackboard *data){
    if(firstTime) {
          firstTime = false;
          return child->run(data);
      }
    return false;
}