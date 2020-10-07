#include "StateCharacterSelection.hpp"
#include <iostream>
#include "input.hpp"
#include "StateMachine.hpp"

int State::character=0;

void StateCharacterSelection::init()
{
   //player
          
   

  std::cout << "==================================" << std::endl;
	std::cout << "Selecciona tu personaje para jugar" << std::endl;
	std::cout << "==================================" << std::endl;

  std::cout << "1. Aire" << std::endl;
  std::cout << "2. Fuego" << std::endl;
  std::cout << "3. Tierra" << std::endl;
  std::cout << "4. Luz" << std::endl;
  std::cout << "5. Oscuridad" << std::endl;
  std::cout << "6. Agua" << std::endl;

    personajes[0] = 0;//aire
    personajes[1] = 1;//fuego
    personajes[2] = 2;//tierra
    personajes[3] = 3;//luz
    personajes[4] = 4;//oscuridad
    personajes[5] = 5;//agua

    fachada->crearinterfacepersonajes();//crea la interfaz de escoger personaje

}


void StateCharacterSelection::input(StateMachine *stados)
{
    if(jugar()){
      //putCharacter(character);
      stados->setIngameState();
     
    }
}

void StateCharacterSelection::update(float deltaTime)
{
 // std::cout << "UPDATING GameOver" << std::endl;
 //selectcharacter(character);
 setCharacter(selectcharacter(character));
 fachada->selectCharacter(character);
 
}

void StateCharacterSelection::render(float percentick)
{
  fachada->driver->beginScene(true, true, irr::video::SColor(255,113,113,133));
  fachada->smgr->drawAll();
  fachada->background->drawAll();
  fachada->driver->endScene();
}

void StateCharacterSelection::setCharacter(int i){
  if(i!=-1){
    
    character = i;
    //std::cout << i << std::endl;
    
    
    }
    /*
  std::cout << "juas juas juas i'm" <<std::endl;
  std::cout << character<<std::endl;
    */
}

