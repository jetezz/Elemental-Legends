#include "entity/balas/bala_agua.hpp"
#include "../../CONSTANTES.hpp"
#include <math.h>


bala_agua::bala_agua(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo){
float z1=2*cos(rot.Y*PI/180);
float x1=2*sin(rot.Y*PI/180); 
    lanzador.isPlayer = creador->isPlayer();
    lanzador.character = creador->claseElemental;
    setEntidad(creador);
    getEntidad()->setSumarBala();
int tip =rand()%20;
tip++;


//sacar la bala random
if(tip>10)
tip=tip*-1;

int tip2 =rand()%20;
tip2++;

if(tip>10)
tip2=tip2*-1;
//

    setPosition(vector3d(pos.X+x1*4,pos.Y,pos.Z+z1*4));
    setPositionI(vector3d(pos.X+x1*4,pos.Y,pos.Z+z1*4));
    setPositionLast(pos);    
    setVelocityI(vector3d(VelocidadAgua*sin(rot.Y*PI/180)+tip,tip2,VelocidadAgua*cos(rot.Y*PI/180)+tip));    
    setGravedad(vector3d(0,gravedadAgua,0));
    getImage().initBalaAgua(pos,true);
    getImage().initImagen(getposition(),getRotation());  
    setHitBox(getImage().calcularHitBox()) ; 
    initPuntos();     
    setRotation(rot);   
    setRotationLast(rot);  
    setVelocidadRotacion(vector3d(10,10,10));   
    setMuerte(MuereAlColisionar);
    setTiempo(std::chrono::system_clock::now());
   
    switch (tier)
    {
   
    case 1:
        setDmg(dmgAgua*dayo);    
        break;
    case 2:
        setDmg(dmgAgua1*dayo);
        break;

    case 3:
        setDmg(dmgAgua2*dayo);
        break;
    default:
        break;
    }
    
    
    
    
  
    
    

    
}

bool bala_agua::calcularVelocidad(float frame){
  
       


    setVelocity(vector3d(getvelocityI().X*frame,getvelocityI().Y*frame,getvelocityI().Z*frame));   
    


   if(std::chrono::system_clock::now()-getTiempo()>std::chrono::milliseconds{TiemAgua}){
       setTipo(muerto);
        return true;
   }
return false;
}


bool bala_agua::efectoBala(entity & ent){

    if(ent.hitEntity(getDmg(), lanzador)){        
        getEntidad()->addKill();
        ent.setTipo(muerto);             
        ent.getImage().setVisible(false);
        ent.setBehaviour(NINGUNO);
        
      }
    
    




return getMuerte();
}