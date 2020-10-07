#include "input.hpp"
#include "entity/entity.hpp"
#include "ConstantesEfectosIngame.hpp"
#include "CONSTANTES.hpp"
#include <math.h>
#include "estados/StateIngame.hpp"
#include "motor_sonido/audio.hpp"
#include "estados/StateMachine.hpp"
#include "motor_sonido/audio.hpp"
//INPUT:
//INT CLOSE: PUNTERO PARE CERRAR LA PANTALLA 
//VELOCIDAD: PUNTERO AL VECTOR DE VELOCIDADES A MODIFICAR
//RECEIVER: 
//FRAMEDELTATIME: TIEMPO QUE HA TRANSCURRIDO PARA HACER LA MULTIPICLACION CON LA CONSTANTE MOVEMENT_SPEED

#define PI 3.14159265
#define ROTSPEED 3 //Velocidad de rotación del jugador
static fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();




static CAudioEngine audio;


void check_close(){
///cerrar ventana
if(fachada->receiver.IsKeyDown(irr::KEY_ESCAPE)){
	fachada->device->closeDevice();
	std::cout << "================" << std::endl;
	std::cout << "Cerrando juego.." << std::endl;
	std::cout << "================" << std::endl;
}
}
//cerrar el juego cuando se le da a la opcion de salir en el menu
void cerrar(){
	if(fachada->receiver.IsKeyDown(irr::KEY_RETURN)){
		


    		audio.PlayEvent("event:/Menús/Seleccion Opcion");
    		audio.Update();

    		///////////////////////////////////
		fachada->device->closeDevice();
		std::cout << "================" << std::endl;
		std::cout << "Cerrando juego.." << std::endl;
		std::cout << "================" << std::endl;

	}

}

