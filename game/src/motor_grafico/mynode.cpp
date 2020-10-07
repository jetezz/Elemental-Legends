#include "motor_grafico/mynode.hpp"
#include "motor_grafico/vector3d.hpp"
#include "motor_grafico/fachadaIrrlicht.hpp"
#include "CONSTANTES.hpp"

class vector3d;
/////////////////////
///clase mynode_t////
/////////////////////



//imagen
void MyNode_t::initImagen(vector3d &pos, vector3d &rot){
	fachada->cambiarPosicion(pos, *this,  rot);
}
vector3d MyNode_t::calcularHitBox(){
	vector3d hitBox;

	 hitBox.X = points.at(4).getX() - points.at(0).getX();
		
	 hitBox.Y = points.at(1).getY()  - points.at(0).getY();
		
	 hitBox.Z = points.at(2).getZ() - points.at(0).getZ();
	 return hitBox;
}
//entity
void MyNode_t::initPlayer(vector3d& vec,bool colision){

	animMeshNode = render.createPlayer(vec,colision);
	
   
	node = animMeshNode->getAnimMeshNodeIrr();
	//createLocalAxes(node);

	


}
void MyNode_t::initEnemy(vector3d& vec,bool colision){

	animMeshNode = render.createEnemy(vec,colision);
	
   
	node = animMeshNode->getAnimMeshNodeIrr();
    //createLocalAxes(node);
}
//////////////////////////




//balas
	void MyNode_t::initBalaNeutral(vector3d& vec, vector3d& hit){
		fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
		node=fachada->createBulletNeutral(vec,hit);
	}
	
void MyNode_t::initBalaFuego(vector3d& vec,bool colision){

	animMeshNode = render.createBulletFuego(vec,colision);

	node = animMeshNode->getAnimMeshNodeIrr();

}
void MyNode_t::initBalaAgua(vector3d& vec,bool colision){

	animMeshNode = render.createBulletAgua(vec,colision);

	node = animMeshNode->getAnimMeshNodeIrr();

}
void MyNode_t::initBalaAire(vector3d& vec,bool colision){

	animMeshNode = render.createBulletAire(vec,colision);

	node = animMeshNode->getAnimMeshNodeIrr();

}
void MyNode_t::initBalaTierra(vector3d& vec,bool colision){

	animMeshNode = render.createBulletTierra(vec,colision);

	node = animMeshNode->getAnimMeshNodeIrr();

}

void MyNode_t::initCofre(vector3d& vec,bool colision){

	animMeshNode = render.createCofre(vec,colision);

	node = animMeshNode->getAnimMeshNodeIrr();

}
////

/////POWERUP
	void MyNode_t::initPowerAgua(vector3d& vec, vector3d& hit){
		animMeshNode = render.createBulletAgua(vec,true);

		node = animMeshNode->getAnimMeshNodeIrr();
	}
	void MyNode_t::initPowerAire(vector3d& vec, vector3d& hit){
		animMeshNode = render.createBulletAire(vec,true);

		node = animMeshNode->getAnimMeshNodeIrr();
	}
	void MyNode_t::initPowerFuego(vector3d& vec, vector3d& hit){
		
		animMeshNode = render.createBulletFuego(vec,true);

		node = animMeshNode->getAnimMeshNodeIrr();

	}
	void MyNode_t::initPowerTierra(vector3d& vec, vector3d& hit){

		animMeshNode = render.createBulletTierra(vec,true);

		node = animMeshNode->getAnimMeshNodeIrr();
	}
	void MyNode_t::initPowerVida(vector3d& vec, vector3d& hit){
		fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
		node=fachada->createVida(vec,hit);
	}
/////


void MyNode_t::lookAt(vector3d vec){
	float dx = vec.X - getNode()->getPosition().X;
	float dy = vec.Y - getNode()->getPosition().Y;
	float dz = vec.Z - getNode()->getPosition().Z;
	float xzdistance = sqrtf(dx*dx+dz*dz);

	auto rotacion = vector3d(-atan2f(dy,xzdistance)*180/PI,-atan2f(-dx,dz)*180/PI,0);
	//cout << "rotacion" << rotacion.Y << endl;
	setRotation(rotacion);
}

