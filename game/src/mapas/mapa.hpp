#pragma once

#include <iostream>
#include <vector>

#include "coordenada.hpp"
#include "leerFicheroMapa.hpp"

class ObjetosMapa;

class Mapa
{

private:

    vector<ObjetosMapa> objetosMapa;
    LeerFicheroMapa mapFileReader;

public:

    Mapa();
    ~Mapa();


    void addObjMapa(ObjetosMapa&); // add objs mapa
    const int getNumObjsMapa() const; // devuelve cuantos obj hay
};