#pragma once

#include <irrlicht/irrlicht.h>
#include "motor_grafico/fachadaIrrlicht.hpp"
#include "coordenada.hpp"
#include "../render.hpp"

class vector3d;


struct MyNode_t {
	//MyNode_t(MyNode_t&) = delete;
	//MyNode_t(MyNode_t&&) = delete;
	//MyNode_t& operator=(MyNode_t&) = delete;
	//MyNode_t& operator=(MyNode_t&&) = delete;

	//inicializar imagen
	void initImagen(vector3d &pos, vector3d &rot);
	vector3d calcularHitBox();
	//
	//bala
		void initBalaNeutral(vector3d& vec, vector3d& hit) ;
		void initBalaFuego(vector3d& vec, bool colision);
		void initBalaAgua(vector3d& vec, bool  colision) ;
		void initBalaAire(vector3d& vec, bool colision);
		void initBalaTierra(vector3d& vec, bool colision);
	//

	//entity
		void initPlayer(vector3d& vec,bool colision);
		void initEnemy(vector3d& vec, bool);
		std::vector<Coordenada> getPoints();
		void setPoints();
	//
	
	//cofre	
		void initCofre(vector3d& vec, bool colision);
	//

	//power
		void initPowerAgua(vector3d& vec, vector3d& hit);
		void initPowerAire(vector3d& vec, vector3d& hit);
		void initPowerFuego(vector3d& vec, vector3d& hit);
		void initPowerTierra(vector3d& vec, vector3d& hit);
		void initPowerVida(vector3d& vec, vector3d& hit);

	//
	void eliminarNode();
	void lookAt(vector3d vec);
	void makeTransparent(); //Hacer la textura transparente
	void makeSolid();       //Hacer la textura solida y quitar la transparencia

	vector3d getRotation();
	vector3d getPosition();
	void setPosition(vector3d vec);
	void setRotation(vector3d vec);
	void setScale(vector3d vec);
	irr::scene::ISceneNode* getNode();
	IAnimMeshNode* getAnimMeshNode();

	void drawBoundingBoxWithEdges(std::vector<vector3d> &puntos);
	void setVisible(bool modo);
	vector3d getMinAABB();
	vector3d getMaxAABB();
	
	private:
	irr::scene::ISceneNode* node {nullptr};
	IAnimMeshNode* animMeshNode {nullptr};
	fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
	Render render;	
	std::vector<Coordenada> points {};
	irr::core::array<irr::scene::IAnimatedMeshSceneNode*> createLocalAxes(irr::scene::ISceneNode* parent, bool box = false, irr::f32 scale = 1.0f);


	
  };
