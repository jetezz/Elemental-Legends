#pragma once

#include"entity/balas/bala.hpp"

class bala_agua : public bala{


 public:

    //FUNCIONES
   
    bala_agua(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo);
    virtual bool calcularVelocidad(float frame);
    bool efectoBala(entity & ent);
    //variables

    


    //constantes

    private:

    //FUNCIONES


    //VARIABLES
   
  
    

    //CONSTANTES

};