#include "entity/balas/bala_tierra.hpp"
#include "../../CONSTANTES.hpp"



  

bala_tierra::bala_tierra(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo){
    float z1=2*cos(rot.Y*PI/180);
    float x1=2*sin(rot.Y*PI/180); 

    lanzador.isPlayer = creador->isPlayer();
    lanzador.character = creador->claseElemental;
    setEntidad(creador);
    getEntidad()->setSumarBala();

    setPosition(vector3d(pos.X+x1*4,pos.Y,pos.Z+z1*4));
    setPositionLast(pos);
    setPositionI(pos); 
    setVelocity(vector3d(0,0.5,0));
    setVelocityI(vector3d(VelocidadTierra*sin(rot.Y*PI/180),2,VelocidadTierra*cos(rot.Y*PI/180)));
    setGravedad(vector3d(0,gravedadTierra,0));
    getImage().initBalaTierra(pos,true);
    getImage().initImagen(getposition(),getRotation());  
    setHitBox(getImage().calcularHitBox()) ; 
    initPuntos();
    setRotation(rot);
    setRotationLast(rot);
    setVelocidadRotacion(vector3d(10,10,10));    
    setMuerte(NoMuereAlColisionar);    
    setTiempo(std::chrono::system_clock::now());    
    tickDmg=std::chrono::system_clock::now();

         switch (tier)
    {
   
    case 1:
        setDmg(dmgTierra*dayo);  
        break;
    case 2:
        setDmg(dmgTierra2*dayo);
        break;

    case 3:
        setDmg(dmgTierra3*dayo);
        break;
    default:
        break;
    }
}

bool bala_tierra::calcularVelocidad(float frame){
   
   setVelocity(vector3d(getvelocityI().X*frame,getvelocity().Y+(frame*getGravedad().Y),getvelocityI().Z*frame));   


   if(std::chrono::system_clock::now()-getTiempo()>std::chrono::milliseconds{TiemTierra}){
        setTipo(muerto);        
        return true;
   }
return false;
}


bool bala_tierra::efectoBala(entity & ent){
if(std::chrono::system_clock::now()-tickDmg>std::chrono::milliseconds{50}){
    tickDmg=std::chrono::system_clock::now();
  if(ent.hitEntity(getDmg(), lanzador)){        
        getEntidad()->addKill();
        ent.setTipo(muerto);             
        ent.getImage().setVisible(false);
        ent.setBehaviour(NINGUNO);
        
      }

}



return getMuerte();
}