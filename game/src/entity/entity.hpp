#pragma once


#include "balas/bala.hpp"
#include <vector>
#include "arma.hpp"
#include <memory>
#include "entity/gameObject.hpp"
#include "behaviourTrees/BotIas/BotIa.hpp"
#include "behaviourTrees/blackboard.hpp"
///meter variables en protected para acceder con los hijos


enum comportamiento{NINGUNO,NORMAL,TEST};
class lanzadorBala;
class entity : public gameObject{

    public:

    //FUNCIONES
    
    
    void disparar(std::vector<std::unique_ptr <bala>> &ArrayDeBalas);    
    virtual void calcularVelocidad(float &frame)=0;
    virtual void consecuenciasIngame(int option)=0;
    virtual void moveTo(vector3d pos)=0;
    bool hitEntity(float& dmg, lanzadorBala& lanzador);
    bool efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject);
    void lookAt(vector3d vec);              //Mira al punto objetivo
    void run();                             //Ejecuta la IA de la entidad
    bool isAlive();                         //Devuelve si está viva o no
    bool isPickeable() override; //Devuelve true o false si es un objeto recogible.

    virtual bool hasWaypointToMove() = 0;   //Indica si tiene un punto para moverse (IA)
    virtual void removeWaypoint() = 0;      //Elimina el siguiente punto para moverse(IA)
    virtual void setWaypoint() = 0;         //Se llama cuando se establece su punto, hace que haswaypoinToMove() devuelva true unicamente. (IA)
    virtual bool checkIfOpenChest() = 0;    //Se comprueba si abre el cofre o no. En caso de jugador tiene que pulsar E. En caso de enemigo lo abre siempre.
    virtual bool isPlayer() = 0;            //Devuelte true si es el jugador

    //GETTERS
   
    int& getlife();   
    vector3d& getvelocity();       
    uint8_t getvidatotal();  
    arma& getArma();
    virtual vector3d& getWayPoint() = 0;    //Devuelve el waypoint al que se moverá (IA)
    blackboard* getData();                  //Devuelve los datos de IA (IA)
    float& getDayo();
    int getTipo();
    int getKills();
    int getBalasDisparadas();
  
    
    //SETTERS         
    void setVelocity(vector3d vec);     
    void setVida(int hp);    
    void setArma(arma &weap);  
    void setVidaTotal(int hp);
    void setBehaviour(comportamiento ia);   //Establece el comportamiento de la entidad [NINGUNO / NORMAL] (IA)
    void setDanyo(float damage);
    void setTipo(int tipo);                 //tipos de entidad, y si esta muerto el jugador
    void setBalasDisparadas(int bal);
    void setSumarBala();
    void setRestarBala();
    void addKill();                         //aumenta en 1 el los enemigos asesinados

    void playKillSounds();                      //Reproducir los sonidos de racha de muerte
    void playHitSounds(lanzadorBala& origen, bool muerte);   //Reproducir sonidos de impacto, muerte, kills y frases elementales especificas.

    int claseElemental; //la clase elemental del personaje
    


    private:

   


    //VARIABLES
    
    vector3d velocidad;    
    
   
   
    uint8_t vidatotal;     
    arma weapon;
    std::unique_ptr<BotIa> behaviour {};    //El comportamiento que tendrá la entidad (IA)
    std::unique_ptr<blackboard> data;       //Los datos usados por la IA de la entidad (IA)
   
   protected:
    float danyo{1};
    int vida;
    int vidaextra{0};
    int velocidadextra{1};    
    int tipo;                                
    int enemigosAsesinados{0};
    int balasDisparadas{0};                              
    
    enum characters{AirCharacter, FireCharacter, GroundCharacter, LightCharacter, OscurityCharacter, WaterCharacter};

   

    
};  
