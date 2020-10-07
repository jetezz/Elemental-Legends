#pragma once

#include"entity/balas/bala.hpp"

class bala_fuego : public bala{


 public:

    //FUNCIONES
    
    bala_fuego(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo);
    virtual bool calcularVelocidad(float frame);
    bool efectoBala(entity & ent);
    //variables

    


    //constantes

    private:

    //FUNCIONES


    //VARIABLES
   
  
    

    //CONSTANTES
    const int64_t accion1 {500};    
    std::chrono::time_point<std::chrono::system_clock> tickDmg;
    std::chrono::time_point<std::chrono::system_clock> reduccionHit;

    int tamano{200};
};