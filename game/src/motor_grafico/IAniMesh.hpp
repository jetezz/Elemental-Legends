#pragma once
#include <irrlicht/irrlicht.h>
#include "motor_grafico/fachadaIrrlicht.hpp"
#include "motor_grafico/vector3d.hpp"

#include "coordenada.hpp"
#include "vector"


//============== mapas ===============
struct IAnimMesh{
	IAnimMesh* crearObj(const char*);
	irr::scene::IAnimatedMesh* getAnimMeshIrr();
	private:
	irr::scene::IAnimatedMesh* malla{nullptr};
	fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
};

struct IAnimMeshNode{
	IAnimMeshNode* crearNodoMalla(IAnimMesh* model,const char* tPathChain,Coordenada& coords,bool colisionable);
	void setEscala(float);
	void setRotacion(float,float,float);
	void setBox(IAnimMesh* );
	void updateBox();
	irr::scene::IAnimatedMeshSceneNode* getAnimMeshNodeIrr() const;
	irr::core::aabbox3d<irr::f32>& getBoxIrrlicht();
	IAnimMesh* getAnimMesh();
	vector3d getBoxVec();
	

	private:
	IAnimMesh* mallita{nullptr};
	irr::scene::IAnimatedMeshSceneNode* mallaNodo{nullptr};
	fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
	irr::core::aabbox3d<irr::f32> aBox; //esta es la bounding box que sacamos al hacerle el getBoundingBox() al modelo
	vector<Coordenada> boundBoxEdges {};
	vector3d vectorBoxDimension {0,0,0};

	void initBoxEdges();
	void setBoxEdges(irr::core::vector3d<irr::f32> [8]);
};

//===================================