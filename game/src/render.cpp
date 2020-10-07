#include "render.hpp"
#include "coordenada.hpp"


//constructor
Render::Render(){

}


//Dibuja el modelo
IAnimMeshNode Render::pintarModelo( const char* rutaModelo , const char* rutaTextura, Coordenada& coord, bool colisionable){
    
     IAnimMesh modeloMalla;
     IAnimMeshNode mallaNodo;

    modeloMalla = *modeloMalla.crearObj(rutaModelo);
    mallaNodo = *mallaNodo.crearNodoMalla(& modeloMalla,rutaTextura,coord,colisionable);

    return mallaNodo;

}

//renderiza al modelo del player
IAnimMeshNode* Render::createPlayer(vector3d vec,bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/player.obj", "modelos/player.png", coord, colision);//dibuja un cubo
    
    
    node.setEscala(5);
	
	return &node;
}

//renderiza el modelo de enemigo
IAnimMeshNode* Render::createEnemy(vector3d vec,bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/char_enemi.obj", "modelos/char_enemi.png", coord, colision);//dibuja un cubo
    
    
    node.setEscala(5);
	
	return &node;
}

//renderiza el modelo de cofre

IAnimMeshNode* Render::createCofre(vector3d vec, bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/cofre.obj", "modelos/cofre.png", coord,colision);//dibuja un cubo

    node.setEscala(6);
	
	return &node;
}

// renderiza las balas 

IAnimMeshNode* Render::createBulletFuego(vector3d vec,bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/balaFuego.obj", "modelos/balaFuego.png", coord,colision);//dibuja un cubo

    node.setEscala(6);
	
	return &node;
}

IAnimMeshNode* Render::createBulletAgua(vector3d vec,bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/balaAgua.obj", "modelos/balaAgua.png", coord,colision);//dibuja un cubo

    node.setEscala(6);
	
	return &node;
}

IAnimMeshNode* Render::createBulletTierra(vector3d vec,bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/balaTierra.obj", "modelos/balaTierra.png", coord,colision);//dibuja un cubo

    node.setEscala(6);
	
	return &node;
}

IAnimMeshNode* Render::createBulletAire(vector3d vec, bool colision){

    Coordenada coord(vec.X, vec.Y, vec.Z);

	node = pintarModelo("modelos/balaAire.obj", "modelos/balaAire.png", coord,colision);//dibuja un cubo

    node.setEscala(6);
	
	return &node;
}


//Destructor
Render::~Render(){



}