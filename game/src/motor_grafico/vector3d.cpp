#include "motor_grafico/vector3d.hpp"

/////////////////////
//Clase vector 3d////
/////////////////////
irr::core::vector3df vector3d::transformar(){
irr::core::vector3df aux;
aux.X=this->X;
aux.Y=this->Y;
aux.Z=this->Z;


return aux;
}