/*
*Check_cambioCamara comprueba si se pulsa F1 o F2. Si es así cambia la cámara a la siguiente entidad
* @param tamanoArray. Se le pasa el tamaño del array de entidades para no mover la cámara a una entidad inexistente.
*/
static bool camChangePressed = false; //Esto es para que solo se ejecute una vez cada vez que se pulsa el boton
static bool debugPressed=false;
bool check_cambioCamara(int tamanoArray){

	if(fachada->receiver.IsKeyDown(irr::KEY_F1)){
		if(camChangePressed) return false;
		prevCam(tamanoArray);
		camChangePressed = true;
		return true;
	}
	if(fachada->receiver.IsKeyDown(irr::KEY_F2)){
		if(camChangePressed) return false;
		nextCam(tamanoArray);
		camChangePressed = true;
		return true;
	}
	camChangePressed = false;
	return false;
}
bool check_debug(){

	if(fachada->receiver.IsKeyDown(irr::KEY_F7)){
		if(debugPressed) return false;

		debugPressed = true;
		return true;
	}

	debugPressed = false;
	return false;
}
static std::chrono::time_point<std::chrono::system_clock> comienzoPasos;
static bool walkingSoundPlaying {false};
static bool walkPressed {false};
void check_playerKeys(entity &jugador,const float frameDeltaTime,std::vector<unique_ptr <bala>> &Arraybalas){

//colocar velocidades


	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_W)){
			walkPressed = true;
			jugador.getvelocity().Z += MOVEMENT_SPEED*cos(jugador.getRotation().Y*PI/180);
			jugador.getvelocity().X += MOVEMENT_SPEED*sin(jugador.getRotation().Y*PI/180); 
				
	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_S)){
			walkPressed = true;
			jugador.getvelocity().Z -= MOVEMENT_SPEED*cos(jugador.getRotation().Y*PI/180);
			jugador.getvelocity().X -= MOVEMENT_SPEED*sin(jugador.getRotation().Y*PI/180); 		
	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_A)){
			walkPressed = true;
			jugador.getvelocity().Z -= MOVEMENT_SPEED*cos((jugador.getRotation().Y+90)*PI/180);
			jugador.getvelocity().X -= MOVEMENT_SPEED*sin((jugador.getRotation().Y+90)*PI/180);  		
	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_D)){
			walkPressed = true;
			jugador.getvelocity().Z += MOVEMENT_SPEED*cos((jugador.getRotation().Y+90)*PI/180);
			jugador.getvelocity().X += MOVEMENT_SPEED*sin((jugador.getRotation().Y+90)*PI/180);  		
	
	}

	if(fachada->receiver.IsKeyDown(irr::KEY_SPACE)){
		
			jugador.getvelocity().Y += MOVEMENT_JUMP; 
	}

	///CAMBIAR ARMA

	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_1)){
			if(jugador.getArma().getMunicion().at(ArmaNeutral)>0)
			jugador.getArma().setTipo(ArmaNeutral) ;
			jugador.consecuenciasIngame(ArmaNeutral);
			

			 
	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_2)){
			if(jugador.getArma().getMunicion().at(ArmaAgua)>0)
			jugador.getArma().setTipo(ArmaAgua) ; 
			jugador.consecuenciasIngame(ArmaAgua);

			


	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_3)){
			if(jugador.getArma().getMunicion().at(ArmaAire)>0)
			jugador.getArma().setTipo(ArmaAire) ;  
			jugador.consecuenciasIngame(ArmaAire);
			


		
	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_4)){
			if(jugador.getArma().getMunicion().at(ArmaFuego)>0)
			jugador.getArma().setTipo(ArmaFuego) ;
			jugador.consecuenciasIngame(ArmaFuego);
			


	}
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_5)){
			if(jugador.getArma().getMunicion().at(ArmaTierra)>0)
			jugador.getArma().setTipo(ArmaTierra) ;
			jugador.consecuenciasIngame(ArmaTierra);
			


	}
	static bool changeWeapon = false; //Esto es para que solo se ejecute una vez cada vez que se pulsa el boton
	bool entra=false;	
	if(fachada->receiver.IsKeyDown(irr::KEY_TAB)){
		entra=true;
		if(changeWeapon){		
		}
		else{
			int tipo=jugador.getArma().gettipo();
			bool entra=false;
			tipo++;
			for (int i = tipo; i<6;i++){
				if(jugador.getArma().getMunicion().at(i)>0 && !entra){
					jugador.getArma().setTipo(i) ;
					jugador.consecuenciasIngame(i);
					entra=true;
				}
				
			}
			if (!entra){
					jugador.getArma().setTipo(0) ;
					jugador.consecuenciasIngame(0);
				}
				
		}
		changeWeapon = true;
		
	}
	if(!entra)
	changeWeapon = false;
	
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_Q)){
			if(jugador.getArma().getMunicion().at(PowerCura)>0)
			jugador.getArma().setTipo(PowerCura) ;
			jugador.consecuenciasIngame(PowerCura);
	


	}



	if (fachada->receiver.SMouseLeftClicked()){
		jugador.disparar(Arraybalas);
	}
	if(fachada->receiver.MouseState.Dx){
		auto x = 0;		
		auto y = - fachada->receiver.MouseState.Dx*ROTSPEED;
		auto z = 0;
		auto vec = vector3d(x,y,z);
		jugador.setVelocidadRotacion(vec); 
	}
/*
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_P)){
		auto x = 0;		
		auto y = 190;
		auto z = 0;
		auto vec = vector3d(x,y,z);
		jugador.setVelocidadRotacion(vec); 
	


	}
	*/
	
/////////////////

	if(walkPressed){

		if(!walkingSoundPlaying){

			comienzoPasos = std::chrono::system_clock::now();
			walkingSoundPlaying = true;
			audio.PlayEvent("event:/Efectos/Movimiento Normal");
        	audio.Update();
			
		}
		std::chrono::duration<float, ratio<1,1>> tiempoPasado =  std::chrono::system_clock::now() - comienzoPasos;

		if(tiempoPasado.count()>=8) walkingSoundPlaying = false;

	}else{
		walkingSoundPlaying = false;
		audio.StopEvent("event:/Efectos/Movimiento Normal");
        audio.Update();		
	}

      

    walkPressed = false;
}

