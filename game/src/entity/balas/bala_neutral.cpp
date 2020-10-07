#include "entity/balas/bala_neutral.hpp"
#include "../../CONSTANTES.hpp"
#include <math.h>



    

bala_neutral::bala_neutral(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo){
float z1=2*cos(rot.Y*PI/180);
float x1=2*sin(rot.Y*PI/180); 
    lanzador.isPlayer = creador->isPlayer();
    lanzador.character = creador->claseElemental;
    setEntidad(creador);
    getEntidad()->setSumarBala();



    setPosition(vector3d(pos.X+x1*4,pos.Y,pos.Z+z1*4));


    setPositionI(pos);
    setPositionLast(pos);   
    setVelocityI(vector3d(VelocidadNeutral*sin(rot.Y*PI/180),0,VelocidadNeutral*cos(rot.Y*PI/180)));
    setVelocity(vector3d(0,0.3,0));
    setGravedad(vector3d(0,gravedadNeutral,0));
    getImage().initBalaAire(pos,true);
    getImage().initImagen(getposition(),getRotation());  
    setHitBox(getImage().calcularHitBox()) ; 
    initPuntos();
    setRotation(rot); 
    setRotationLast(rot);  
    setVelocidadRotacion(vector3d(10,10,10));
    setMuerte(MuereAlColisionar);
    setDmg(dmgNeutral*dayo);
    setTiempo(std::chrono::system_clock::now());
    
}

bool bala_neutral::calcularVelocidad(float frame){
  
       


    setVelocity(vector3d(getvelocityI().X*frame,getvelocity().Y+(frame*getGravedad().Y),getvelocityI().Z*frame));   
    


   if(std::chrono::system_clock::now()-getTiempo()>std::chrono::milliseconds{TiemNeutral}){
        setTipo(muerto);
        return true;
   }
return false;
}


bool bala_neutral::efectoBala(entity & ent){
    if(ent.hitEntity(getDmg(), lanzador)){        
        getEntidad()->addKill();
        ent.setTipo(muerto);             
        ent.getImage().setVisible(false);
        ent.setBehaviour(NINGUNO);
        
      }
    




return getMuerte();
}