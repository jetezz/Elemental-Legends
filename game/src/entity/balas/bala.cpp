#include "entity/balas/bala.hpp"
#include "CONSTANTES.hpp"






bool bala::efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject){
    
    
    return efectoBala(enti);
}

//Devuelve true o false si es un objeto recogible.
bool bala::isPickeable(){ return false;}




//GETTERS
   
vector3d& bala::getvelocity(){

    return velocidad;
}
vector3d& bala::getvelocityI(){
    return velocidadI;
}
vector3d& bala::getpositionI(){
    return posicionI;
}
vector3d& bala::getGravedad(){
    return gravedad;
}
bool bala::getMuerte(){
    return muerte;
}
float&  bala::getDmg(){
    return dmg;
}
entity* bala::getEntidad(){
    return ent;
}
int bala::getTipo(){
    return tipo;
}




 //SETTERS         
void bala::setVelocity(vector3d vec){
    velocidad=vec;

}
void bala::setVelocityI(vector3d vec){
    velocidadI=vec;

}
void bala::setPositionI(vector3d vec){
    posicionI=vec;

}

void bala::setGravedad(vector3d vec){
    gravedad=vec;

}
void bala::setMuerte(bool muer){
    muerte=muer;
 }
void bala::setDmg(float dm){
    dmg=dm;
}
void bala::setEntidad(entity* entidad){
    ent=entidad;
}
void bala::setTipo(int tip){
    tipo=tip;
}