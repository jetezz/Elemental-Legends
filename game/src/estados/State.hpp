#pragma once

#include "motor_grafico/fachadaIrrlicht.hpp"
#include "motor_sonido/audio.hpp"
#include "estadisticas.hpp"


//bjarne the cpp languaje
//A tour of c++ second edition 
// Tambine el lbro de principiantes principles and practice using c++ second edition

class StateMachine;
//Clase padre de estados

class State
{
    
public:

    State();
    virtual ~State() = default;
    virtual void init() = 0;
    virtual void input(StateMachine *stados) = 0;

    virtual void update(float deltaTime) = 0;
    virtual void render(float pecentick) = 0;

    fachadaIrrlicht * fachada;
    CAudioEngine audio;
     int option {0};// para controlar las opciones del menu las opciones validas son de 1 a 3
    static int character;
     
    
private:
    

};


 