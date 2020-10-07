#include "objetosMapa.hpp"
#include "motor_grafico/IAniMesh.hpp"

ObjetosMapa::ObjetosMapa() : modelPath(nullptr), texturePath(nullptr), modelo(nullptr), modeloNodo(nullptr), coord(), type(0), colisionable(nullptr), visible(nullptr){}


//Metodo que  construye el objeto.
ObjetosMapa::ObjetosMapa( const std::string mPath, const std::string tPath,std::vector<float> coords,int tp,bool colis,bool vis)
                    : modelPath{mPath}, texturePath{tPath}, coord{Coordenada(coords[0],coords[1],coords[2])}, type{tp},
                      colisionable{colis}, visible{vis}{

    const char* mPathChain = mPath.c_str(); //c_str() devuelve un const char* a partir de un string, es un metodo propia de esta clase incluido bajo el espacio de nombres "std"
    const char* tPathChain = tPath.c_str();

    IAnimMesh malla;
    IAnimMeshNode mallaNodo;
    modelo = malla.crearObj(mPathChain);
    modeloNodo = mallaNodo.crearNodoMalla(modelo,tPathChain,coord,colis);
    modeloNodo->setEscala(25);
    modeloNodo->setRotacion(0,90,0);

}

const std::string ObjetosMapa::getDirModelo() const{
     return modelPath;
}

const std::string ObjetosMapa::getDirTextura() const{
     return texturePath;
}

const int ObjetosMapa::getTipo() const{
     return type;
}

const bool ObjetosMapa::getEsColisionable() const{
    return colisionable;
}

const bool ObjetosMapa::getEsVisible() const{
    return visible;
}

ObjetosMapa::~ObjetosMapa(){

}
