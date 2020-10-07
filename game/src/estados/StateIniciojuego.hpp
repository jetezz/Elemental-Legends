#pragma once

#include "State.hpp"


//ESTADO DE MAIN MENU

class StateIniciojuego : public State
{

public:
 
    
    virtual void init();
    virtual void input(StateMachine *stados);

    virtual void update(float deltaTime);
    virtual void render(float percentick);

    void LoadEvents();
    
    
    



};