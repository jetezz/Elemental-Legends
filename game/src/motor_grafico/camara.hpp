#pragma once

#include <irrlicht/irrlicht.h>
#include "motor_grafico/fachadaIrrlicht.hpp"
#include "vector3d.hpp"
class vector3d;
class MyNode_t;





struct camara{

static float inline SENSIBILIDAD {04};		//Sensibilidad del raton
static float inline MAXPITCH     {89};		//Maximos que se puede subir la camara (mirando la cabeza del jugador)
static float inline MINPITCH     {-89};     //Minimo que se puede bajar la camara (mirando los pies del jugador)

static float inline ZOOMSPEED    {50};		//Velocidad a la que se puede hacer zoom
static float inline MAXZOOM      {60};		//Distancia maxima a la que se puede hacer zoom
static float inline MINZOOM      {01};     //Distancia minima a la que se puede hacer zoom

static float inline FIRSTPITCH   {15};		//Angulo inicial altura camara
static float inline FIRSTANGLE   {00};		//Angulo inicial camara
static float inline FIRSTZOOM    {35};		//Zoom inicial camara

static float inline DESPCAMX     {10};		//Desplazamiento horizontal de la camara
static float inline DESPCAMY	   {10};     //Desplazamiento vertical camara
static vector3d inline maxPos {0,0,0};

	camara();
	void setPosition(vector3d& posicion3d);	//Cambiar posicion de la camara
	vector3d getPosition();					//Obtener la posicion de la camara
	void updateThirdPersonPosition(MyNode_t& nodo, bool followNodeAngle=false);		//Actualizar la posicion de la camara pasandole el MyNode objetivo
	void updatePitch(float deltaTime); 								//Actualizar el ángulo vertical de la cámara, no puede pasar de -89 y 89 grados
	void updateAngleAround(float deltaTime);								//Actualizar el angulo alrededor del objeto
	void updateDistance(float deltaTime);   //Actualizar distancia camara
	void chocando(float distancia);
	void nochocando();

	irr::scene::ICameraSceneNode* cam;
	float distancia;
	float anguloAlObj;
	float pitch;
	bool colisionando {false};
	float distanciaColision {0};
};