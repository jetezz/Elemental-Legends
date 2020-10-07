#pragma once

#include "motor_grafico/vector3d.hpp"
#include "motor_grafico/mynode.hpp"

#include"entity/gameObject.hpp"
#include"entity/entity.hpp"
#include "../../motor_sonido/audio.hpp"

static CAudioEngine audio;
enum characters{AirCharacter, FireCharacter, GroundCharacter, LightCharacter, OscurityCharacter, WaterCharacter};

class powerUp : public gameObject {

    public:
    
    //FUNCIONES
   
    bool efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    bool isPickeable() override; //Devuelve true o false si es un objeto recogible.

    virtual void efectoPowerUp(entity &enti)=0;

    //get
   
    int gettipo();

    

    //set
   
    void settipo(int tip);

    //constantes
    
    static const int tipoArmaAgua       {1};
    static const int tipoArmaAire       {2};
    static const int tipoArmaFuego      {3};
    static const int tipoArmaTierra     {4};
    static const int tipoVida           {5};
    static const int HitBoxPowerUp      {10};
    private:

    //VARIABLES
    
   
   int tipo;



    


};
