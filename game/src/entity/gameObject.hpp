#pragma once

#include "motor_grafico/mynode.hpp"
#include "motor_grafico/vector3d.hpp"
#include <memory>
#include <chrono>
#include <ctime>
#include "ConstantesEfectosIngame.hpp"
#include "motor_fisicas/vector2d.hpp"

class bala;
class entity;

class gameObject{

    public:

    //FUNCIONES
            
    virtual bool efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject)=0;//efectoColision es una funcion virtualPura  que dependiendo del objeto con el que chocas (caja,powerup,entity) realice una accion o otra
    virtual bool isPickeable()=0; //Devuelve true o false si es un objeto recogible.
   
    
    
    void actualizarPercentick(float percentick);    
    void initPuntos();

    //GETTERS
   
    vector3d &getposition();
    vector3d &getpositionLast();
    vector3d &getVelocidadRotacion();
    vector3d &getRotation();
    vector3d &getRotationLast();
    MyNode_t &getImage();
    vector3d &getHitBox();
    std::chrono::time_point<std::chrono::system_clock> &getTiempo();
    int getPower();
    vector<vector3d> &getPuntos();
    vector <vector2d> &getRegion();
   
    //SETTERS

    void setPosition(vector3d vec);
    void setPositionLast(vector3d vec);
    void setImage(MyNode_t& img);
    void setRotation(vector3d vec);
    void setRotationLast(vector3d vec);
    void setVelocidadRotacion(vector3d vec);
    void setHitBox(vector3d vec);
    void setTiempo(std::chrono::time_point<std::chrono::system_clock> time);
    void setPower(int num);
    void setPuntos(vector <vector3d> puntos);
    void setRegion(vector <vector2d> regiones);
    
    //variables
    vector3d transfor{vector3d(1,1,1)};

    //constantes
    
   




    

    private:

    //FUNCIONES


    //VARIABLES
   
    vector3d posicion;
    vector3d posicionLast;
    vector3d rotacion;
    vector3d rotacionLast;
    vector3d velocidadRotacion;
    MyNode_t Imagen;
    vector3d hitbox;    
    std::chrono::time_point<std::chrono::system_clock> tiempo;   
    static std::chrono::time_point<std::chrono::system_clock> start2;
    int power               {NoEsUnPowerUp};  //indica el powerUp que es en caso de que lo sea
    fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
    vector <vector3d> puntos {};
    vector <vector2d> region;    
    //CONSTANTES
    const static int NoHayColision {-1};
    
};
  
 