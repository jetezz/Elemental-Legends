#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Coordenada
{
private:
    float posX; //coordenada en el eje X
    float posY; //coordenada en el eje Y
    float posZ; //coordenada en el eje Z
public:
    Coordenada(); //constructor por defecto de la clase coordenada (pone las 3 posiciones a 0)
    Coordenada(float, float, float); //constructor en el que se le indican el valor que tendran las 3 posiciones para la coordeanda creada
    Coordenada* const getCoordenadaObject() const; //metodo que devuelve un puntero al objeto coordenada actual de manera constante de manera que, el puntero no se puede modificar pero desde fuera puedo cambiar los datos del objeto en caso de necesitarlo
    const vector<float> getCoordenadas() const; //metodo que devuelve de manera constante un vector de floats correspondiente a las coordeandas x, y, z de la clase, de esta forma devolvemos los 3 valores directamente en forma de vector de floats
    const float getX() const;
    const float getY() const;
    const float getZ() const;
    void setCoordenada(float, float, float); //metodo que modifica los valores correspondientes a las posiciones en x, y, z con tal de cambiar la coordenada en cuestion
    ~Coordenada(); //destructor de la clase coordenada (no implementado ni utilizado hasta el momento)
};