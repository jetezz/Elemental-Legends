#pragma once

#include <memory>
#include "../entity/entity.hpp"
#include "../entity/balas/bala.hpp"
#include "../entity/gameObject.hpp"
/*

La blackboard es una tabla que contiene datos del juego que
será usada por la IA de los bots para gestionar sus datos.

*/

struct blackboard{
    blackboard(entity* bot): b_bot(bot) {};

    public:

    //Lista con todas las entidades
    static std::vector<std::unique_ptr<entity>>* entidades;
    //Lista con todas las balas
    static std::vector<std::unique_ptr<bala>>* balas;
    //Lista con los puntos que han hecho ruido
    static std::unique_ptr<std::vector<vector3d>> PuntosEscuchados;
    //Lista con los cofres
    static std::vector<std::unique_ptr<gameObject>>* pickeables;

    //El bot poseedor de la ia
    entity* b_bot;

    //El enemigo más cercano dentro del rango
    entity* b_closestEnemyInRange = nullptr;

    //El angulo con el enemigo mas cercano
    float anguloClosestEnemy {0};
    //Distancia al enemigo más cercano
    float closestEnemyDistance {};

    //Si estoy atacando a un objetivo no actualizaré el enemigo más cercano, para que se centre en el objetivo actual
    bool atacando = false;
    

    //Si el enemigo al que atacamos está lejos/cerca del disparo habra que acercarse o alejarse
    bool Acercarse = false;
    bool Alejarse = false;

    //La rotacion a el siguiente punto que mirará el BOT
    vector3d rotacionaPuntoaMirar {};

    //El punto al que se moverá el bot
    vector3d wayPoint {};
    
    static void setEntities(std::vector<std::unique_ptr<entity>>* ent); //Hace que la lista de entidades sea la misma que en ingame
    static void setPickeables(std::vector<std::unique_ptr<gameObject>>* ent);    //Hace que la lista de cofres/powerups sea la misma que en ingame
    static void setBalas(std::vector<std::unique_ptr<bala>>* ent);      //Hace que la lista de balas sea la misma que la de ingame
    static void addPuntoEscuchado(vector3d punto);                      //Añade un punto en el que se generó ruido
    static void clearPuntosEscuchados();                                //Limpia los puntos donde hubo ruido
};
