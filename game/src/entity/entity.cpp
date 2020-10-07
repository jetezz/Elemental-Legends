#include "entity.hpp"
#include "balas/bala_fuego.hpp"
#include "behaviourTrees/blackboard.hpp"
#include "behaviourTrees/BotIas/NormalBotIa.hpp"
#include "ConstantesEfectosIngame.hpp"
#include "CONSTANTES.hpp"
#include "../motor_sonido/audio.hpp"
#include "motor_fisicas/fisicas.hpp"

static CAudioEngine audio;
/////////////////
///funciones/////
/////////////////


//esta funcion llama al disparar del arma y este le devuelve una consecuencia(actualizar el cargador en el hud , quitar el arma en el hud porque ya no hay balas, curarse porque dispara el powerup cura...)
//despues llama a el consecuenciasIngame del entity y dependiendo si es player o enemy realiza unas funciones o otras
void entity::disparar(std::vector<std::unique_ptr <bala>> &ArrayDeBalas){
    int consecDisparo=SinConsecuencia;

    consecDisparo=weapon.disparar(ArrayDeBalas,getposition(),getImage().getRotation(),this);
    if(consecDisparo!=SinConsecuencia)
    consecuenciasIngame(consecDisparo);        
          
        blackboard::addPuntoEscuchado(getposition());
}


//


//esta funcion es llamada cualdo el enemigo recibe daño y compruebo si muere o no y actualizo el hud para que diga la vida que tiene
bool entity::hitEntity(float& dmg, lanzadorBala& origen){
    
    bool muerte=false;
    vida-=dmg;
    if (vida<=0)
    muerte=true;
    
    playHitSounds(origen,muerte);

    consecuenciasIngame(ReajustarVida);
   
    return muerte;
}



bool entity::efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject){

    return false;
}
//Devuelve true o false si es un objeto recogible.
bool entity::isPickeable(){
    return false;
}
void entity::lookAt(vector3d vec){
    getImage().lookAt(vec);
}

bool entity::isAlive(){

    if(vida<=0) return false;

    return true;
}


///////
//GET//
///////
int &entity::getlife(){
    return vida;
}

vector3d& entity::getvelocity(){
    return velocidad;
}



uint8_t entity::getvidatotal(){
    return vidatotal;
}



arma& entity::getArma(){
    return weapon;
}
/*
*Al lanzar entity run, ejecuta el arbol de comportamiento que tiene asociado
*/
void entity::run(){
    if(behaviour!=nullptr)
    behaviour->run(data.get());
}

blackboard* entity::getData(){
    return data.get();
}
float& entity::getDayo(){
    return danyo;
}
int entity::getTipo(){
    return tipo;
}

int entity::getKills(){
    return enemigosAsesinados;
}
int entity::getBalasDisparadas(){
    return balasDisparadas;
}




///////
//SET//
///////




void entity::setVelocity(vector3d vec){
    velocidad.X=vec.X*velocidadextra;
    velocidad.Y=vec.Y*velocidadextra;
    velocidad.Z=vec.Z*velocidadextra;
}
void entity::setVida(int hp){
    vida=hp;
    if(vida>vidatotal) vida = vidatotal;
}

void entity::setArma(arma &weap){
    weapon=weap;
}
void entity::setVidaTotal(int hp){
    vidatotal=hp;
}

void entity::setDanyo(float damage){
    danyo = damage;
}
void entity::setTipo(int tip){
    tipo=tip;
}
void entity::setBalasDisparadas(int bal){
    balasDisparadas=bal;
}
void entity::setSumarBala(){
    balasDisparadas++;
}
void entity::setRestarBala(){
    balasDisparadas--;
}
void entity::addKill(){
    enemigosAsesinados++;
    playKillSounds();
}


/*
*Asignarle un arbol de comportamiento la entidad
* @param comportamiento un tipo de BotIa, define el behaviour del bot puede ser "NINGUNO" o "NORMAL"
*
*/
#include "../behaviourTrees/BotIas/testBotIa.hpp"
void entity::setBehaviour(comportamiento ia){
  //   behaviour = std::move(&comportamiento);
    
     switch (ia)
     {
     case NORMAL:
         behaviour = make_unique<NormalBotIa>();
         break;
     case NINGUNO:
         behaviour.release();
         break;
     case TEST:
          behaviour = make_unique<testBotIa>();
         break;
     default:
         break;
     }
     data = std::make_unique<blackboard>(this);
     
}

