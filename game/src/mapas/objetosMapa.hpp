#pragma once

#include <iostream>
#include <vector>


#include "coordenada.hpp"
class IAnimMesh;
class IAnimMeshNode;
class ObjetosMapa
{
private:
    std::string modelPath;
    std::string texturePath;
    IAnimMesh* modelo;
    IAnimMeshNode* modeloNodo;
    Coordenada coord;
    int type;
    bool colisionable;
    bool visible;
public:
    ObjetosMapa();
    ObjetosMapa(const std::string,const std::string,std::vector<float>,int,bool,bool);
    const std::string getDirModelo() const;
    const std::string getDirTextura() const;
    const int getTipo() const;
    const bool getEsColisionable() const;
    const bool getEsVisible() const;
    ~ObjetosMapa();
};
