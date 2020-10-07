#include"motor_grafico/IAniMesh.hpp"

#define BOUNDING_BOX_EDGES 8

///////////////////////
//   RENDER Y MAPAS  //
///////////////////////

//Cargador de modelos

//Metodo que crea la malla para el modelo
IAnimMesh* IAnimMesh::crearObj(const char* mPathChain){

	malla = fachada->smgr->getMesh(mPathChain);
	return this;
}
//devuelve la malla del modelo
irr::scene::IAnimatedMesh* IAnimMesh::getAnimMeshIrr(){
	return malla;
}

//Dibuija el modelo 
IAnimMeshNode* IAnimMeshNode::crearNodoMalla(IAnimMesh* model,const char* tPathChain,Coordenada& coords,bool colisionable){
	
	mallita=model;

	mallaNodo = fachada->smgr->addAnimatedMeshSceneNode(model->getAnimMeshIrr()); //le pongo la malla normalizada (en principio)

	if(mallaNodo){
		mallaNodo->setMaterialTexture(0, fachada->driver->getTexture(tPathChain));//le mete una textura
		mallaNodo->setMaterialFlag(irr::video::EMF_LIGHTING,false);//dibuja

		initBoxEdges();//para ponerle una boundig box

		if (colisionable){
			this->setBox(model);
			this->getBoxVec();
			mallaNodo->setPosition(irr::core::vector3df(coords.getX()-(vectorBoxDimension.X/2),coords.getY()-(vectorBoxDimension.Y/2),coords.getZ()-(vectorBoxDimension.Z/2)));//le da una posicion
		}
	} 

	boundBoxEdges.reserve(BOUNDING_BOX_EDGES);

	//mallaNodo->setDebugDataVisible(irr::scene::EDS_BBOX); //-->para que irrlicht pinte automaticamente la bounding box de los modelos que se cargan

	return this;  
}

//Escala los modelos
void IAnimMeshNode::setEscala(float esc){
	mallaNodo->setScale(irr::core::vector3df(esc));
}
//Rota los modelos
void IAnimMeshNode::setRotacion(float x, float y, float z){
	mallaNodo->setRotation(irr::core::vector3df(x,y,z));
}
//devuelve el nodo de irrlitch
irr::scene::IAnimatedMeshSceneNode* IAnimMeshNode::getAnimMeshNodeIrr() const{
	return mallaNodo;
}

irr::core::aabbox3d<irr::f32>& IAnimMeshNode::getBoxIrrlicht(){ //con esto obtengo el bounding box que sacamos de la malla con el getBoundingBox() para tratar de hacer las colisiones con irrlicht (con el metodo que he hecho siempre colisiona y no se porque)
	return aBox;
}

void IAnimMeshNode::setBox(IAnimMesh* model){

	 	
		auto modelo = model->getAnimMeshIrr();

		//conseguimos la boundingbox
		aBox = modelo->getBoundingBox();
		//Conseguimos los ejes
		irr::core::vector3d<irr::f32> gEdges[8];
		aBox.getEdges(&gEdges[0]);

		setBoxEdges(gEdges);

		//Conseguimos ancho alto y profundidad para la hitbox de jesus
		auto x = gEdges[4].X - gEdges[0].X; 
		
		auto y = gEdges[1].Y - gEdges[0].Y;
		
		auto z = gEdges[2].Z - gEdges[0].Z;

    	vectorBoxDimension = vector3d (x,y,z);


		
		

}

void IAnimMeshNode::initBoxEdges(){
	for (int i = 0; i < BOUNDING_BOX_EDGES; i++)
	{
		boundBoxEdges.push_back(Coordenada(0,0,0));
	}
}

void IAnimMeshNode::setBoxEdges(irr::core::vector3d<irr::f32> gEdges [8]){

	for (int i = 0; i < BOUNDING_BOX_EDGES; i++)
	{
		boundBoxEdges[i].setCoordenada(gEdges[i].X, gEdges[i].Y, gEdges[i].Z);
	}

}

void IAnimMeshNode::updateBox(){

	aBox = mallaNodo->getTransformedBoundingBox();
	
	irr::core::vector3d<irr::f32> gEdges[8];
	aBox.getEdges(&gEdges[0]);

	setBoxEdges(gEdges);

	
	auto x = gEdges[4].X - gEdges[0].X; 
		
	auto y = gEdges[1].Y - gEdges[0].Y;
		
	auto z = gEdges[2].Z - gEdges[0].Z;

    vectorBoxDimension = vector3d (x,y,z);

	
}

//conseguir el vector de la hitbox
vector3d IAnimMeshNode::getBoxVec(){
	return vectorBoxDimension;
}