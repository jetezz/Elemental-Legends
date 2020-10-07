#pragma once



#include "decorator.hpp"


struct Limit : public decorator{
   
public:

   virtual bool run(blackboard *data) override;

    private: 

    int runLimit=5;
    int intentos=0;
};