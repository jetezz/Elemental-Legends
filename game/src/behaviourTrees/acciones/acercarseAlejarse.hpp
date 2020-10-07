#pragma once

#include "../treeTask.hpp"

class blackboard;
struct acercarseAlejarse : public treeTask {

public:
/*
   Comprueba si el bot está en el rango correcto para atacar con el arma que tiene.
   Si es así cambia la información de movimiento.
*/
   virtual bool run(blackboard *data) override;
};