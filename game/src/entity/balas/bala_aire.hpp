#pragma once

#include"entity/balas/bala.hpp"

class bala_aire : public bala{


 public:

    //FUNCIONES
    
    bala_aire(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo);
    virtual bool calcularVelocidad(float frame);
    bool efectoBala(entity & ent);
    //variables

    


    //constantes

    private:

    //FUNCIONES


    //VARIABLES
   vector3d aceleracion{vector3d(0,0,0)};
  
    

    //CONSTANTES

};