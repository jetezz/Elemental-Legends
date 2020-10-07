#include "motor_grafico/camara.hpp"
#include "motor_grafico/vector3d.hpp"
#include "motor_grafico/mynode.hpp"
#include "../entity/entity.hpp"
#include "fachadaIrrlicht.hpp"
#include "../entity/gameObject.hpp"
#include "../CONSTANTES.hpp"
#include <memory>

camara::camara()
 : distancia{FIRSTZOOM}, anguloAlObj{FIRSTANGLE}, pitch{FIRSTPITCH}{
	cam = fachadaIrrlicht::getFachada()->smgr->addCameraSceneNode(0,irr::core::vector3df(0,30,-40),irr::core::vector3df(0,5,0)); 
	
}

void camara::setPosition(vector3d& posicion3d){
	cam->setPosition(posicion3d.transformar());
}
vector3d camara::getPosition(){

	
	return vector3d((float)cam->getPosition().X,(float)cam->getPosition().Y,(float)cam->getPosition().Z);


}

void camara::chocando(float distanciaChoque){
	colisionando = true;
	distanciaColision = distanciaChoque;
}
void camara::nochocando(){
	colisionando = false;
}




/*
*Actualizar la posicion de la camara pasandole el MyNode objetivo en tercera persona
* @param nodo Es el nodo que va a seguir la camara
* @param deltaTime es el tiempo delta
* @param followNodeAngle booleano que indica si la camara esta sujeta al giro del nodo o la gira el usuario
*/
void camara::updateThirdPersonPosition(MyNode_t& nodo,bool followNodeAngle){
	static const float movimientoCam {0.016};


	updatePitch(movimientoCam);
	updateDistance(movimientoCam);
	if (followNodeAngle){
		anguloAlObj = nodo.getRotation().Y;
	} else {
		updateAngleAround(movimientoCam);
	}
	vector3d pos = getPosition();


	float horizontalDis = distancia * cos(pitch*PI/180);     //Distancia horizontal camara
	float verticalDis   = distancia * sin(pitch*PI/180);     //Distancia vertical camara
	float offSetX = horizontalDis * sin(anguloAlObj*PI/180);
	float offSetZ = horizontalDis * cos(anguloAlObj*PI/180); 

		pos.X = nodo.getPosition().X - offSetX;		 //Posicion en x camara
		pos.Z = nodo.getPosition().Z - offSetZ;		 //Posicion en y camara
		pos.Y = nodo.getPosition().Y + verticalDis;     //Calcular altura de camara
	
	//Hacer invisible a la entidad si estas en primera persona
	if(distancia!=MINZOOM){
		nodo.getNode()->setVisible(true);
	}else{
		nodo.getNode()->setVisible(false);
	}
	auto percentDist = distancia/MAXZOOM;
	auto desplazamientoX = DESPCAMX*percentDist;
	auto desplazamientoY = DESPCAMY*percentDist;

	if(followNodeAngle && distancia!=MINZOOM){
		//Desplazamos posicion de la camara para que esté movida a un lado y no encima del jugador
		pos.Z += desplazamientoX*cos((nodo.getRotation().Y+90)*PI/180);	//Desplazamiento z camara
		pos.X += desplazamientoX*sin((nodo.getRotation().Y+90)*PI/180);	//Desplazamiento x camara
		pos.Y += desplazamientoY;											//Desplaazamiento vertical camara
	}
	if(pos.Y<=0) pos.Y = 0;
	cam->setPosition(pos.transformar());
	//Cogemos el target del jugador y lo desplazamos para que la camara no apunte al jugador sino a donde disparar
	vector3d vec = nodo.getPosition();
	
	if(followNodeAngle && distancia!=MINZOOM){
		vec.Z += desplazamientoX*cos((nodo.getRotation().Y+90)*PI/180);	//Desplazamiento del target z
		vec.X += desplazamientoX*sin((nodo.getRotation().Y+90)*PI/180);	//Desplazamiento del target x
		vec.Y += desplazamientoY;											//Desplazamiento del target vertical
	}
	
	cam->setTarget(vec.transformar());
	
}

//Actualizar el ángulo vertical de la cámara, no puede pasar de -89 y 89 grados
void camara::updatePitch(float deltaTime){
	fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
	pitch += fachada->receiver.MouseState.Dy * SENSIBILIDAD * deltaTime;
	if(pitch>MAXPITCH) pitch = MAXPITCH;
	if(pitch<MINPITCH)	pitch = MINPITCH;
	//std::cout << "Pitch: " << pitch << std::endl;
}

//Actualizar el angulo de la camara alrededor del jugador, solo si se activa
void camara::updateAngleAround(float deltaTime){
	fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
	anguloAlObj += fachada->receiver.MouseState.Dx * SENSIBILIDAD * deltaTime;
}

//Actualizar la distancia de la camara
void camara::updateDistance(float deltaTime){
fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
	if(fachada->receiver.MouseState.wheelMoved){
		distancia -= fachada->receiver.MouseState.valorRuleta * ZOOMSPEED * deltaTime;
		if(distancia>MAXZOOM) distancia = MAXZOOM;
		if(distancia<MINZOOM) distancia = MINZOOM;
		fachada->receiver.MouseState.wheelMoved = false;
		//std::cout << "dist: " << distancia << std::endl;
	}

}