#include "entity/cofre.hpp"
#include "entity/entity.hpp"
#include "input.hpp"
#include "entity/powerUp/powerArmaAgua.hpp"
#include "entity/powerUp/powerArmaAire.hpp"
#include "entity/powerUp/powerArmaFuego.hpp"
#include "entity/powerUp/powerArmaTierra.hpp"
#include "entity/powerUp/powerVida.hpp"
#include "../CONSTANTES.hpp"
#include "../motor_sonido/audio.hpp"


cofre::cofre(){

    punteroCrearPowerup [1] =&cofre::crearArmaAgua;
    punteroCrearPowerup [2] =&cofre::crearArmaAire;
    punteroCrearPowerup [3] =&cofre::crearArmaFuego;
    punteroCrearPowerup [4] =&cofre::crearArmaTierra;
    punteroCrearPowerup [5] =&cofre::crearPowerVida;
    setPower(0);




    int tip =rand()%5;
    tip++;
 
    int v1 = rand()%radioSpawnCofres;
   
    int v3 = rand()%radioSpawnCofres;

    int s1 = rand()%50;
  
    int s3 = rand()%50;

    if(s1 % 2){
        v1 = -v1;
    }

  

    if(s3 % 2){
        v3 = -v3;
    }

    float v2=2.5;
   
   
    setPosition(vector3d (v1, v2, v3));
    getImage().initCofre(this->getposition(),true);
     
    setHitBox(vector3d(13,10,15)) ; 
    initPuntos();
    
    tipo=tip;

    //std::cout << "COFRE CREADO" << endl;
    //std::cout << v1 << "\n" << v2 << "\n" << v3 << endl;
}


bool cofre::efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject){
    
    
    if(enti.checkIfOpenChest()){//llamo al input para comprobar si esta pulsando la e
       if(enti.isPlayer()){
            audio.PlayEvent("event:/Efectos/Abrir Cofre");
    	    audio.Update();
       }
       
        (this->*punteroCrearPowerup[tipo])(ArrayGameObject);        //cuando lo abro creo el objeto que tiene el cofre dependiendo del tipo
        return true; //el cofre se abre
    }

       
    return false; //el corfre no se abre

}

//Devuelve true o false si es un objeto recogible.
bool cofre::isPickeable(){
    return true;
}

void cofre::crearArmaAgua(std::vector<unique_ptr <gameObject>> &ArrayGameObject){
    unique_ptr<powerArmaAgua> aux = make_unique<powerArmaAgua>(getposition());
        ArrayGameObject.emplace_back(std::move(aux));
}
void cofre::crearArmaAire(std::vector<unique_ptr <gameObject>> &ArrayGameObject){
     unique_ptr<powerArmaAire> aux = make_unique<powerArmaAire>(getposition());
        ArrayGameObject.emplace_back(std::move(aux));
}
void cofre::crearArmaFuego(std::vector<unique_ptr <gameObject>> &ArrayGameObject){
     unique_ptr<powerArmaFuego> aux = make_unique<powerArmaFuego>(getposition());
        ArrayGameObject.emplace_back(std::move(aux));
}
void cofre::crearArmaTierra(std::vector<unique_ptr <gameObject>> &ArrayGameObject){
     unique_ptr<powerArmaTierra> aux = make_unique<powerArmaTierra>(getposition());
        ArrayGameObject.emplace_back(std::move(aux));
}
void cofre::crearPowerVida(std::vector<unique_ptr <gameObject>> &ArrayGameObject){
     unique_ptr<powerVida> aux = make_unique<powerVida>(getposition());
        ArrayGameObject.emplace_back(std::move(aux));
}


//get
uint8_t& cofre::getTipo(){

return tipo;
}



//set

void cofre::settipo(uint8_t tip){

}