#pragma once
#include "motor_grafico/vector3d.hpp"
#include <vector>
#include "motor_fisicas/vector2d.hpp"





class entity;
class gameObject;
class MyNode_t;
class myMotorF
{
public:
    static vector3d move(vector3d &position, vector3d &velocidad);
   
    static bool colision(vector3d &posicion1,std::vector<vector3d> &puntos1,vector3d &posicion2,std::vector<vector3d> &puntos2);    
   
    static float gistancia(std::vector<vector3d> &puntos,int eje);
    static vector3d calcularHitBox(vector3d &posicion, vector3d &hitbox,vector3d &rotacion);
    static std::vector<vector3d> getPuntos(vector3d &posicion, vector3d &hitbox, vector3d &rotacion);
    static std::vector<vector2d> getRegion(std::vector<vector3d> &puntos);
    static bool existeRegion( std::vector<vector2d> &regiones, vector2d & region);
    static bool coincidenRegiones(std::vector<vector2d> &regiones1,std::vector<vector2d> &regiones2);
   
    enum eje{ejex,ejey,ejez};
    static const int TamanoRegion {50};
};




