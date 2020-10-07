#pragma once

#include "motor_grafico/IAniMesh.hpp"
#include "coordenada.hpp"

class Render
{
private:
    /* data */
    IAnimMeshNode node;
public:
    Render();
    ~Render();
   IAnimMeshNode pintarModelo( const char* rutaModelo , const char* rutaTextura, Coordenada& coord, bool colisionable);
   
   IAnimMeshNode* createPlayer(vector3d vec,bool colision);
   IAnimMeshNode* createEnemy(vector3d vec,bool colision);
   
   IAnimMeshNode* createCofre(vector3d vec,bool colision);

   IAnimMeshNode* createBulletFuego(vector3d,bool);                                                                                          
   IAnimMeshNode* createBulletAgua(vector3d,bool);
   IAnimMeshNode* createBulletTierra(vector3d,bool);
   IAnimMeshNode* createBulletAire(vector3d,bool);
};

