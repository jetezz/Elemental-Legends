#pragma once

#include "motor_grafico/vector3d.hpp"
#include "motor_grafico/mynode.hpp"

#include"entity/gameObject.hpp"

class cofre : public gameObject {

    public:
    
    //FUNCIONES
    cofre();
    bool efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    void crearArmaAgua(std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    void crearArmaAire(std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    void crearArmaFuego(std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    void crearArmaTierra(std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    void crearPowerVida(std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    bool isPickeable() override; //Devuelve true o false si es un objeto recogible.


    //get
    uint8_t& getTipo();

    //set
    void settipo(uint8_t tip);

    private:

    //VARIABLES
    uint8_t tipo;
    void (cofre::*punteroCrearPowerup[6])(std::vector<unique_ptr <gameObject>> &ArrayGameObject);                                                                             //delegado tengo las funciones de todos los crear 
    
};
