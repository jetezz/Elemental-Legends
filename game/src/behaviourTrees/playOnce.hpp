#pragma once



#include "decorator.hpp"


struct playOnce : public decorator{
   
public:

   virtual bool run(blackboard *data) override;

    bool firstTime = false;
};