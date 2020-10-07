#pragma once

#include "../treeTask.hpp"

class blackboard;
struct enemyNear : public treeTask {


public:

/*
Comprueba si un enemigo está cerca y lo pone como objetivo.
Este código hace dos cosas:
Si hay objetivo ya: Comprueba solo si el objetivo murió o salio del rango de visión
*/
   virtual bool run(blackboard *data) override;
};