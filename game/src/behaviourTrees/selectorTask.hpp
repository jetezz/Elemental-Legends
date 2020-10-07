#pragma once



#include "treeTask.hpp"


/*
   =====
 /       \
|    ?    |
 \       /
   =====
El selector recorre sus hijos hasta que uno es correcto. Si encuentra un hijo exitoso el selector se detiene
Si no entuentra ningun hijo extitoso el selector falla.
*/

class blackboard;
struct selectorTask : public treeTask{
   
public:

   virtual bool run(blackboard *data) override;

};