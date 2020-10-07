#pragma once


/*

En este archivo he puesto las constantes que tiene el juego
Las pongo aquí porque creo que es un método más sencillo ya que cuando están
por cada lado del código se vuelve caótico encontrarlas.

*/

static const float     MOVEMENT_SPEED = 40.f;
static const float     MOVEMENT_JUMP = 50.f;
static const float     PI {3.14159265};
static const int       rangoNextwaypoint = 150;
static const int       numEnemies = 9;
static const int       numCofres = 15;
static const int       spawnRange = 400;
static const int       radioSpawnCofres = 300;
static const int       alturaSpawn = 30;
static constexpr float distanciaVision = 200;
static constexpr float distanciaEscucha = 300;
static constexpr int   anguloVision = 40;
static constexpr int   distanciaDeteccionMinima = 24;
static const int       curacionMedikit = 10;
static const float     gravedad {35};	
static const float     noGameObject {-1};
static const float     vidaEntidades {20};
static const int       SIZE_POINTS {8};

enum Enumtipo{jugador,enemigo,online,muerto};