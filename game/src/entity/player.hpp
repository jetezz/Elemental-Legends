#pragma once

#include "entity.hpp"
#include "hud.hpp"
#include "ConstantesEfectosIngame.hpp"



class arma;
class vector3d;
class player : public entity{

    public:

    //FUNCIONES
    
    player(vector3d pos, int i);
    
    //void lesslife(int damage);
    //void heal(int laifu);
    void calcularVelocidad(float &frame);
    void consecuenciasIngame(int option);
    void moveTo(vector3d pos) override;
    bool hasWaypointToMove();
    void removeWaypoint();
    void setWaypoint();
    vector3d& getWayPoint();



    //todas las consecuencias ingame
    void actualizarArmaNeutral();
    void actualizarArmaAgua();
    void actualizarArmaAire();
    void actualizarArmaFuego();
    void actualizarArmaTierra();
    void actualizarPowerVida();
    void actualizarTier();    
    void colocarMensajePulsaE();
    void quitarMensajePulsaE();
    void actualizarCargador();
    void curarPlayer();
    void actualizarVida();
    bool checkIfOpenChest();    //Se comprueba si abre el cofre o no. En caso de jugador tiene que pulsar E. En caso de enemigo lo abre siempre.
    bool isPlayer() override;


    //GETTERS
   
   

    
    //SETTERS    
   

    //variables

    hud hudPlayer;
    void (player::*punteroConsecuenciasIngame[TotalConsecuencias])();                                                                             //delegado con todas las funciones de las consecuencias 

    //eleccion del personaje
  
    //constantes

    private:

    //FUNCIONES
    

    //VARIABLES
   

    //CONSTANTES

};



