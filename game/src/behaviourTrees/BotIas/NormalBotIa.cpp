
#include "NormalBotIa.hpp"
#include <iostream>

/*
Este es el arbol de comportamiento de la ia normal
*/

NormalBotIa::NormalBotIa() : 
   arbolroot                           {std::make_shared<selectorTask>()}, 
   combatSequence                      {std::make_shared<sequenceTask>()}, 
   decisionTaskenemyNear               {std::make_shared<enemyNear>()},
   detectarSelector                    {std::make_shared<selectorTask>()},
   decisionTaskEnemigoenangulodevision {std::make_shared<enemyOnSight>()},
   decisionNOescuchoNada               {std::make_shared<enemyHeard>()},
   actionTaskrotateToPoint             {std::make_shared<rotateToPoint>()},
   AtaqueSequence                      {std::make_shared<sequenceTask>()},
   AmmoSelector                        {std::make_shared<selectorTask>()},
   hasAmmoDecision                     {std::make_shared<hasAmmo>()},
   changeWeaponAction                  {std::make_shared<changeWeapon>()},
   accionAcercarseAlejarse             {std::make_shared<acercarseAlejarse>()},
   actionShotTask                      {std::make_shared<shotTask>()},
   haycofreSequence                    {std::make_shared<sequenceTask>()}, 
   decisionPickeableOnSight            {std::make_shared<pickeableOnSight>()},
   sequenceCurar                       {std::make_shared<sequenceTask>()},
   decisionHplow                       {std::make_shared<hpLow>()},
   decisionhasMedkit                   {std::make_shared<hasMedkit>()},
   accionUsemedkit                     {std::make_shared<useMedkit>()},
   andarSequence                       {std::make_shared<sequenceTask>()}, 
   waypointSelector                    {std::make_shared<selectorTask>()},
   haywaypointDecision                 {std::make_shared<hayWaypoint>()},
   generarWaypointTask                 {std::make_shared<generarWaypoint>()},
   moveToAcction                       {std::make_shared<moveTo>()}
{
    arbolroot->addChild(combatSequence);
    arbolroot->addChild(haycofreSequence);
    arbolroot->addChild(sequenceCurar);
    arbolroot->addChild(andarSequence);
    //Ataque
    
    combatSequence->addChild(decisionTaskenemyNear);
    combatSequence->addChild(detectarSelector);
    detectarSelector->addChild(decisionTaskEnemigoenangulodevision);
    detectarSelector->addChild(decisionNOescuchoNada);
    combatSequence->addChild(actionTaskrotateToPoint);
    combatSequence->addChild(AtaqueSequence);
    AtaqueSequence->addChild(AmmoSelector);
    AmmoSelector->addChild(hasAmmoDecision);
    AmmoSelector->addChild(changeWeaponAction);
    AtaqueSequence->addChild(accionAcercarseAlejarse);
    AtaqueSequence->addChild(actionShotTask);

    //Pickeables
    haycofreSequence->addChild(decisionPickeableOnSight);
    haycofreSequence->addChild(moveToAcction);
    haycofreSequence->addChild(changeWeaponAction);
    //Curar
    sequenceCurar->addChild(decisionHplow);
    sequenceCurar->addChild(decisionhasMedkit);
    sequenceCurar->addChild(accionUsemedkit);
    //Andar
    andarSequence->addChild(waypointSelector);
    andarSequence->addChild(moveToAcction);
    waypointSelector->addChild(haywaypointDecision);
    waypointSelector->addChild(generarWaypointTask);
}


bool NormalBotIa::run(blackboard *data){
 //  std::cout << "entrando en ia" << std::endl;
   return arbolroot->run(data);
}