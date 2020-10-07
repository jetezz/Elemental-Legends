#include "player.hpp"
#include "hud.hpp"
#include "ConstantesEfectosIngame.hpp"
#include "CONSTANTES.hpp"
#include "../input.hpp"
#include "../motor_sonido/audio.hpp"

static CAudioEngine audio;

player::player(vector3d pos,int character){ 
  claseElemental = character;
  setPosition(pos);
  setPositionLast(pos);
  setRotation(vector3d(0,0,0)); 
  setTipo(jugador);
  getImage().initPlayer(pos,true);
  getImage().initImagen(getposition(),getRotation());  
  setHitBox(getImage().calcularHitBox()) ; 
  initPuntos();
  setVelocity(vector3d(0,0,0));
  setVidaTotal(vidaEntidades);
  setVida(vidaEntidades);
  setTiempo(std::chrono::system_clock::now());
  getArma().setEntidad(this);
/////////////////////////////
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
    actualizarVida();
    break;
  case LightCharacter:
 
    getArma().recargarPowerVida();
    actualizarPowerVida();
    break;
  case OscurityCharacter:
  
    getArma().recargarArmaTierra();
    actualizarArmaTierra();
    break;
  case WaterCharacter:
  
    getArma().recargarArmaAgua();
    actualizarArmaAgua();
    break;
default:
  break;
}


///////////////////////////////////
  

  punteroConsecuenciasIngame [ActualizarArmaNeutral] =&player::actualizarArmaNeutral;
  punteroConsecuenciasIngame [ActualizarArmaAgua] =&player::actualizarArmaAgua;
  punteroConsecuenciasIngame [ActualizarArmaAire] =&player::actualizarArmaAire;
  punteroConsecuenciasIngame [ActualizarArmaFuego] =&player::actualizarArmaFuego;
  punteroConsecuenciasIngame [ActualizarArmaTierra] =&player::actualizarArmaTierra;
  punteroConsecuenciasIngame [ActualizarArmaPowerVida] =&player::actualizarPowerVida;

  punteroConsecuenciasIngame [PonerMensajeHud] =&player::colocarMensajePulsaE;
  punteroConsecuenciasIngame [QuitarMensajeHud] =&player::quitarMensajePulsaE;
  punteroConsecuenciasIngame [ReajustarCargador] =&player::actualizarCargador;
  punteroConsecuenciasIngame [Curar] =&player::curarPlayer;
  punteroConsecuenciasIngame [ReajustarVida] =&player::actualizarVida;
  punteroConsecuenciasIngame [ReajustarTier] =&player::actualizarTier;


 
  
  }   



void player::calcularVelocidad(float &frame){

      
  
}

void player::moveTo(vector3d pos){}
bool player::hasWaypointToMove() {return true;}
void player::removeWaypoint()    {}
void player::setWaypoint()       {}
vector3d& player::getWayPoint(){return getposition();}

void player::consecuenciasIngame(int option){


  (this->*punteroConsecuenciasIngame[option])(); 
  
}
void player::actualizarArmaNeutral(){
  hudPlayer.actualizarArmaNeutral(getArma());
  actualizarTier();
}
void player::actualizarArmaAgua(){
  hudPlayer.actualizarArmaAgua(getArma());
  actualizarTier();
}
void player::actualizarArmaAire(){
  hudPlayer.actualizarArmaAire(getArma());
  actualizarTier();

}
void player::actualizarArmaFuego(){
  hudPlayer.actualizarArmaFuego(getArma());
  actualizarTier();

}
void player::actualizarArmaTierra(){
  hudPlayer.actualizarArmaTierra(getArma());
  actualizarTier();

}
void player::actualizarPowerVida(){
  hudPlayer.actualizarPowerVida(getArma());
  
}
void player::colocarMensajePulsaE(){
  hudPlayer.activarMensaje();
}
void player::quitarMensajePulsaE(){
  hudPlayer.desactivarMensaje();
}
void player::actualizarCargador(){
  hudPlayer.actualizarCargador(getArma().getMunicion().at(getArma().gettipo()));
}
void player::curarPlayer(){

  audio.PlayEvent("event:/Efectos/Cura");
  audio.Update();
  setVida(getlife()+curacionMedikit);
  
  actualizarPowerVida();
  actualizarVida();
  actualizarCargador();

}
void player::actualizarTier(){
 hudPlayer.actualizarTier(getArma().getTier());
}
void player::actualizarVida(){
  hudPlayer.actualizarVida(getlife());
}

bool player::isPlayer(){
  return true;
}
bool player::checkIfOpenChest(){
  
    return check_abrirCofre();

}    //Se comprueba si abre el cofre o no. En caso de jugador tiene que pulsar E. En caso de enemigo lo abre siempre.
