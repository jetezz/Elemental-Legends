#pragma once

#include <iostream>
#include <fstream> //para la lectura y escritura de ficheros
#include <vector>
#include <sstream>

class Mapa;

class LeerFicheroMapa
{
private:
    std::ifstream fileIn;
    std::string fileInPath;
    std::vector<std::string> split(std::string, char);
    void readMapObject(std::string&, Mapa*);
    std::vector<float> getMapObjectCoordinate(std::string&);
    bool convertStringIntoBool(std::string &);
public:
    LeerFicheroMapa();
    void readMapFile(const std::string, Mapa*);
    ~LeerFicheroMapa();
};
