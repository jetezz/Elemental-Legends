#pragma once



#include <vector>
#include <iostream>
#include "entity/enemy.hpp"
#include <vector>




class vector3d;
class entity;

//FUNCIONES


class fisicas{

public:

fisicas()=default;

void initFisicas(std::vector<unique_ptr <entity>> *ArEnt,std::vector<std::unique_ptr <bala>> *ArBal,std::vector<unique_ptr <gameObject>> *ArGO); 
void moverTodo(float frame);



void moverEntidad(entity &enti,float frame); 
void moverEntidadOptimizado(bala &bal, float frame);
int colisionConEntidades(vector3d &posicionLast,vector3d &posicionSiguiente,std::vector<vector3d> &puntos,std::vector<vector2d> &region);
int colisionConGameObject(vector3d &posicionLast,vector3d &posicionSiguiente,std::vector<vector3d> &puntos,std::vector<vector2d> &regiones);

static std::vector<vector3d> getPuntos(vector3d &posicion, vector3d &hitboxinit, vector3d &rotacion);
static std::vector <vector2d> getRegiones(std::vector<vector3d> &puntos);


bool esLaMismaEntidad(vector3d & pos1, vector3d& pos2);

private:

std::vector<unique_ptr <entity>> *ArrayEntity {nullptr};
std::vector<unique_ptr <bala>> *ArrayDeBalas {nullptr};
std::vector<unique_ptr <gameObject>> *ArrayGameObject {nullptr};




};

//VARIABLES


//CONSTANTES










