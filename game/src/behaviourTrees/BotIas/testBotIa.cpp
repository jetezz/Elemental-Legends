
#include "testBotIa.hpp"
#include <iostream>

/*
Este es el arbol de comportamiento de la ia normal
*/

testBotIa::testBotIa() : 
   arbolroot                           {std::make_shared<sequenceTask>()},
   decisionHplow                       {std::make_shared<hpLow>()},
   decisionhasMedkit                   {std::make_shared<hasMedkit>()},
   accionUsemedkit                     {std::make_shared<useMedkit>()}
   
{

   
    arbolroot->addChild(decisionHplow);
    arbolroot->addChild(decisionhasMedkit);
    arbolroot->addChild(accionUsemedkit);

}


bool testBotIa::run(blackboard *data){
 //  std::cout << "entrando en ia" << std::endl;
   return arbolroot->run(data);
}