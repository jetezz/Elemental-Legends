#include "StateIngame.hpp"
#include "entity/player.hpp"
#include "input.hpp"
#include "motor_fisicas/fisicas.hpp"
#include "entity/arma.hpp"
#include "entity/cofre.hpp"
#include <memory>
#include "behaviourTrees/BotIas/NormalBotIa.hpp"
#include "behaviourTrees/blackboard.hpp"
#include "IAScheduling.hpp"
#include "CONSTANTES.hpp"
#include "debugRender.hpp"
#include "estados/StateMachine.hpp"



//Estado de juego

int StateIngame::idCam = 0;          //La entidad que tiene que mirar la cámara
bool StateIngame::controlCam = true; //Si el jugador puede girar la entidad con la cámara.
entity* StateIngame::WatchingEnt = nullptr; //La entidad que estamos observando

StateIngame::~StateIngame(){
 


  
}

void nextCam(int Entityssize){

  StateIngame::idCam++;
  if(StateIngame::idCam>=Entityssize){
    StateIngame::idCam = 0;
  }
  if(StateIngame::idCam == 0) StateIngame::controlCam = true;
  else StateIngame::controlCam = false;
}
void prevCam(int Entityssize){
  StateIngame::idCam--;
  if(StateIngame::idCam<0){
    StateIngame::idCam = Entityssize-1;
  }
  if(StateIngame::idCam == 0) StateIngame::controlCam = true;
  else StateIngame::controlCam = false;
}

/*
*Crea NPC enemigos en posiciones aleatorias en el juego. Y les otorga IA
*/
void StateIngame::createNPCs(){
   //std::cout << character <<std::endl;
    for(int i = 0; i<numEnemies; i++){
      auto X = rand() % spawnRange*2-1 + (-spawnRange);
      auto Z = rand() % spawnRange*2-1 + (-spawnRange);
      int personaje = rand() % 6;
      vector3d pos = vector3d(X,alturaSpawn,Z);
      unique_ptr<enemy> NPC = make_unique<enemy>(pos,vector3d(5,5,5), personaje);
      
      NPC.get()->setBehaviour(NORMAL);
      ArrayEntity.emplace_back(std::move(NPC));
    
    }
}


/*
*Crea cofres
*/
void StateIngame::createCofres(){
    for(int i = 0; i<numCofres; i++){
      unique_ptr<cofre> CHEST = make_unique<cofre>();
      ArrayGameObject.emplace_back(std::move(CHEST));

    }

}


void StateIngame::UpdateIdCam(){
  

  if(check_cambioCamara(ArrayEntity.size())){
    WatchingEnt=ArrayEntity.at(idCam).get();
  }
  bool encontrada = false;
  for(std::vector<std::unique_ptr<entity> >::size_type i=0;i<ArrayEntity.size();i++){
    if(ArrayEntity.at(i).get()==WatchingEnt && !encontrada){
      encontrada = true;
      idCam = i;
    }
  }
 if(!encontrada){
    if(ArrayEntity.at(0)->getTipo()==0){
       controlCam = true;
    }else{
       controlCam = false;
    }
    idCam = 0;
    WatchingEnt=ArrayEntity.at(0).get();
 }
}
void StateIngame::init()
{

  
   fachada->initHud();
 

   fachada->setMouseVisibility(false); 

  /////////////////////////////////////////////////////////////entity
    ArrayEntity.reserve(20);
    

    //player
    unique_ptr<player> jugador = std::make_unique<player>(vector3d(-10, alturaSpawn, 5), character);      
    //putCharacter(std::move(jugador), character);
   
    ArrayEntity.emplace_back(std::move(jugador));


   
  //Crear todos los NPC
  createNPCs();
  //Crear todos los Cofres
  createCofres();
  
 

 


  //camara//
    camera = make_unique<camara>();
    WatchingEnt = jugador.get();
    controlCam = true;
    idCam = 0;

    Arraybalas.reserve(100);
    

  //Behaviour trees
    blackboard::setEntities(&ArrayEntity);  
    blackboard::setBalas(&Arraybalas);
    blackboard::setPickeables(&ArrayGameObject);
    //ArrayEntity.at(0)->setBehaviour(TEST);

    debug=false;



    ///////////////////////////////////////////
    //prueba con musica
   ///////////////////////////////////////////

   
   
    audio.StopEvent("event:/Música/Musica Menu");

    audio.PlayEvent("event:/Ambientes/Ambiente Juego");
    audio.Update();

    ///////////////////////////////////


  ///////input init
 
  //////////////
    motorFisico.initFisicas(&ArrayEntity,&Arraybalas,&ArrayGameObject);

    
   
}

void StateIngame::checkCameraColision(){

  for(std::vector<std::unique_ptr<gameObject>>::size_type i=0;i<ArrayGameObject.size();i++){
   
      if(WatchingEnt && TestRayOBBIntersection(WatchingEnt->getposition(),camera->getPosition(),ArrayGameObject.at(i)->getImage())){
        ArrayGameObject.at(i)->getImage().makeTransparent();
      }else{
        ArrayGameObject.at(i)->getImage().makeSolid();
      }
  }

}


void StateIngame::input(StateMachine *stados)
{
  if(partidaFinalizada){

    if(check_intro()){
      resetAll();
      
      stados->setEstadiscitas(est);
      stados->setGameOverState();
    }

  }
}



