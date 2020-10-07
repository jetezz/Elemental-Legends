#pragma once

struct blackboard;
/*
El bot ia es una clase padre que construye ias diseñadas para los bots utilizando los elementos del behaviour tree
*/
struct BotIa{

    virtual bool run(blackboard *data) = 0;
    
};