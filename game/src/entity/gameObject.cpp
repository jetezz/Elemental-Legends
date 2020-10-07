#include "entity/gameObject.hpp"
#include "entity/entity.hpp"
#include "CONSTANTES.hpp"
#include "motor_fisicas/fisicas.hpp"




void gameObject::actualizarPercentick(float percentick){

    if(percentick<1){
    float posicionMediaX=0;
    float posicionMediaY=0;
    float posicionMediaZ=0;

    
    posicionMediaX=getpositionLast().X*(1-percentick)+getposition().X*percentick;
    posicionMediaY=getpositionLast().Y*(1-percentick)+getposition().Y*percentick;
    posicionMediaZ=getpositionLast().Z*(1-percentick)+getposition().Z*percentick;
    
    float rotacionMediaX=0;
    float rotacionMediaY=0;
    float rotacionMediaZ=0;

   
    rotacionMediaX=getRotationLast().X*(1-percentick)+getRotation().X*percentick;
    rotacionMediaY=getRotationLast().Y*(1-percentick)+getRotation().Y*percentick;
    rotacionMediaZ=getRotationLast().Z*(1-percentick)+getRotation().Z*percentick;



vector3d posicionMedia=vector3d(posicionMediaX,posicionMediaY,posicionMediaZ);
vector3d rotacionMedia=vector3d(rotacionMediaX,rotacionMediaY,rotacionMediaZ);

      fachada->cambiarPosicion(posicionMedia,getImage(),rotacionMedia);
    }
}
void gameObject::initPuntos(){
    puntos.resize(8);
    puntos=fisicas::getPuntos(posicion,hitbox, rotacionLast);
    region.reserve(4);
    region=fisicas::getRegiones(puntos);
    
}

///////
//GET//
///////

vector3d &gameObject::getposition(){
    return posicion;
}
vector3d &gameObject::getpositionLast(){
    return posicionLast;
}
MyNode_t &gameObject::getImage(){
    return Imagen;
}

vector3d &gameObject::getRotation(){
    return rotacion;
}
vector3d &gameObject::getRotationLast(){
    return rotacionLast;
}
vector3d &gameObject::getVelocidadRotacion(){
    return velocidadRotacion;
}
vector3d &gameObject::getHitBox(){
    return hitbox;
}
 std::chrono::time_point<std::chrono::system_clock> &gameObject::getTiempo(){
    return tiempo;
}
int gameObject::getPower(){
    return power;
}
vector<vector3d>& gameObject::getPuntos(){
    return puntos;
}
vector<vector2d> &gameObject::getRegion(){
    return region;
}
    




///////
//SET//
///////

void gameObject::setImage(MyNode_t& img){
    Imagen = img;
 }

 void gameObject::setPosition(vector3d vec){
    posicion=vec;
}
void gameObject::setPositionLast(vector3d vec){
    posicionLast=vec;
}


void gameObject::setRotation(vector3d vec){
    rotacion=vec;
}
void gameObject::setRotationLast(vector3d vec){
    rotacionLast=vec;
}
void gameObject::setVelocidadRotacion(vector3d vec){
    velocidadRotacion=vec;
}

void gameObject::setHitBox(vector3d vec){

    hitbox=vec;
  
}
void gameObject::setTiempo(std::chrono::time_point<std::chrono::system_clock> time){
    tiempo=time;
}
void gameObject::setPower(int num){
    power=num;
}
void gameObject::setPuntos(vector <vector3d> pun){
    puntos=pun;
}
void gameObject::setRegion(vector <vector2d> regi){
    region=regi;
}
