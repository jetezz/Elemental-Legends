#include "StateIniciojuego.hpp"
#include <iostream>
#include "input.hpp"
#include "StateMachine.hpp"


//Estado de inicio



void StateIniciojuego::init()
{
 ///////////////////////////////////////////
    //prueba con musica
    /////////////////////////////////////////
    audio.Init();

    audio.LoadBank("src/motor_sonido/bancos/Master.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);
    audio.LoadBankStrings("src/motor_sonido/bancos/Master.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL);

    LoadEvents();
    ////////////////////////////////////////////////

  std::cout << "========================" << std::endl;
	std::cout << "Pulsa Enter para iniciar" << std::endl;
	std::cout << "========================" << std::endl;
   
  fachada->crearinterfaceinicio();//para pner imagen de fondo, despues sera un video

}


void StateIniciojuego::input(StateMachine *stados)
{
  fachada->crearinterfaceinicio2();//para pner imagen de fondo, despues sera un video
  if(iniciarjuego()){
        stados->setMenuState();  
    }
  
}

void StateIniciojuego::update(float deltaTime)
{
 // std::cout << "UPDATING MENU" << std::endl;
 
  
}

void StateIniciojuego::render(float percentick)
{
  fachada->driver->beginScene(true, true, irr::video::SColor(255,113,113,133));
  fachada->smgr->drawAll();
  fachada->background->drawAll();
  fachada->driver->endScene();

}

void StateIniciojuego::LoadEvents(){

  audio.LoadEvent("event:/Ambientes/Ambiente Juego");
  audio.LoadEvent("event:/Ambientes/Ganar Partida");
  audio.LoadEvent("event:/Efectos/Abrir Cofre");
  audio.LoadEvent("event:/Efectos/Cura");
  audio.LoadEvent("event:/Efectos/Disparo Agua");
  audio.LoadEvent("event:/Efectos/Disparo Aire");
  audio.LoadEvent("event:/Efectos/Disparo Default");
  audio.LoadEvent("event:/Efectos/Disparo Fuego");
  audio.LoadEvent("event:/Efectos/Disparo Tierra");
  audio.LoadEvent("event:/Efectos/Kill");
  audio.LoadEvent("event:/Efectos/Mejora de Arma");
  audio.LoadEvent("event:/Efectos/Movimiento Normal");
  audio.LoadEvent("event:/Efectos/Sonido Impacto Proyectil");
  audio.LoadEvent("event:/Menús/Cambio de Opciones en Menu");
  audio.LoadEvent("event:/Menús/Seleccion Opcion");
  audio.LoadEvent("event:/Música/Musica Menu");
  audio.LoadEvent("event:/Voces/Personaje Agua/Agua cura o mejora");
  audio.LoadEvent("event:/Voces/Personaje Agua/Agua en Racha");
  audio.LoadEvent("event:/Voces/Personaje Agua/Agua mata a Fuego");
  audio.LoadEvent("event:/Voces/Personaje Agua/Agua Muere");
  audio.LoadEvent("event:/Voces/Personaje Agua/Agua recibe danyo");
  audio.LoadEvent("event:/Voces/Personaje Aire/Aire cura o mejora");
  audio.LoadEvent("event:/Voces/Personaje Aire/Aire en Racha");
  audio.LoadEvent("event:/Voces/Personaje Aire/Aire Mata a Tierra");
  audio.LoadEvent("event:/Voces/Personaje Aire/Aire Muere");
  audio.LoadEvent("event:/Voces/Personaje Aire/Aire recibe danyo");
  audio.LoadEvent("event:/Voces/Personaje Fuego/Fuego cura o mejora");
  audio.LoadEvent("event:/Voces/Personaje Fuego/Fuego en Racha");
  audio.LoadEvent("event:/Voces/Personaje Fuego/Fuego mata a otro de fuego");
  audio.LoadEvent("event:/Voces/Personaje Fuego/Fuego Muere");
  audio.LoadEvent("event:/Voces/Personaje Fuego/Fuego recibe danyo");
  audio.LoadEvent("event:/Voces/Personaje Luz/Luz cura o mejora");
  audio.LoadEvent("event:/Voces/Personaje Luz/Luz en Racha");
  audio.LoadEvent("event:/Voces/Personaje Luz/Luz mata a Oscuridad");
  audio.LoadEvent("event:/Voces/Personaje Luz/Luz Muere");
  audio.LoadEvent("event:/Voces/Personaje Luz/Luz recibe danyo");
  audio.LoadEvent("event:/Voces/Personaje Oscuridad/Oscuridad cura o mejora");
  audio.LoadEvent("event:/Voces/Personaje Oscuridad/Oscuridad en Racha");
  audio.LoadEvent("event:/Voces/Personaje Oscuridad/Oscuridad mata a Luz");
  audio.LoadEvent("event:/Voces/Personaje Oscuridad/Oscuridad Muere");
  audio.LoadEvent("event:/Voces/Personaje Oscuridad/Oscuridad recibe danyo");
  audio.LoadEvent("event:/Voces/Personaje Tierra/Tierra cura o mejora");
  audio.LoadEvent("event:/Voces/Personaje Tierra/Tierra en Racha");
  audio.LoadEvent("event:/Voces/Personaje Tierra/Tierra mata a otra Tierra");
  audio.LoadEvent("event:/Voces/Personaje Tierra/Tierra Muere");
  audio.LoadEvent("event:/Voces/Personaje Tierra/Tierra recibe danyo");

}