irr::scene::ISceneNode* MyNode_t::getNode(){
	return this->node;
}
void MyNode_t::eliminarNode(){
	node->remove();
}

vector3d MyNode_t::getPosition(){
	return vector3d((float)node->getPosition().X,(float)node->getPosition().Y,(float)node->getPosition().Z);
}

vector3d MyNode_t::getRotation(){
	
	
	return vector3d((float)node->getRotation().X,(float)node->getRotation().Y,(float)node->getRotation().Z);
}
int fachadaIrrlicht::crearPantalla(){
 


     device = createDevice(irr::video::EDT_OPENGL,
			irr::core::dimension2d<irr::u32>(ancho, alto), 16, false, false, false, &receiver);

    if (device == 0)
		return 1; // could not create selected driver.

        driver = device->getVideoDriver();
	    smgr = device->getSceneManager();
return 0;
}

void MyNode_t::setPosition(vector3d vec){

	node->setPosition(vec.transformar());

}

void MyNode_t::setRotation(vector3d vec){
	if(vec.Y>=360) vec.Y -= 360;
	if(vec.Y<0)	   vec.Y += 360;
	node->setRotation(vec.transformar());
	//cout << "nodo angle" << vec.Y << endl;

}

void MyNode_t::setScale(vector3d vec){
	node->setScale(irr::core::vector3df(vec.X, vec.Y, vec.Z));
}

IAnimMeshNode* MyNode_t::getAnimMeshNode(){

	return this->animMeshNode;
}

//metodo que devuelve un vector de coordenaadas con los 8 puntos de la bounding box
vector<Coordenada> MyNode_t::getPoints(){
	return points;
}

//Metodo que da los 8 puntos de la hitbopx en un array de coordenadas 
void MyNode_t::setPoints(){
	irr::core::vector3d<irr::f32> gEdges[8];
	//Aqui diferenciamos entre el tipo modelo y el tipo IScene node creado por defecto para los cubos
	if(animMeshNode !=nullptr){
		animMeshNode->getAnimMeshNodeIrr()->getTransformedBoundingBox().getEdges(&gEdges[0]);
	}else{
		node->getTransformedBoundingBox().getEdges(&gEdges[0]);
	}
	
	std::vector<Coordenada> aux ;
	aux.push_back(Coordenada(gEdges[0].X,gEdges[0].Y,gEdges[0].Z));
	aux.push_back(Coordenada(gEdges[1].X,gEdges[1].Y,gEdges[1].Z));
	aux.push_back(Coordenada(gEdges[2].X,gEdges[2].Y,gEdges[2].Z));
	aux.push_back(Coordenada(gEdges[3].X,gEdges[3].Y,gEdges[3].Z));
	aux.push_back(Coordenada(gEdges[4].X,gEdges[4].Y,gEdges[4].Z));
	aux.push_back(Coordenada(gEdges[5].X,gEdges[5].Y,gEdges[5].Z));
	aux.push_back(Coordenada(gEdges[6].X,gEdges[6].Y,gEdges[6].Z));
	aux.push_back(Coordenada(gEdges[7].X,gEdges[7].Y,gEdges[7].Z));

	points = aux;

	/*Puntos de los ejes de coordnadas:
	 			   /3--------/7
                  / |       / |
                 /  |      /  |
                1---------5   |
                |  /2- - -|- -6
                | /       |  /
                |/        | /
                0---------4/
     */
	
}

//Conseguir el eje minimo
vector3d MyNode_t::getMinAABB(){
	irr::core::vector3d<irr::f32> gEdges[8];
	
	node->getTransformedBoundingBox().getEdges(gEdges);
	return vector3d(gEdges[0].X,gEdges[0].Y,gEdges[0].Z);
	
}
//Conseguir el eje maximo
vector3d MyNode_t::getMaxAABB(){
	irr::core::vector3d<irr::f32> gEdges[8];
	
	node->getTransformedBoundingBox().getEdges(gEdges);
	return vector3d(gEdges[7].X,gEdges[7].Y,gEdges[7].Z);
	
}

void MyNode_t::makeTransparent(){
	node->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR); //makes it transparent
} //Hacer la textura transparente

void MyNode_t::makeSolid(){
	node->setMaterialType(irr::video::EMT_SOLID); //makes it solid
} //Hacer la textura solida y quitar la transparencia


