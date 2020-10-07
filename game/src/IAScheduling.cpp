

#include "IAScheduling.hpp"

static int frames {0};//Los frames que han pasado de juego
static int frecuency {3}; //la frecuencia de ejecución de la IA
static std::size_t iaIndex {0}; //la IA que se esta ejecutando actualmente
/*
*Ejecuta la inteligencia artificial de cada una de las IAs primero se espera unos frames de cortesia para que la ia no se ejecute
*todos los frames. Cuando empieza a ejecutarse se ejecuta en cada ciclo la IA de un bot
*/
void runIAs(std::vector<unique_ptr <entity>> &ArrayEntity){

frames++;//Cada vez que iniciamos el algoritmo aumentamos 1 frame
    
    if(iaIndex<ArrayEntity.size()){
      ArrayEntity.at(iaIndex)->run();
      iaIndex++;
    }
    if(iaIndex<ArrayEntity.size()){
      ArrayEntity.at(iaIndex)->run();
      iaIndex++;
    }
    if(iaIndex<ArrayEntity.size()){
      ArrayEntity.at(iaIndex)->run();
      iaIndex++;
    }

    if(iaIndex>=ArrayEntity.size() && frames > frecuency) { //Si el index de la ia actual pasa el tamano del array, empezamos de 0
      iaIndex=0;
      frames = 0;
      blackboard::clearPuntosEscuchados();
    }


}



