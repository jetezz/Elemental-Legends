#include "entity/balas/bala_fuego.hpp"
#include "../../CONSTANTES.hpp"






bala_fuego::bala_fuego(vector3d pos,vector3d rot, entity* creador, int tier, float& dayo){

    float z1=2*cos(rot.Y*PI/180);
    float x1=2*sin(rot.Y*PI/180); 
    lanzador.isPlayer = creador->isPlayer();
    lanzador.character = creador->claseElemental;
    setEntidad(creador);
    setPosition(vector3d(pos.X+x1*16,pos.Y+50,pos.Z+z1*16));
    getEntidad()->setSumarBala();


    setPositionI(pos);
    setPositionLast(pos);    
    setVelocityI(vector3d(VelocidadFuego*sin(rot.Y*PI/180),2,VelocidadFuego*cos(rot.Y*PI/180)));
    getImage().initBalaFuego(pos,true);
    getImage().initImagen(getposition(),getRotation());  
    setHitBox(getImage().calcularHitBox()) ; 
    initPuntos();
    setRotation(rot);    
    setRotationLast(rot);
    setVelocidadRotacion(vector3d(10,10,10));
    setMuerte(NoMuereAlColisionar);    
    setTiempo(std::chrono::system_clock::now());
   
    tickDmg=std::chrono::system_clock::now();
    reduccionHit=std::chrono::system_clock::now();
      switch (tier)
    {
   
    case 1:
        setDmg(dmgFuego*dayo);    
        break;
    case 2:
        setDmg(dmgFuego2*dayo);
        break;

    case 3:
        setDmg(dmgFuego3*dayo);
        break;
    default:
        break;
    }

}

bool bala_fuego::calcularVelocidad(float frame){
    
       


    setVelocity(vector3d(getvelocityI().X*frame,0,getvelocityI().Z*frame));   


    if(std::chrono::system_clock::now()-getTiempo()>std::chrono::milliseconds{accion1}){
    

    
    setVelocity(vector3d(0,-VelocidadFuego*frame,0));  
   }

    if(getposition().Y<=getpositionI().Y){
    
    setVelocity(vector3d(0,0,0));
    if(std::chrono::system_clock::now()-reduccionHit>std::chrono::milliseconds{100}){
        tamano-=30;
        reduccionHit=std::chrono::system_clock::now();
    }  
    transfor=vector3d(tamano,tamano,tamano);
    setHitBox(vector3d(transfor.X/5,transfor.Y/5,transfor.Z/5));
    getImage().setScale(transfor); //para hacer que la bala de fuego explote en el momento en el que llega al suelo

    
   }


   if(std::chrono::system_clock::now()-getTiempo()>std::chrono::milliseconds{TiemFuego}){

        setTipo(muerto);
        return true;
   }
return false;
}

bool bala_fuego::efectoBala(entity & ent){
 if(std::chrono::system_clock::now()-tickDmg>std::chrono::milliseconds{100}){
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