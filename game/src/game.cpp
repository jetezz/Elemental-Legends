#include "game.hpp"

#include "input.hpp"
#include <iostream>
#include <algorithm> 
#define SENSIBILIDAD 3


//static int actualFPS {0};  //Los fps actuales del juego


game::game(){


//Crear el device
fachada->crearPantalla();
nowTime = std::chrono::system_clock::now();
oldTime = std::chrono::system_clock::now();


}

void game::start(){
srand(time(NULL));  //Sirve para crear los cofres en posiciones aleatorias




//Establecer el estado actual, en un principio ingame luego se cambiara
estados->setInitState();
const int maxFPSlogica {40}; //Numero de frames por seconds
const int maxFPSRender {60}; //Numero de frames por seconds





while(fachada->device->run()){


//CONTADOR DE FPS
if(std::chrono::system_clock::now()-tiempo >std::chrono::milliseconds(1000)){
  
  cout<<"FPS UPDATE"<<contador<<endl;
  cout<<"FPS RENDER"<<contadorRender<<endl;

  contador=0;
  contadorRender=0;
  tiempo=std::chrono::system_clock::now();
  
}

nowTime = std::chrono::system_clock::now();
std::chrono::duration<float,std::ratio<1,1>> tiem=nowTime-oldTime;
std::chrono::duration<float,std::ratio<1,1>> tiem2=nowTime-oldRenderTime;

//cout<<"tiempo"<<tiem.count()<<endl;
deltaTime=tiem.count();



//LIMITACION DE FPS EN EL UPDATE
if(tiem >std::chrono::milliseconds(1000/maxFPSlogica)){
  //cout<<"tiempo"<<tiem.count()<<endl;
  estados->input(estados.get());//acceder a input de los estados
    
  oldTime = std::chrono::system_clock::now();
  contador++;
  estados->update(deltaTime);
  
}

if(tiem2 >std::chrono::milliseconds(1000/maxFPSRender)){
contadorRender++;
percentick=min(1.f,(deltaTime*1000)/(1000/maxFPSlogica));
//cout<<"percentick"<<percentick<<endl;
  oldRenderTime = std::chrono::system_clock::now();

estados->render(percentick);
}


check_close();

}

 
    fachada->device->drop();

}