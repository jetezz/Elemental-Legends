#include "StateGameOver.hpp"
#include "estados/StateMachine.hpp"
#include "input.hpp"

//Estado de juego



void StateGameOver::init()
{

}


void StateGameOver::input(StateMachine *stados)
{
  if(!primeraVez){
  estadistic=stados->getEstadisticas();
  primeraVez=true;
  }
  if(check_intro()){      
       stados->setMenuState();
    }
    primeraVez=true;
}

void StateGameOver::update(float deltaTime)
{          
    fachada->createGameOver(estadistic.tiempo,estadistic.muertes,estadistic.victoria);   
  
}

void StateGameOver::render(float percentick)
{
 
  
  
   fachada->driver->beginScene(true, true, irr::video::SColor(255,113,113,133));
  fachada->smgr->drawAll();
  fachada->background->drawAll();
  fachada->driver->endScene();
}