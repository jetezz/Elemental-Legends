#pragma once

#include"entity/balas/bala.hpp"

class bala_tierra : public bala{


 public:

    //FUNCIONES
   
    bala_tierra(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo);
    virtual bool calcularVelocidad(float frame);
    bool efectoBala(entity & ent);
    //variables

    


    //constantes

    private:

    //FUNCIONES


    //VARIABLES   
    std::chrono::time_point<std::chrono::system_clock> tickDmg;
    

    //CONSTANTES
   
};