void entity::playKillSounds(){
 if(isPlayer() && enemigosAsesinados == 3){
        audio.StopEvent("event:/Efectos/Kill");
        audio.StopEvent("event:/Efectos/Sonido Impacto Proyectil");
        switch (claseElemental)
            {
            case AirCharacter:
                audio.StopEvent("event:/Voces/Personaje Aire/Aire Mata a Tierra");
                audio.PlayEvent("event:/Voces/Personaje Aire/Aire en Racha");
    	        audio.Update();
                break;
            case FireCharacter:
                audio.StopEvent("event:/Voces/Personaje Fuego/Fuego mata a otro de fuego");
                audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego en Racha");
    	        audio.Update();
                break;
            case GroundCharacter:
                audio.StopEvent("event:/Voces/Personaje Tierra/Tierra mata a otra Tierra");
                audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra en Racha");
    	        audio.Update();
                break;
            case LightCharacter:
                audio.StopEvent("event:/Voces/Personaje Luz/Luz mata a Oscuridad");
                audio.PlayEvent("event:/Voces/Personaje Luz/Luz en Racha");
    	        audio.Update();
                break;
            case OscurityCharacter:
                audio.StopEvent("event:/Voces/Personaje Oscuridad/Oscuridad mata a Luz");
                audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad en Racha");
    	        audio.Update();
                break;
            case WaterCharacter:
                audio.StopEvent("event:/Voces/Personaje Agua/Agua mata a Fuego");
                audio.PlayEvent("event:/Voces/Personaje Agua/Agua en Racha");
    	        audio.Update();
                break;
            default:
                break;
            }
    }
}//Reproducir los sonidos de racha de muerte

void entity::playHitSounds(lanzadorBala& origen, bool muerte){
/*
*Reproducción de sonidos. 2 casos, que quien recibe el danyo sea un player,
*en este caso se reproduce el sonido de recibir danyo de cada clase, o de morir de cada clase si muere.
*Si quien recibe danyo es un bot, solo se reproduce si el lanzador es un jugador, ya que si no es una 
*locura. Si quien recibe el golpe muere suena un sonido, sino, suena otro de impacto satisfactorio.
*Si, es un switch anidado bastante grande, pero no importa ya que es un punto no crítico del programa.
*/

    if(isPlayer()){
        if(muerte){
            switch (claseElemental)
            {
            case AirCharacter:
                audio.PlayEvent("event:/Voces/Personaje Aire/Aire Muere");
    	        audio.Update();
                break;
            case FireCharacter:
                audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego Muere");
    	        audio.Update();
                break;
            case GroundCharacter:
                audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra Muere");
    	        audio.Update();
                break;
            case LightCharacter:
                audio.PlayEvent("event:/Voces/Personaje Luz/Luz Muere");
    	        audio.Update();
                break;
            case OscurityCharacter:
                audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad Muere");
    	        audio.Update();
                break;
            case WaterCharacter:
                audio.PlayEvent("event:/Voces/Personaje Agua/Agua Muere");
    	        audio.Update();
                break;
            default:
                break;
            } 
        }else{
            switch (claseElemental)
            {
            case AirCharacter:
                audio.PlayEvent("event:/Voces/Personaje Aire/Aire recibe danyo");
    	        audio.Update();
                break;
            case FireCharacter:
                audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego recibe danyo");
    	        audio.Update();
                break;
            case GroundCharacter:
                audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra recibe danyo");
    	        audio.Update();
                break;
            case LightCharacter:
                audio.PlayEvent("event:/Voces/Personaje Luz/Luz recibe danyo");
    	        audio.Update();
                break;
            case OscurityCharacter:
                audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad recibe danyo");
    	        audio.Update();
                break;
            case WaterCharacter:
                audio.PlayEvent("event:/Voces/Personaje Agua/Agua recibe danyo");
    	        audio.Update();
                break;
            default:
                break;
            } 
        }
       

    }else{
        if(origen.isPlayer){

            if(muerte){
                if(origen.character == WaterCharacter && claseElemental == FireCharacter){
                    audio.PlayEvent("event:/Voces/Personaje Agua/Agua mata a Fuego");
                    audio.Update();
                }else if(origen.character == AirCharacter && claseElemental == GroundCharacter){
                    audio.PlayEvent("event:/Voces/Personaje Aire/Aire Mata a Tierra");
                    audio.Update();
                }else if(origen.character == FireCharacter && claseElemental == FireCharacter){
                    audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego mata a otro de fuego");
                    audio.Update();
                }else if(origen.character == LightCharacter && claseElemental == OscurityCharacter){
                    audio.PlayEvent("event:/Voces/Personaje Luz/Luz mata a Oscuridad");
                    audio.Update();
                }else if(origen.character == OscurityCharacter && claseElemental == LightCharacter){
                    audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad mata a Luz");
                    audio.Update();
                }else if(origen.character == GroundCharacter && claseElemental == GroundCharacter){
                    audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra mata a otra Tierra");
                    audio.Update();
                }else{
                    audio.PlayEvent("event:/Efectos/Kill");
                    audio.Update();
                }
                
            }else{
                audio.PlayEvent("event:/Efectos/Sonido Impacto Proyectil");
                audio.Update();
            }

        }
        
    }
}//Reproducir sonidos de impacto, muerte, kills y frases elementales especificas.
