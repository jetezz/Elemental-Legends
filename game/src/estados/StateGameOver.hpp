#pragma once

#include "State.hpp"
#include "estadisticas.hpp"

class StateGameOver : public State
{

public:

  
    
    virtual void init();
    virtual void input(StateMachine *stados);

    virtual void update(float deltaTime);
    virtual void render(float percentick);
 
    bool primeraVez {false};
    bool dibujado {false};
    estadisticas estadistic;


};


