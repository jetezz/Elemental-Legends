#pragma once

#include "State.hpp"

//ESTADO DE MAIN MENU

class StateMenu : public State
{

public:

    
    virtual void init();
    virtual void input(StateMachine *stados);

    virtual void update(float deltaTime);
    virtual void render(float percentick);
 
    void setOption(int i);//asignar valor a la variable opcion

private:
    int opciones[3];//array con las diferentes opciones del menu
};

