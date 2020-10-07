#pragma once

#include "State.hpp"
#include <vector>
#include <memory>
#include  "motor_grafico/camara.hpp"
#include "entity/gameObject.hpp"
#include "entity/balas/bala.hpp"
#include "entity/entity.hpp"
#include "behaviourTrees/sequenceTask.hpp"
#include "motor_sonido/audio.hpp"
#include "mapas/mapa.hpp"
#include "entity/player.hpp"
#include "estadisticas.hpp"
#include "motor_fisicas/fisicas.hpp"

class StateMachine;
class blackboard;
class enemyNear;
class sayHi;


class StateIngame : public State
{

public:

    ~StateIngame();
    virtual void init();
    virtual void input(StateMachine *stados);

    virtual void update(float deltaTime);
    virtual void render(float percentick);
    
    void createNPCs();  //Crea los npc en posiciones aleatorias
    void createCofres();  //Crea los cofres
    void UpdateIdCam(); //Actualiza la id de la camara, cambiandola si se pulsa F1 o F2 y actualizandola si alguien murio
	void checkCameraColision();
    void resetAll();
    void finalizarPartida(bool victoria);
    void limpiarArrayEntidades();
    
    //void putCharacter(std::unique_ptr<player> jugador, int i);//para asignar el personaje al jugador

    static int idCam;
    static bool controlCam;
    static entity* WatchingEnt;
    Mapa mapa;

private:


unique_ptr <camara> camera;
std::vector<unique_ptr <gameObject>> ArrayGameObject;
std::vector<unique_ptr <bala>> Arraybalas;
std::vector<unique_ptr <entity>> ArrayEntity;

CAudioEngine audio;
bool debug = false;
bool partidaFinalizada {false};


void drawHitBoxes();
void drawRegiones();
estadisticas est;
fisicas motorFisico {};
bool victoria {false};
};



void nextCam(int Entityssize); //Cambia la camara a la siguiente entidad
void prevCam(int Entityssize); //Cambia la camara para que mire a la entidad anterior