//Metodo para debug de modelos 
void MyNode_t::drawBoundingBoxWithEdges(std::vector<vector3d> &puntos){
	irr::video::SColor color(255,255,0,0);
	irr::core::vector3d<irr::f32> gEdges[8];
	node->getTransformedBoundingBox().getEdges(gEdges);
	fachada->driver->draw3DLine(puntos[0].transformar(), puntos[1].transformar());
	fachada->driver->draw3DLine(puntos[0].transformar(), puntos[2].transformar());
	fachada->driver->draw3DLine(puntos[0].transformar(), puntos[4].transformar());
	fachada->driver->draw3DLine(puntos[1].transformar(), puntos[3].transformar());
	fachada->driver->draw3DLine(puntos[1].transformar(), puntos[5].transformar());
	fachada->driver->draw3DLine(puntos[2].transformar(), puntos[3].transformar());
	fachada->driver->draw3DLine(puntos[2].transformar(), puntos[6].transformar());
	fachada->driver->draw3DLine(puntos[3].transformar(), puntos[7].transformar());
	fachada->driver->draw3DLine(puntos[4].transformar(), puntos[5].transformar());
	fachada->driver->draw3DLine(puntos[4].transformar(), puntos[6].transformar());
	fachada->driver->draw3DLine(puntos[5].transformar(), puntos[7].transformar());
	fachada->driver->draw3DLine(puntos[6].transformar(), puntos[7].transformar());
}
irr::core::array<irr::scene::IAnimatedMeshSceneNode*> MyNode_t::createLocalAxes(irr::scene::ISceneNode* parent, bool box, irr::f32 scale){
	
    irr::core::array<irr::scene::IAnimatedMeshSceneNode*> axes;
    irr::scene::IAnimatedMeshSceneNode* xAxis = 0;
    irr::scene::IAnimatedMeshSceneNode* yAxis = 0;
    irr::scene::IAnimatedMeshSceneNode* zAxis = 0;

	auto smgr = fachada->smgr;
       
    irr::f32 parentScale = parent->getScale().Y;

	if(box){
		scale = parentScale * 3;
	}
       
    irr::f32 h = scale;
    irr::f32 ch = h * 0.6f;
    irr::f32 cd = h * 0.05f;
    irr::f32 d = h * 0.3f;
       
    xAxis = smgr->addAnimatedMeshSceneNode
    (
        smgr->addArrowMesh(
            "xAxis",
            irr::video::SColor(255, 255,0,0),
            irr::video::SColor(255, 255,0,0),
            4, 8,
            h, ch, cd, d
        )
    );
    xAxis->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    xAxis->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    //xAxis->setMaterialFlag(video::EMF_ZBUFFER, false);
    xAxis->setParent(parent);
    xAxis->setScale(irr::core::vector3df(scale));
       
    xAxis->setRotation(irr::core::vector3df(0.0f, 0.0f, 90.0f));
       
       
    yAxis = smgr->addAnimatedMeshSceneNode
    (
        smgr->addArrowMesh(
            "yAxis",
            irr::video::SColor(255, 0,255,0),
            irr::video::SColor(255, 0,255,0),
            4, 8,
            h, ch, cd, d
        )
    );
    yAxis->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    yAxis->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    yAxis->setParent(parent);
    yAxis->setScale(irr::core::vector3df(scale));
       
    zAxis = smgr->addAnimatedMeshSceneNode
	(
        smgr->addArrowMesh(
            "zAxis",
            irr::video::SColor(255, 0,0,255),
            irr::video::SColor(255, 0,0,255),
            4, 8,
            h, ch, cd, d
    	)
    );
    zAxis->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    zAxis->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    //zAxis->setMaterialFlag(video::EMF_ZBUFFER, false);
    zAxis->setParent(parent);
    zAxis->setScale(irr::core::vector3df(scale));
       
    zAxis->setRotation(irr::core::vector3df(90.0f, 0.0f, 0.0f));
 
    axes.push_back(xAxis);
    axes.push_back(yAxis);
    axes.push_back(zAxis);
       
    return axes;
}
void MyNode_t::setVisible(bool modo){
	if(modo){
		node->setVisible(true);
	}else{
		node->setVisible(false);
	}
}