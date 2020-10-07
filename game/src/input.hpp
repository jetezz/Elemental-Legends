#pragma once


#include <iostream>
#include <memory>
#include <vector>
#include "entity/balas/bala.hpp"


class vector3d;
class entity;



//funciones
void initInpunt();
void check_playerKeys(entity &jugador,const float frameDeltaTime,std::vector<unique_ptr <bala>> &Arraybalas);
void check_close();
bool check_debug();
bool check_abrirCofre();
bool check_cambioCamara(int sizeEntidades);
bool check_intro();

void verCreditos();//para ver los creditos desde el menu
void cerrar();//para cerrar el juego desde el menu
bool empezarjuego();//para ir a seleccion de personaje
bool iniciarjuego();//para saltar la animacion, actualmente una imagen
bool jugar(); //para empezar a jugar

int selectmenuoption(int option);//para seleccionar las diferentes opciones del menu
int selectcharacter(int option);//para seleccionar el personaje
void stopevents();