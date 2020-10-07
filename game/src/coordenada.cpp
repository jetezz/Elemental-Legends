#include "coordenada.hpp"

Coordenada::Coordenada() : posX(0), posY(0), posZ(0){} //constructor por defecto de la clase coordenada (pone los valores correspondientes a posX, posY y posZ a 0)

Coordenada::Coordenada(float x, float y, float z){ //constructor al que se le especifican los valores de posX, posY y posZ respectivamente (se pasan por valor debido primero a que es un tipo basico y no costaria nada hacer una copia del mismo (puede que costara incluso bastante menos que pasarle una referencia (un puntero)) y segundo, para poder especificarle directamente al llamar al constructor valores enteros sin tener que crear una variable de tipo float para poder pasarselos al constructor)
    posX = x;
    posY = y;
    posZ = z;
}

Coordenada* const Coordenada::getCoordenadaObject() const{ //metodo que devuelve un puntero de solo lectura a los datos correspondientes al objeto coordenada, con tal de modificarlo desde fuera si se precisa (aunque el puntero no se puede modificar)
    return (Coordenada* const) this; //this quiere decir, este objeto coordenada, actual (es un puntero al objeto coordenada actual)
}

const vector<float> Coordenada::getCoordenadas() const{ //metodo que devuelve un vector de floats de solo lectura atendiendo a los valores de posX, posY y posZ del objeto coordenada actual
    vector<float> vec; //creamos un vector de floats
    
    vec.resize(3);
    
    vec[0] = posX;
    vec[1] = posY;
    vec[2] = posZ;

    
    return vec; //devolvemos el vector de floats creado
}


const float Coordenada::getX() const{
    return posX;
}

const float Coordenada::getY() const{
    return posY;
}

const float Coordenada::getZ() const{
    return posZ;
}

void Coordenada::setCoordenada(float x, float y, float z){ //metodo que cambia las posiciones en el eje x, y, z atendiendo a los floats pasados por parametro
    posX = x;
    posY = y;
    posZ = z;
}

Coordenada::~Coordenada() //destructor de la clase coordenada (no implementado ni utilizado hasta el momento)
{
}