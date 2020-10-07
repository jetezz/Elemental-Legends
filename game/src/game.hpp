

#include <iostream>
#include "motor_grafico/fachadaIrrlicht.hpp"
#include "estados/StateMachine.hpp"
#include <memory>
#include <chrono>

#define SENSIBILIDAD 3



class vertor3d;
class game{

public:

//FUNCIONES
game();         //constructor
void start();
//VARIABLES
//Se crea la maquina de estados con la que cambiar los estados
std::unique_ptr<StateMachine> estados = make_unique<StateMachine>();

//CONSTANTES


private:

//FUNCIONES


//VARIABLES

std::chrono::time_point<std::chrono::system_clock> nowTime, oldTime,oldRenderTime;

float deltaTime {0}; // Acumulación de deltaTime
float percentick {0};
int contador{0};
int contadorRender{0};
float gameTime {0}; //tiempo de juego
std::chrono::time_point<std::chrono::system_clock> tiempo; 
//Se llama a la fachada de modo Singleton
fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();


//CONSTANTES


};



