#include "entity/powerUp/powerArmaAire.hpp"

powerArmaAire::powerArmaAire(vector3d& pos){
    settipo(tipoArmaAire);
    setPower(2);
    setPosition(vector3d(pos.X,pos.Y,pos.Z));    
    getImage().initPowerAire(getposition(),getHitBox());      
    setHitBox(vector3d(HitBoxPowerUp,HitBoxPowerUp,HitBoxPowerUp)) ;
    initPuntos();
}

void powerArmaAire::efectoPowerUp(entity &enti){
      if(enti.isPlayer()){
        switch (enti.claseElemental)
            {
            case AirCharacter:
                audio.PlayEvent("event:/Voces/Personaje Aire/Aire cura o mejora");
                audio.Update();
                break;
            case FireCharacter:
                audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego cura o mejora");
                audio.Update();
                break;
            case GroundCharacter:
                audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra cura o mejora");
                audio.Update();
                break;
            case LightCharacter:
                audio.PlayEvent("event:/Voces/Personaje Luz/Luz cura o mejora");
                audio.Update();
                break;
            case OscurityCharacter:
                audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad cura o mejora");
                audio.Update();
                break;
            case WaterCharacter:
                audio.PlayEvent("event:/Voces/Personaje Agua/Agua cura o mejora");
                audio.Update();
                break;
            default:
                break;
            } 
   }
    enti.getArma().setMunicion(gettipo());
    enti.consecuenciasIngame(ReajustarCargador);
}