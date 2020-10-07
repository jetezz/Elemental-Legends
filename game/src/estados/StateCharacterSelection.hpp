#pragma once



#include "State.hpp"

class StateCharacterSelection : public State
{

public:

  
    
    virtual void init();
    virtual void input(StateMachine *stados);

    virtual void update(float deltaTime);
    virtual void render(float percentick);
 
    void setCharacter(int i);
    

    int personajes[6];
    

    



};