#pragma once


#include "../sequenceTask.hpp"
#include "../selectorTask.hpp"
#include "../decisiones/enemyNear.hpp"
#include "../decisiones/enemyHeard.hpp"
#include "../decisiones/enemyOnSight.hpp"
#include "../decisiones/hayWaypoint.hpp"
#include "../decisiones/hasAmmo.hpp"
#include "../decisiones/pickeableOnSight.hpp"
#include "../decisiones/hpLow.hpp"
#include "../decisiones/hasMedkit.hpp"
#include <memory>
#include "../acciones/acercarseAlejarse.hpp"
#include "../acciones/shotTask.hpp"
#include "../acciones/generarWaypoint.hpp"
#include "../acciones/rotateToPoint.hpp"
#include "../acciones/changeWeapon.hpp"
#include "../acciones/moveTo.hpp"
#include "../acciones/useMedkit.hpp"
#include "BotIa.hpp"

class blackboard;
struct NormalBotIa : public BotIa{

    NormalBotIa();
   
    std::shared_ptr<selectorTask>     arbolroot;
    std::shared_ptr<sequenceTask>     combatSequence;
    std::shared_ptr<enemyNear>        decisionTaskenemyNear;
    std::shared_ptr<selectorTask>     detectarSelector;
    std::shared_ptr<enemyOnSight>     decisionTaskEnemigoenangulodevision;
    std::shared_ptr<enemyHeard>       decisionNOescuchoNada;
    std::shared_ptr<rotateToPoint>    actionTaskrotateToPoint;
    std::shared_ptr<sequenceTask>     AtaqueSequence;
    std::shared_ptr<selectorTask>     AmmoSelector;
    std::shared_ptr<hasAmmo>          hasAmmoDecision;
    std::shared_ptr<changeWeapon>     changeWeaponAction;
    std::shared_ptr<acercarseAlejarse>accionAcercarseAlejarse;
    std::shared_ptr<shotTask>         actionShotTask;
    std::shared_ptr<sequenceTask>     haycofreSequence;
    std::shared_ptr<pickeableOnSight> decisionPickeableOnSight;
    std::shared_ptr<sequenceTask>     sequenceCurar;
    std::shared_ptr<hpLow>            decisionHplow;
    std::shared_ptr<hasMedkit>        decisionhasMedkit;
    std::shared_ptr<useMedkit>        accionUsemedkit;
    std::shared_ptr<sequenceTask>     andarSequence;
    std::shared_ptr<selectorTask>     waypointSelector;
    std::shared_ptr<hayWaypoint>      haywaypointDecision;
    std::shared_ptr<generarWaypoint>  generarWaypointTask;
    std::shared_ptr<moveTo>           moveToAcction;

    
    virtual bool run(blackboard *data) override;
    
};