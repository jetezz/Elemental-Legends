
#include "blackboard.hpp"

std::vector<std::unique_ptr<entity>>* blackboard::entidades = nullptr;
std::vector<std::unique_ptr<bala>>* blackboard::balas = nullptr;
std::vector<std::unique_ptr<gameObject>>* blackboard::pickeables = nullptr;
std::unique_ptr<std::vector<vector3d>> blackboard::PuntosEscuchados = make_unique<std::vector<vector3d>>();

void blackboard::setEntities(std::vector<std::unique_ptr<entity>>* ent){
    if(ent!=nullptr) 
    blackboard::entidades = ent;
}
void blackboard::setPickeables(std::vector<std::unique_ptr<gameObject>>* ent){
    if(ent!=nullptr) 
    blackboard::pickeables = ent;
}
void blackboard::setBalas(std::vector<std::unique_ptr<bala>>* ent){
    if(ent!=nullptr) 
    blackboard::balas = ent;
}

void blackboard::addPuntoEscuchado(vector3d puntoEscuchado){
    PuntosEscuchados->push_back(puntoEscuchado);
}

void blackboard::clearPuntosEscuchados(){
    PuntosEscuchados->clear();
}