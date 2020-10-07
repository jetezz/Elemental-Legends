#pragma once

#include <irrlicht/irrlicht.h>
#include <iostream>
#include "glm/glm.hpp"

#include "motor_grafico/MyEventReceiver.hpp"
#include "coordenada.hpp"
















class vector3d;
class MyNode_t;
class fachadaIrrlicht{

    public: 
//FUNCIONES

	
    void updateMouse();
	void rotateNodeWithMouse(MyNode_t* img);
    int tipoRenderizado();
    int crearPantalla();
	float getMouseDx();
	float getMouseDy();
	void setMouseVisibility(bool);
	
  //  void crearCamara();  
	irr::scene::ISceneNode*  createPlayer(vector3d &vec,vector3d &hit);//para crear player
	irr::scene::ISceneNode*  createEnemy(vector3d &vec,vector3d &hit);//para crear enemigo
	irr::scene::ISceneNode*  createBulletFuego(vector3d &vec,vector3d &hit);//para crear bala
	irr::scene::ISceneNode*  createBulletNeutral(vector3d &vec,vector3d &hit);//para crear bala
	irr::scene::ISceneNode*  createBulletAgua(vector3d &vec,vector3d &hit);//para crear bala
	irr::scene::ISceneNode*  createBulletAire(vector3d &vec,vector3d &hit);//para crear bala
	irr::scene::ISceneNode*  createBulletTierra(vector3d &vec,vector3d &hit);//para crear bala
	irr::scene::ISceneNode*  createCofre(vector3d &vec,vector3d &hit); //para crear cofre
	irr::scene::ISceneNode*  createVida(vector3d &vec,vector3d &hit); //para crear la vida del powerUp
	

	
	void createmapa(int tam); //para crear cofre
	
	//hud
	void initHud();	
	void hudArmaNeutral(uint8_t opcion);
	void hudArmaAgua(uint8_t opcion);
	void hudArmaAire(uint8_t opcion);
	void hudArmaFuego(uint8_t opcion);
	void hudArmaTierra(uint8_t opcion);
	void drawLine(vector3d ini, vector3d fin, vector3d color); //Pinta una linea del punto INI al FIN con Color
	
	void hudArmaNeutralb(uint8_t opcion);
	void hudArmaAguab(uint8_t opcion);
	void hudArmaAireb(uint8_t opcion);
	void hudArmaFuegob(uint8_t opcion);
	void hudArmaTierrab(uint8_t opcion);
	void hudPowerVida(uint8_t opcion);
	void hudPowerVidab(uint8_t opcion);
	void hudIntroParaSalir();


	
	void hudTier1(int pos,int num);
	void hudTier2(int pos,int num);
	void hudTier3(int pos,int num);
	void hudTier4(int pos,int num);
	void elimiraTier(int pos);







	void hudMunicion();

	void activarMensaje();
	void activarMensajeIntro();
	void desactivarMensaje();

	void numeroBalas(int num);
	void numeroVida(int num);
	void estadisticaTiempo(float num);
	void estadisticaKills(int num);



	


	void cambiarPosicion(vector3d& vec,MyNode_t& img,vector3d& rotacion);
	
//////////////////menu/////////////////////
	void crearinterfaceinicio();//para asignar la imagen de fondo al iniciar el juego
	void crearinterfaceinicio2();//para asignar la imagen de fondo al iniciar el juego

	void crearinterfacemenu();//para asignar la imagen de fondo y de los botones en el menu
	void crearinterfacepersonajes();//para asignar imagen de fondo y los personajes

	void selectOption(int option);//para cambiar la imagen de las opciones seleccionadas
	void selectCharacter(int character);//para cambiar la imagen de los personajes
	void createGameOver(float tiempo, int muertes,bool victoria);
	void ajustarPantalla();
	void initTier();
///////////////////////////////////////////
	
	static fachadaIrrlicht* getFachada()
	{
		static fachadaIrrlicht instancia = fachadaIrrlicht();
		return &instancia;
	}
  
//VARIABLES
    MyEventReceiver receiver ;
    irr::IrrlichtDevice* device;
    irr::scene::ISceneNode* node;
    irr::video::IVideoDriver* driver;
    irr::scene::ISceneManager* smgr;
	irr::gui::IGUIEnvironment* env ;
	
	irr::gui::IGUIImage *hudPantalla;
	irr::gui::IGUIImage *mira;
	irr::gui::IGUIImage *ArmaNeutral;
	irr::gui::IGUIImage *ArmaAgua;
	irr::gui::IGUIImage *ArmaAire;
	irr::gui::IGUIImage *ArmaFuego;

	irr::gui::IGUIImage *ArmaTierra;
	irr::gui::IGUIImage *mensaje;
	irr::gui::IGUIImage *powerVida;
	irr::gui::IGUIImage *tier;
	irr::gui::IGUIImage *tier1;
	irr::gui::IGUIImage *tier2;
	irr::gui::IGUIImage *tier3;
	irr::gui::IGUIImage *tier4;
	irr::gui::IGUIImage *intro;

	irr::gui::IGUIStaticText *balas;
	irr::gui::IGUIStaticText *vida;
	irr::gui::IGUIStaticText *estTiempo;
	irr::gui::IGUIStaticText *estKills;

	irr::gui::IGUIEnvironment* background;//para iniciar el juego


	
//CONSTANTES 
  static const int ancho {1280};
static const int alto {720};


    private:
//FUNCIONES
	fachadaIrrlicht() {}
	~fachadaIrrlicht();
//VARIABLES
	static fachadaIrrlicht* _instance;

int relativox {0};
int relativoy {0};
int anchoInicial {0};
int altoInicial {0};
bool primtier1 {false};
bool primtier2 {false};
bool primtier3 {false};
bool primtier4 {false};


//CONSTANTES 
};

bool TestRayOBBIntersection(
	vector3d origen,
	vector3d fin,
	MyNode_t& nodo
);

bool pointIntersectsNode(const vector3d& p, MyNode_t& nodo);



