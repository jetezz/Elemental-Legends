#pragma once

#include "entity.hpp"



class arma;
class vector3d;
class enemy : public entity{

    public:

    //FUNCIONES
    enemy();
    enemy(vector3d pos,vector3d hit, int i);
    
    
    void calcularVelocidad(float &frame);
    void consecuenciasIngame(int option);


    void moveTo(vector3d pos) override;
    bool hasWaypointToMove();
    void removeWaypoint();
    void setWaypoint();
    bool checkIfOpenChest();    //Se comprueba si abre el cofre o no. En caso de jugador tiene que pulsar E. En caso de enemigo lo abre siempre.
    bool isPlayer() override;
   // std::unique_ptr<ManagerCharacter> personaje = make_unique<ManagerCharacter>();
  //GETTERS
     
    vector3d& getWayPoint();
   

    
    //SETTERS    
    
    

    //variables

    


    //constantes

    private:

    
    
    //VARIABLES
    int ia{0};
    vector3d nextWaypoint {};
    bool hasWaypoint = false;
    //CONSTANTES
};

