#include "StateMenu.hpp"
#include <iostream>
#include "input.hpp"
#include "StateMachine.hpp"


//Estado del menu de juego



void StateMenu::init()
{
  //se muestran las opciones por consola
  std::cout << "========================" << std::endl;
	std::cout << "Pulsa Intro para iniciar" << std::endl;
	std::cout << "========================" << std::endl;

  std::cout << "1. Jugar" << std::endl;
  std::cout << "2. Créditos" << std::endl;
  std::cout << "3. Salir" << std::endl;

  opciones[0] = 1;
  opciones[1] = 2;
  opciones[2] = 3;
  
  option = 1; 

  fachada->crearinterfacemenu();//para poner imagen de fondo y las imagenes de los botones
  //fachada->selectOption(option);

  //audio.LoadEvent("event:/Música/Musica Menu");
  audio.StopEvent("event:/Ambientes/Ganar Partida");

  audio.PlayEvent("event:/Música/Musica Menu");
  audio.Update();
}


void StateMenu::input(StateMachine *stados)
{
  
    if(empezarjuego() && option==1){
        stados->setCharacterSelectionState();
    }else if(option==2){
        verCreditos();
    }else if(option==4){
        cerrar();
    }
}

void StateMenu::update(float deltaTime)
{
 // std::cout << "UPDATING MENU" << std::endl;
 
  setOption(selectmenuoption(option));//asignar una opcion
  fachada->selectOption(option);//mostrar la opcion seleccionada

  
}

void StateMenu::render(float percentick)
{
  fachada->driver->beginScene(true, true, irr::video::SColor(255,113,113,133));
  fachada->smgr->drawAll();
  fachada->background->drawAll();
  fachada->driver->endScene();
}

void StateMenu::setOption(int i){//asignar valor a la opcion
  if(i !=-1)
    option = i;
}