static bool takeItemPressed = false; //Esto es para que solo se ejecute una vez cada vez que se pulsa el boton
bool check_abrirCofre(){
	if(fachada->receiver.IsKeyDown(irr::KEY_KEY_E)){
		if(takeItemPressed) return false;
		///////////////////////////////////////////
    	//prueba con musica
    	/////////////////////////////////////////
   
    	//audio.LoadEvent("event:/Efectos/Abrir Cofre");




    ///////////////////////////////////

		takeItemPressed = true;
		return true;
	}

	takeItemPressed = false;
	return false;
}

static bool takeReturn = false; //Esto es para que solo se ejecute una vez cada vez que se pulsa el boton
bool check_intro(){
	
		if(fachada->receiver.IsKeyDown(irr::KEY_RETURN)){
		if(takeReturn) return false;

		takeReturn = true;
		return true;
	}
	takeReturn = false;
	return false;
}


//esto sería para saltar la animación del juego si no quieres verla todas las veces que inicias el juego, actualmente hay una imagen
static bool pressenter= false;
bool iniciarjuego(){
	bool result = false;
	if(fachada->receiver.IsKeyDown(irr::KEY_RETURN)){
		if(pressenter) return result;
		///////////////////////////////////////////
    	//prueba con musica
    	/////////////////////////////////////////
   
    	//Event("event:/Menús/Seleccion Opcion");


    	audio.PlayEvent("event:/Menús/Seleccion Opcion");
    	audio.Update();

    ///////////////////////////////////
		result  = true;
		pressenter = true;
		return result;
	}
	pressenter = false;
	return result; 
}
//cuando se le da a la opcion jugar una vez elegido el personaje
bool jugar(){
	bool result = false;
	if(fachada->receiver.IsKeyDown(irr::KEY_RETURN)){
		if(pressenter) return result;
		///////////////////////////////////////////
    	//prueba con musica
    	/////////////////////////////////////////
   
    	//audio.LoadEvent("event:/Menús/Seleccion Opcion");


    	audio.PlayEvent("event:/Menús/Seleccion Opcion");
    	audio.Update();

    ///////////////////////////////////
		result  = true;
		pressenter = true;
		return result;
	}
	pressenter = false;
	return result;
}
//cuando se le da a la opcion jugar del menu
bool empezarjuego(){
	bool result = false;
	if(fachada->receiver.IsKeyDown(irr::KEY_RETURN)){
		if(pressenter) return result;
		///////////////////////////////////////////
    	//prueba con musica
    	/////////////////////////////////////////
   
    	//audio.LoadEvent("event:/Menús/Seleccion Opcion");


    	audio.PlayEvent("event:/Menús/Seleccion Opcion");
    	audio.Update();

    ///////////////////////////////////
		result  = true;
		pressenter = true;
		return result;
	}
	pressenter = false;
	return result;
}
//para seleccionar las diferentes opciones del menu
static bool changeoption= false;
int selectmenuoption(int option){
	
		if((fachada->receiver.IsKeyDown(irr::KEY_DOWN) ||  fachada->receiver.IsKeyDown(irr::KEY_KEY_S)) && option!=4){
			if(changeoption) return -1;
			///////////////////////////////////////////
    		//prueba con musica
    		/////////////////////////////////////////
   
    		//audio.LoadEvent("event:/Menús/Cambio de Opciones en Menu");


    		audio.PlayEvent("event:/Menús/Cambio de Opciones en Menu");
    		audio.Update();

    		///////////////////////////////////
			++option;
			
			std::cout << option << std::endl;
			changeoption = true;
			return option;
		}
		if((fachada->receiver.IsKeyDown(irr::KEY_UP) || fachada->receiver.IsKeyDown(irr::KEY_KEY_W)) && option!=1){
			if(changeoption) return -1;
			///////////////////////////////////////////
    		//prueba con musica
    		/////////////////////////////////////////
   
    		//audio.LoadEvent("event:/Menús/Cambio de Opciones en Menu");


    		audio.PlayEvent("event:/Menús/Cambio de Opciones en Menu");
    		audio.Update();

    		///////////////////////////////////
			--option;
			std::cout << option << std::endl;
			changeoption = true;
			return option;
		}
	
	changeoption = false;
	
	return option;
}
//cuando se selecciona la opcion creditos del menu, actualmente es un mensaje en consola
static bool selection = false;
void verCreditos(){
	if(fachada->receiver.IsKeyDown(irr::KEY_RETURN)){
		if(selection) return ;
		///////////////////////////////////////////
    		//prueba con musica
    		/////////////////////////////////////////
   			
    		//audio.LoadEvent("event:/Menús/Seleccion Opcion");


    		audio.PlayEvent("event:/Menús/Seleccion Opcion");
    		audio.Update();

    		///////////////////////////////////
		std::cout << "========" << std::endl;
		std::cout << "Créditos" << std::endl;
		std::cout << "========" << std::endl;
		selection = true;
		return;
	}
	selection = false;
}
static bool chara= false;
//para seleccinar los diferentes personajes
int selectcharacter(int i){
	if((fachada->receiver.IsKeyDown(irr::KEY_RIGHT) ||  fachada->receiver.IsKeyDown(irr::KEY_KEY_D)) && i!=5){
		if(chara) return -1;

    		audio.PlayEvent("event:/Menús/Cambio de Opciones en Menu");
    		audio.Update();

    		///////////////////////////////////
		++i;
		
		if(i==1){/////////////TERMINAR//////////////////
			stopevents();
    	audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego en Racha");
    	audio.Update();

		}
		if(i==2){
			stopevents();


    	audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra en Racha");
    	audio.Update();

		}
		if(i==3){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Luz/Luz en Racha");
    	audio.Update();

		}
		if(i==4){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad en Racha");
    	audio.Update();

		}
		if(i==5){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Agua/Agua en Racha");
    	audio.Update();

		}
		
		chara = true;
		return i;
	}
	if((fachada->receiver.IsKeyDown(irr::KEY_RIGHT) || fachada->receiver.IsKeyDown(irr::KEY_KEY_D))&& i==5){
		if(chara) return -1;

    		audio.PlayEvent("event:/Menús/Cambio de Opciones en Menu");
    		audio.Update();

		i=0;
		 if(i==0){
			 stopevents();
 
    	audio.PlayEvent("event:/Voces/Personaje Aire/Aire en Racha");
    	audio.Update();

		}
		
		chara = true;
		return i;
	}
	if((fachada->receiver.IsKeyDown(irr::KEY_LEFT) || fachada->receiver.IsKeyDown(irr::KEY_KEY_A)) && i!=0){
		if(chara) return -1;

    		audio.PlayEvent("event:/Menús/Cambio de Opciones en Menu");
    		audio.Update();

		--i;
		 if(i==0){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Aire/Aire en Racha");
    	audio.Update();

		}
		if(i==1){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Fuego/Fuego en Racha");
    	audio.Update();

		}
		if(i==2){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Tierra/Tierra en Racha");
    	audio.Update();

		}
		if(i==3){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Luz/Luz en Racha");
    	audio.Update();

		}
		if(i==4){
			stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Oscuridad/Oscuridad en Racha");
    	audio.Update();

		}
	
		chara = true;
		return i;
	}
	if((fachada->receiver.IsKeyDown(irr::KEY_LEFT) || fachada->receiver.IsKeyDown(irr::KEY_KEY_A)) && i==0){
		if(chara) return -1;

    		audio.PlayEvent("event:/Menús/Cambio de Opciones en Menu");
    		audio.Update();
		i=5;
		if(i==5){
			
		stopevents();

    	audio.PlayEvent("event:/Voces/Personaje Agua/Agua en Racha");
    	audio.Update();

		}
		chara = true;
		return i;
	}
	chara = false;
	return i;
}

void stopevents(){
	audio.StopEvent("event:/Voces/Personaje Fuego/Fuego en Racha");
	audio.StopEvent("event:/Voces/Personaje Tierra/Tierra en Racha");
	audio.StopEvent("event:/Voces/Personaje Luz/Luz en Racha");
	audio.StopEvent("event:/Voces/Personaje Oscuridad/Oscuridad en Racha");
	audio.StopEvent("event:/Voces/Personaje Aire/Aire en Racha");
	audio.StopEvent("event:/Voces/Personaje Agua/Agua en Racha");
}