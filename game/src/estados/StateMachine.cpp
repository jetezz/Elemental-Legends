#include "StateMachine.hpp"
#include "State.hpp"
#include "StateMenu.hpp"
#include "StateIngame.hpp"
#include "StateGameOver.hpp"
#include "StateIniciojuego.hpp"
#include "StateCharacterSelection.hpp"


using namespace std;
StateMachine::StateMachine()
{   
    std::unique_ptr<StateIniciojuego> estado = make_unique<StateIniciojuego>();
    estadoActual = std::move(estado); 
    

}

StateMachine::~StateMachine()
{
    
}

void StateMachine::setMenuState(){
    
    std::unique_ptr<StateMenu> estado = make_unique<StateMenu>();
    estadoActual = std::move(estado);
    estadoActual->init();

   
}

void StateMachine::setIngameState(){

    std::unique_ptr<StateIngame> estado = make_unique<StateIngame>();
    estadoActual = std::move(estado);
    estadoActual->init();
}

void StateMachine::setGameOverState(){
    
    std::unique_ptr<StateGameOver> estado = make_unique<StateGameOver>();
    estadoActual = std::move(estado);
    estadoActual->init();

}

void StateMachine::setInitState(){
    
    std::unique_ptr<StateIniciojuego> estado = make_unique<StateIniciojuego>();
    estadoActual = std::move(estado);
    estadoActual->init();
   

}

void StateMachine::setCharacterSelectionState(){
    
    std::unique_ptr<StateCharacterSelection> estado = make_unique<StateCharacterSelection>();
    estadoActual = std::move(estado);
    estadoActual->init();
   

}

void StateMachine::update(float deltaTime){
    estadoActual->update(deltaTime);
}

void StateMachine::render(float percentick){
    estadoActual->render(percentick);
}

//Devuelve true si el estado actual es game over
bool StateMachine::isGameOver()
{
        if(dynamic_cast<StateGameOver*>(estadoActual.get()))
        return true;
    return false;
}  

 //Devuelve true si el estado actual es Menu      
bool StateMachine::isMenu()
{ 
        if(dynamic_cast<StateMenu*>(estadoActual.get()))
        return true;
    return false;
}
 //Devuelve true si el estado actual es Ingame  
bool StateMachine::isIngame()
{
        if(dynamic_cast<StateIngame*>(estadoActual.get()))
        return true;
    return false;
}
 //Devuelve true si el estado actual es Inicio juego
bool StateMachine::isIniciojuego()
{
        if(dynamic_cast<StateIniciojuego*>(estadoActual.get()))
        return true;
    return false;
}
 //Devuelve true si el estado actual es seleccion de personaje
bool StateMachine::isCharacterSelection()
{
        if(dynamic_cast<StateCharacterSelection*>(estadoActual.get()))
        return true;
    return false;
}
//para acceder a los input de los estados
void StateMachine::input(StateMachine *stados) {
    estadoActual->input(stados); 
}