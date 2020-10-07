#include "entity/powerUp/powerUp.hpp"
#include "entity/entity.hpp"
#include "input.hpp"
#include "../../motor_sonido/audio.hpp"


bool powerUp::efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject){
    
 if(enti.checkIfOpenChest()){
        
        if(enti.isPlayer()){
 	        audio.PlayEvent("event:/Efectos/Mejora de Arma");
    	    audio.Update();
        }
      
        efectoPowerUp(enti);
       
        return true; //el cofre se abre
    }

       
    return false; //el corfre no se abre
}

//Devuelve true o false si es un objeto recogible.
bool powerUp::isPickeable(){
    return true;
}


////get

int powerUp::gettipo(){
    return tipo;
}



////set


void powerUp::settipo(int tip){
    tipo=tip;
}