
#include "Limit.hpp"
#include "blackboard.hpp"

bool Limit::run(blackboard *data){
    if(intentos >= runLimit) return false;
    
    intentos++;
    return child->run(data);
}