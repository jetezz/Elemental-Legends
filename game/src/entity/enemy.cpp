#include "enemy.hpp"
#include "CONSTANTES.hpp"


enemy::enemy(){

}

enemy::enemy(vector3d pos,vector3d hit, int character){
    claseElemental = character;
    setPosition(pos);
    setPositionLast(pos);
    setRotation(vector3d(0,0,0));
    setTipo(enemigo);
    getImage().initEnemy(pos,true); 
    getImage().initImagen(getposition(),getRotation());  
    setHitBox(getImage().calcularHitBox()) ; 
    initPuntos();
    setVelocity(vector3d(0,0,0));
    setVidaTotal(vidaEntidades);
    setVida(vidaEntidades);
    setTiempo(std::chrono::system_clock::now());
switch (character)
{
  case AirCharacter:
  
    velocidadextra = 1.15;
    setVelocity(getvelocity());//mas velocidad
    break;
  case FireCharacter:
   
   
    setDanyo(1.2);
    break;
  case GroundCharacter:
 
    setVidaTotal(vidaEntidades+10);//mas vida
    setVida(vidaEntidades+10);
    //actualizarVida();
    break;
  case LightCharacter:
 
    getArma().recargarPowerVida();
    
    break;
  case OscurityCharacter:
 
    getArma().recargarArmaTierra();
   
    break;
  case WaterCharacter:
  
    getArma().recargarArmaAgua();

    break;
default:
  break;
}
    //////////////////////////

   
    
}
vector3d& enemy::getWayPoint(){
    return nextWaypoint;
}

bool enemy::hasWaypointToMove(){
    return hasWaypoint;
}
void enemy::removeWaypoint(){
    hasWaypoint = false;
    nextWaypoint = getposition();
}
void enemy::setWaypoint(){
    hasWaypoint = true;
}
void enemy::moveTo(vector3d pos){

    auto dx = pos.X - getposition().X;
    auto dz = pos.Z - getposition().Z;
    auto rotacion = vector3d(0,-atan2f(-dx,dz)*180/PI,0);
    setRotation(rotacion);
    nextWaypoint = pos;

   // cout << "x" << pos.X << endl;
   // cout << "z" << pos.Z << endl;

}




void enemy::calcularVelocidad(float &frame){
    
    if(hasWaypoint){
        getvelocity().Z = MOVEMENT_SPEED*cos(getRotation().Y*PI/180);
		getvelocity().X = MOVEMENT_SPEED*sin(getRotation().Y*PI/180);
    }else{
        getvelocity().X = 0;
        getvelocity().Y = 0;
        getvelocity().Z = 0;
    }

    /*
    *Si el bot tiene que acercarse o alejarse se moverá en la dirección indicada.
    */
    if(getData()->Acercarse || getData()->Alejarse) setVelocity(vector3d(0,0,0));
    if(getData()->Acercarse){
        getvelocity().Z += MOVEMENT_SPEED*cos(getRotation().Y*PI/180);
		getvelocity().X += MOVEMENT_SPEED*sin(getRotation().Y*PI/180);
    }
    if(getData()->Alejarse){
        getvelocity().Z -= MOVEMENT_SPEED*cos(getRotation().Y*PI/180);
		getvelocity().X -= MOVEMENT_SPEED*sin(getRotation().Y*PI/180);
    }
    
}

void enemy::consecuenciasIngame(int option){


}


bool enemy::checkIfOpenChest() { return true; }
bool enemy::isPlayer() { return false; }