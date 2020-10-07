#pragma once


#include <list>
#include <memory>
/*

Es la base del comportamiento, tiene unos hijos que realizaran una tarea
como: 
Decidir si continuar
Acciones

Las tareas se ejecutan recursivamente.

*/
class blackboard;
struct treeTask{

    virtual bool run(blackboard *data) = 0;
    virtual void addChild(std::shared_ptr<treeTask> child);
   
    std::list<std::shared_ptr<treeTask>> children;
};