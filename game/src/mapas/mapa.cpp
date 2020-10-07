#include "mapa.hpp"
#include "objetosMapa.hpp"

//constructor
Mapa::Mapa (){
    mapFileReader.readMapFile("",this);
}

//destructor de la clase mapa.
Mapa::~Mapa(){

}

//add un obj al array de mapas
void Mapa::addObjMapa(ObjetosMapa& nuevoObj){
    objetosMapa.push_back(nuevoObj);
}

//devuelve la cantidad de objetos del array de objetos para el mapa
const int Mapa::getNumObjsMapa() const{
    return objetosMapa.size();
}

