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
struct testBotIa : public BotIa{

    testBotIa();
   
    std::shared_ptr<sequenceTask>     arbolroot;
    std::shared_ptr<hpLow>            decisionHplow;
    std::shared_ptr<hasMedkit>        decisionhasMedkit;
    std::shared_ptr<useMedkit>        accionUsemedkit;

 
    
    virtual bool run(blackboard *data) override;
    
};