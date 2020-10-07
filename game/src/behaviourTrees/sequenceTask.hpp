#pragma once



#include "treeTask.hpp"
/*
=============
|           |
|   --->    |
|           |
=============
La secuencia realiza las tareas de sus hijos hasta que uno de ellos falla, entonces la secuencia falla.
Si todos los hijos realizan la tarea correctamente la secuencia es correcta.
*/
class blackboard;
struct sequenceTask : public treeTask{
   
public:

    virtual bool run(blackboard *data) override;
   
};