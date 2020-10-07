#pragma once
#include "estadisticas.hpp"

#include <memory>


class State;
//MAQUINA DE ESTADOS ESTA CLASE MANEJA LOS ESTADOS
class StateMachine
{
public:

    StateMachine();
    ~StateMachine();
  

    State &getActualState() { return *estadoActual; }
    void setMenuState();        //Establece el estado Menu
    void setIngameState();      //Establece el estado Ingame
    void setGameOverState();    //Establece el estado Game Over
    void setInitState();        //Establece el estado Inicio juego
    void setCharacterSelectionState();        //Establece el estado Eleccion del personaje
    bool isGameOver();          //Devuelve true si el estado actual es game over
    bool isMenu();              //Devuelve true si el estado actual es Menu
    bool isIngame();            //Devuelve true si el estado actual es ingame
    bool isIniciojuego();       //Devuelve true si el estado actual es iniciojuego
    bool isCharacterSelection();       //Devuelve true si el estado actual es seleccion de personaje
    void update(float deltaTime);              //updatea el estado actual
    void render(float percentick);              //Renderiza el estado actual
 
    void input(StateMachine *stados);//para acceder al imput de los estados

    estadisticas &getEstadisticas() {return estadistic;};
    void setEstadiscitas(estadisticas est){estadistic=est;};
private:
//State* estadoActual;
std::unique_ptr<State> estadoActual;

estadisticas estadistic;
};

