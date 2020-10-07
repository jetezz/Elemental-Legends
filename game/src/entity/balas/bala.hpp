#pragma once


#include <iostream>
#include "motor_grafico/mynode.hpp"
#include "motor_grafico/vector3d.hpp"
#include  <ctime>
#include "entity/gameObject.hpp"
#include "entity/entity.hpp"

struct lanzadorBala {
    int character;
    bool isPlayer {false};
};


class bala : public gameObject{

    public:

    //FUNCIONES
   
    virtual bool calcularVelocidad(float frame)=0;
    
    virtual bool efectoBala(entity & ent)=0;


       //GETTERS
   
    vector3d& getvelocity();
    vector3d& getvelocityI();
    vector3d& getpositionI();
    vector3d& getGravedad();    

    bool getMuerte();
    float&  getDmg();
    bool efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    bool isPickeable() override; //devuelve true o false si es un objeto recogible.
    entity* getEntidad();
    int getTipo();

    
    //SETTERS         
    void setVelocity(vector3d vec);
    void setVelocityI(vector3d vec);
    void setPositionI(vector3d vec);
    void setGravedad(vector3d vec);       
    void setMuerte(bool muerte);
    void setDmg(float dmg);
    void setEntidad(entity* entidad);
    void setTipo(int tip);

    


     //CONSTANTES

    static const int noColision {-1};
    
    static const bool  MuereAlColisionar      {true};
    static const bool  NoMuereAlColisionar    {false};
    

    //costantes de balas individuales
  

  //Tier 0 Arma Nutral
    const int64_t    TiemNeutral           {1000};
    static const int64_t    VelocidadNeutral      {100};
    static const int64_t    dmgNeutral            {1};
    static const int        hitBoxNeutral         {1};
    static const int        gravedadNeutral       {-2};


//Tier 0 Arma Agua
    const int64_t    TiemAgua              {1000};
    static const int64_t    VelocidadAgua         {100};
    static const int64_t    dmgAgua               {1};
    static const int        hitBoxAgua            {1};
    static const int        gravedadAgua          {-2};
//Tier 1    
    static const int64_t    dmgAgua1               {2};   
//Tier 2    
    static const int64_t    dmgAgua2               {3};
//

//Tier 0 Arma Aire
     const int64_t    TiemAire              {1800};
    static const int64_t    VelocidadAire         {200};   
    static const int64_t    dmgAire               {2};
    static const int        hitBoxAire            {2};
    static const int        gravedadAire          {-180};
//Tier 2
    static const int64_t    dmgAire2               {3};

//Tier 3
    static const int64_t    dmgAire3               {4};


//Tier 0 Arma Fuego
     const int64_t    TiemFuego             {2000};
    static const int64_t    VelocidadFuego        {60};
    static const int64_t    dmgFuego              {2};
    static const int        hitBoxFuego           {1};
//Tier 2
    static const int64_t    dmgFuego2            {3};

//Tier 3
    static const int64_t    dmgFuego3            {4};

//Tier 0 Arma Tierra
    const int64_t    TiemTierra            {1000};
    static const int64_t    VelocidadTierra       {200};
    static const int64_t    dmgTierra             {20};
    static const int        hitBoxTierra          {3};
    static const int        gravedadTierra        {-2};
//Tier 2
    static const int64_t    dmgTierra2             {40};

//Tier 3
    static const int64_t    dmgTierra3             {100};

    
    const float gravedad2                {-2};
    
  

    lanzadorBala lanzador {};
    

    private:

   


    //VARIABLES
   
    int tipo {0};  //tipo para saber si muere 
    vector3d posicionI;
    vector3d velocidad;
    vector3d velocidadI;
    vector3d gravedad;
    bool muerte;
    float dmg{0};
    entity* ent {nullptr};
   

};