void StateIngame::update(float deltaTime)
{ 
  if(check_debug()){
    if(debug){
      debug=false;
    }else{
      debug=true;
    }
  }

motorFisico.moverTodo(deltaTime); //mover todas las entidades y balas
limpiarArrayEntidades();                                     //limpiar entidades o balas muertas
checkCameraColision();
runIAs(ArrayEntity);




if(ArrayEntity.size()>1){

  if(ArrayEntity.at(0)->getTipo()==jugador){

    check_playerKeys(*ArrayEntity.at(0).get(),deltaTime,Arraybalas);
     

  }else{ //el tipo 3 es que ha muerto el player

      finalizarPartida(false); 
    

   
  }
}else{

  if(!partidaFinalizada){
     audio.PlayEvent("event:/Ambientes/Ganar Partida");
     audio.Update();
     finalizarPartida(true);
  }


}

  
  UpdateIdCam(); //Actualizar el idCam, comprueba si se pulsa F1/F2 y actualiza si alguien muere.
  
  //IdCam es el objetivo a mostrar en la camara
  //ControlCam si la camara puede girar al objetivo, true solo en 0
  
  fachada->updateMouse(); //Actualizar el raton al centro y recoger su desplazamiento 
}



void StateIngame::drawHitBoxes(){
  for(std::vector<std::unique_ptr<entity>>::size_type i = 0; i < ArrayEntity.size(); i++){
    ArrayEntity.at(i)->getImage().drawBoundingBoxWithEdges(ArrayEntity.at(i)->getPuntos());
  }
  
   for(std::vector<std::unique_ptr<entity>>::size_type i = 0; i < ArrayGameObject.size(); i++){
    ArrayGameObject.at(i)->getImage().drawBoundingBoxWithEdges(ArrayGameObject.at(i)->getPuntos());
  }

    for(std::vector<std::unique_ptr<entity>>::size_type i = 0; i < Arraybalas.size(); i++){
    Arraybalas.at(i)->getImage().drawBoundingBoxWithEdges(Arraybalas.at(i)->getPuntos());
  }
}
void StateIngame::drawRegiones(){
  for (int i=-500; i<500 ;i+=50){
    fachada->drawLine(vector3d(i,5,-500),vector3d(i,5,500),vector3d(255,255,255));
    fachada->drawLine(vector3d(-500,5,i),vector3d(500,5,i),vector3d(255,255,255));

  }
}

void StateIngame::render(float percentick)
{
  for(std::vector<std::unique_ptr<entity> >::size_type i=0;i<ArrayEntity.size();i++){
    if(ArrayEntity.at(i)->getTipo()!=muerto)
    ArrayEntity.at(i)->actualizarPercentick(percentick);
  }

  for(std::vector<std::unique_ptr<bala> >::size_type i=0;i<Arraybalas.size();i++){
    Arraybalas.at(i)->actualizarPercentick(percentick);
  }
  camera.get()->updateThirdPersonPosition(ArrayEntity.at(idCam)->getImage(), controlCam);

  fachada->driver->beginScene(true, true, irr::video::SColor(255,113,113,133));
  if(debug){

    fachada->driver->setTransform(irr::video::ETS_WORLD, irr::core::IdentityMatrix); // inicializa las lineas para debuger
    //renderDebug(ArrayEntity);
    drawHitBoxes();
    drawRegiones();
   
  }
  
  fachada->smgr->drawAll();
  fachada->env->drawAll();
  fachada->driver->endScene();

}




void StateIngame::resetAll(){
  std::vector<std::unique_ptr<entity> >::size_type num =ArrayEntity.size();
  for (std::vector<std::unique_ptr<entity> >::size_type i=0;i<num;++i){
  ArrayEntity.at(0)->getImage().eliminarNode();
  ArrayEntity.erase(ArrayEntity.begin() );
  }

num =ArrayGameObject.size();
 for (std::vector<std::unique_ptr<gameObject> >::size_type i=0;i<num;++i){
    ArrayGameObject.at(0)->getImage().eliminarNode();
  ArrayGameObject.erase(ArrayGameObject.begin() );
  }

num =Arraybalas.size();

  for (std::vector<std::unique_ptr<bala> >::size_type i=0;i<num;++i){
    Arraybalas.at(0)->getImage().eliminarNode();
  Arraybalas.erase(Arraybalas.begin() );
  }
     
  
  
}


void StateIngame::finalizarPartida(bool victo){
    audio.StopEvent("event:/Efectos/Movimiento Normal");
    audio.StopEvent("event:/Ambientes/Ambiente Juego");
    audio.Update();
  controlCam = false;
  fachada->activarMensajeIntro(); 
  auto t1 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<float> fs = t1 - ArrayEntity.at(0)->getTiempo();
  est.tiempo=fs.count();
  est.muertes=ArrayEntity.at(0)->getKills();
  est.victoria=victo;
  partidaFinalizada=true;
}
void StateIngame::limpiarArrayEntidades(){
std::vector<std::unique_ptr<entity> >::size_type num =ArrayEntity.size();
  for (std::vector<std::unique_ptr<entity> >::size_type i=0;i<num;++i){
    if (ArrayEntity.at(i)->getTipo()==muerto && ArrayEntity.at(i)->getBalasDisparadas()==0){
      ArrayEntity.at(i)->getImage().eliminarNode();
      ArrayEntity.erase(ArrayEntity.begin() + i);      
      i--;
      num--;
    }
  }

  num=Arraybalas.size();
  for (std::vector<std::unique_ptr<entity> >::size_type i=0;i<num;++i){
    if (Arraybalas.at(i)->getTipo()==muerto){
      Arraybalas.at(i)->getEntidad()->setRestarBala();
      Arraybalas.at(i)->getImage().eliminarNode();
      Arraybalas.erase(Arraybalas.begin() + i);    
      i--;
      num--;
    }
  }





}

