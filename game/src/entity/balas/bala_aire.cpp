#include "entity/balas/bala_aire.hpp"
#include "../../CONSTANTES.hpp"



bala_aire::bala_aire(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo){

float z1=2*cos(rot.Y*PI/180);
float x1=2*sin(rot.Y*PI/180); 
    lanzador.isPlayer = creador->isPlayer();
    lanzador.character = creador->claseElemental;
    setEntidad(creador);
    getEntidad()->setSumarBala();


    setPosition(vector3d(pos.X+x1*4,pos.Y,pos.Z+z1*4));


    setPositionI(pos);
    setPositionLast(pos);    
    setVelocity(vector3d(VelocidadAire*sin(rot.Y*PI/180),0,VelocidadAire*cos(rot.Y*PI/180)));
    setVelocityI(vector3d(VelocidadAire*sin(rot.Y*PI/180),0,VelocidadAire*cos(rot.Y*PI/180)));
    setGravedad(vector3d(gravedadAire*sin(rot.Y*PI/180),0,gravedadAire*cos(rot.Y*PI/180)));
    getImage().initBalaAire(pos,true);
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
        setDmg(dmgAire*dayo);    
        break;
    case 2:
        setDmg(dmgAire2*dayo);
        break;

    case 3:
        setDmg(dmgAire3*dayo);
        break;
    default:
        break;
    }

}

bool bala_aire::calcularVelocidad(float frame){       
 
    getvelocityI().X=getvelocityI().X+getGravedad().X*frame;
    getvelocityI().Z=getvelocityI().Z+getGravedad().Z*frame;

    

    setVelocity(vector3d(getvelocityI().X*frame,0,getvelocityI().Z*frame));   


   if(std::chrono::system_clock::now()-getTiempo()>std::chrono::milliseconds{TiemAire}){
        setTipo(muerto);
        return true;
   }
return false;
}


bool bala_aire::efectoBala(entity & ent){

   if(ent.hitEntity(getDmg(), lanzador)){        
        getEntidad()->addKill();
        ent.setTipo(muerto);             
        ent.getImage().setVisible(false);
        ent.setBehaviour(NINGUNO);
        
      }





return getMuerte();
}