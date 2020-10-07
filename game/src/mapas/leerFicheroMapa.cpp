#include "leerFicheroMapa.hpp"
#include "mapa.hpp"
#include "objetosMapa.hpp"

#include <map>

#define DEFAULT_FILEIN_PATH "src/mapas/mapa.txt"
#define COORDS_DELIMITER ','

std::map<std::string,const int> mapObjectMapping = {
    {"house", 0},
    {"door" , 1},
    {"tree" , 2}
}; //mapa creado como enumerable, de manera que, cuando se lee en el fichero alguno de los strings, se traduce a una id determinada de tipo int

LeerFicheroMapa::LeerFicheroMapa() : fileIn(nullptr), fileInPath(DEFAULT_FILEIN_PATH){
}

void LeerFicheroMapa::readMapFile(const std::string filePath, Mapa* map){
    std::string line;
    std::stringstream ss;
    if(!filePath.empty()){
        fileInPath = filePath;
    }
    try
    {
        fileIn.open(fileInPath);
        if(!fileIn.fail()){
            while(getline(fileIn, line)){
                readMapObject(line,map);
            }
        }
        else{
            throw "Could not open map file";
        }
        fileIn.close();
        if(fileInPath != DEFAULT_FILEIN_PATH){
            fileInPath = DEFAULT_FILEIN_PATH;
        }
    }
    catch(const char* e){
        cout<<e<<endl;
    }
    catch(const std::exception& e)
    {
        if(!fileIn.eof()){
            fileIn.close();
        }
        std::cerr << e.what() << '\n';
    }
}

void LeerFicheroMapa::readMapObject(std::string &line, Mapa* map){
    vector<std::string> mapObjectParameters;
    while (line != "") //mientras no encuentre una linea vacia, ve leyendo linea por linea ya que quiere decir que aun no se han terminado de obtener todos los parametros del objeto del mapa que se va a crear en esta iteracion
    {
        mapObjectParameters.push_back(line);
        getline(fileIn, line); //como el fichero a leer es una instancia de la clase, puedo acceder desde cualquier metodo de la misma al puntero correspondiente a la linea actual por la que se esta leyendo el fichero en todo momento
    }  

    ObjetosMapa mapObject(mapObjectParameters[0], mapObjectParameters[1], getMapObjectCoordinate(mapObjectParameters[2]), 
                        mapObjectMapping[mapObjectParameters[3]], convertStringIntoBool(mapObjectParameters[4]), 
                        convertStringIntoBool(mapObjectParameters[5])); //creo mi objeto del mapa con los parametros obtenidos en el bucle anterior, IMPORTANTE: DEBEN ESTAR EN ORDEN O NO FUNCIONARA
                        
    map->addObjMapa(mapObject); //Cuando he construido mi objeto, lo anyado al vector de objetos de mapa de la clase mapa
    
}

std::vector<std::string> LeerFicheroMapa::split(std::string line, char delimiter){ //metodo que separa una linea de texto atendiendo al delimitador de tipo char que se le pase por parametro
    stringstream splitLine(line);
    std::string lineToken;
    vector<std::string> lineSplitted;
    while(getline(splitLine, lineToken, delimiter)){
        lineSplitted.push_back(lineToken);
    }
    return lineSplitted;
}

std::vector<float> LeerFicheroMapa::getMapObjectCoordinate(std::string &coordString){ //metodo con el que se obtiene un vector de floats correspondiente a las coordenadas del objeto y el cual es resultado de la conversion del string pasado por parametro
    std::vector<std::string> coordStringSplitted = split(coordString, COORDS_DELIMITER);
    std::vector<float> coordsVector;
    coordsVector.resize(coordStringSplitted.size()); //para ahorrar tiempo, relleno el array de floats de "0" atendiendo al tamanyo del vector de strings obtenido tras hacer split en el string pasado por parametro
    int i = 0;
    for(auto coordString : coordStringSplitted){
        coordsVector[i] = std::stof(coordString);
        i++;
    }
    return coordsVector;
}

bool LeerFicheroMapa::convertStringIntoBool(std::string &st){
    if(st == "true"){
        return true;
    }
    else{
        return false;
    }
}

LeerFicheroMapa::~LeerFicheroMapa(){
    if(!fileIn.eof()){
        fileIn.close();
    }
}