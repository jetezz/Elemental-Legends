

#include "motor_fisicas/fisicas.hpp"
#include "CONSTANTES.hpp"
#include "motor_fisicas/myMotorF.hpp"
#include "entity/entity.hpp"
#include <math.h>
#include <stdio.h>

 void fisicas::initFisicas(std::vector<unique_ptr <entity>> *ArEnt,std::vector<std::unique_ptr <bala>> *ArBal,std::vector<unique_ptr <gameObject>> *ArGO){

   if(ArEnt)
   ArrayEntity=ArEnt;

    if(ArBal)
   ArrayDeBalas=ArBal;

    if(ArGO)
   ArrayGameObject=ArGO;
   

 }

void fisicas::moverTodo(float frame){

   if(ArrayDeBalas && ArrayDeBalas->size()>0){
   
     for(auto& entidad : *ArrayDeBalas) {       
        entidad->calcularVelocidad(frame);
        moverEntidadOptimizado(*entidad, frame);
    }
  }

   for(auto& entidad : *ArrayEntity) {      
        entidad->calcularVelocidad(frame);
        moverEntidad(*entidad, frame);
    }
  
  
 
 
}


 void fisicas::moverEntidad(entity &enti,float frame){
  vector3d velocidadAux(0,0,0);
  vector3d rotacionAux(0,0,0);
  vector3d posicionSiguiente(0,0,0);
  vector3d rotacionSiguiente(0,0,0);
  std::vector<vector3d>puntosLast;
  puntosLast.resize(8);
  puntosLast=enti.getPuntos();
  
  
 

  enti.setPositionLast(enti.getposition());
  enti.setRotationLast(enti.getRotation());


  if (enti.getvelocity().X!=0){    
    velocidadAux.X=enti.getvelocity().X*frame;
    velocidadAux.Y=0;
    velocidadAux.Z=0;

    posicionSiguiente=myMotorF::move(enti.getposition(),velocidadAux);

    if(posicionSiguiente.X>1000 || posicionSiguiente.X<-1000)
    posicionSiguiente=enti.getposition();
    enti.setPuntos(myMotorF::getPuntos(posicionSiguiente,enti.getHitBox(),enti.getRotation()));
   
  
    
      if(noGameObject==colisionConEntidades(enti.getposition(),posicionSiguiente,enti.getPuntos(),enti.getRegion())){
        enti.setPosition(posicionSiguiente);
        puntosLast=enti.getPuntos();
      }else{
        enti.setPuntos(puntosLast);  
      }
  }

    if (enti.getvelocity().Y!=0){    
    velocidadAux.X=0;
    velocidadAux.Y=enti.getvelocity().Y*frame;
    velocidadAux.Z=0;

    posicionSiguiente=myMotorF::move(enti.getposition(),velocidadAux);
    
      if(posicionSiguiente.Y>30)
      posicionSiguiente=enti.getposition();
    enti.setPuntos(myMotorF::getPuntos(posicionSiguiente,enti.getHitBox(),enti.getRotation()));
  
    
      if(noGameObject==colisionConEntidades(enti.getposition(),posicionSiguiente,enti.getPuntos(),enti.getRegion())){
        enti.setPosition(posicionSiguiente);
        puntosLast=enti.getPuntos();
      }else{
         enti.setPuntos(puntosLast);   
      }
  }

  


  //Comprobar al caer
        if(enti.getvelocity().Y==0 && enti.getposition().Y-enti.getHitBox().Y/2>0){ //aqui compruebo si choca con el suelo que en este caso seria la y 0 y si no estoy chocando hago que baje por gravedad
            velocidadAux.Y=-gravedad*frame;
            posicionSiguiente=myMotorF::move(enti.getposition(),velocidadAux);          
            enti.setPuntos(myMotorF::getPuntos(posicionSiguiente,enti.getHitBox(),enti.getRotation()));

            if(noGameObject==colisionConEntidades(enti.getposition(),posicionSiguiente,enti.getPuntos(),enti.getRegion())){
             enti.setPosition(posicionSiguiente);             
             puntosLast=enti.getPuntos();

        }else{
           enti.setPuntos(puntosLast); 
        }
        }

   if (enti.getvelocity().Z!=0){    
    velocidadAux.X=0;
    velocidadAux.Y=0;
    velocidadAux.Z=enti.getvelocity().Z*frame;

    posicionSiguiente=myMotorF::move(enti.getposition(),velocidadAux);    
    if(posicionSiguiente.Z>1000 || posicionSiguiente.Z<-1000)
    posicionSiguiente=enti.getposition();
    enti.setPuntos(myMotorF::getPuntos(posicionSiguiente,enti.getHitBox(),enti.getRotation()));
  
    
      if(noGameObject==colisionConEntidades(enti.getposition(),posicionSiguiente,enti.getPuntos(),enti.getRegion())){
        enti.setPosition(posicionSiguiente);
        puntosLast=enti.getPuntos();
      }else{
         enti.setPuntos(puntosLast); 
      }
  }
  
  enti.setVelocity(vector3d(0,0,0));
  enti.setRegion(myMotorF::getRegion(enti.getPuntos()));

  //cout<<"regiones"<<endl;
  //for (auto &reg : enti.getRegion()){
  //  cout<<"posicionX"<<reg.X<<endl;
  //  cout<<"posicionY"<<reg.Z<<endl;
//
  //}
 //



    /////////////rotar en y
    if(enti.getVelocidadRotacion().Y!=0){  
    velocidadAux.X=0;
    velocidadAux.Y=0;
    velocidadAux.Z=0;

    rotacionAux.Y=enti.getVelocidadRotacion().Y*frame;

    posicionSiguiente=myMotorF::move(enti.getposition(),velocidadAux);
    rotacionSiguiente=myMotorF::move(enti.getRotation(),rotacionAux);

    enti.setPuntos(myMotorF::getPuntos(posicionSiguiente,enti.getHitBox(),rotacionSiguiente));

    if(noGameObject==colisionConEntidades(enti.getposition(),posicionSiguiente,enti.getPuntos(),enti.getRegion())){

      enti.setRotation(rotacionSiguiente);
      puntosLast=enti.getPuntos();
    
    }else{
      enti.setPuntos(puntosLast); 
      
     
    }

    enti.setVelocidadRotacion(vector3d(0,0,0));
    }

       //////comprobar el choque con los objetos
       
    velocidadAux.X=enti.getvelocity().X*frame;
    velocidadAux.Y=enti.getvelocity().Y*frame;
    velocidadAux.Z=enti.getvelocity().Z*frame;

     if(ArrayGameObject->size()>0){       
      int numGameObject=colisionConGameObject(enti.getposition(),enti.getposition(),enti.getPuntos(),enti.getRegion());  
                
                if(noGameObject!=numGameObject){
                  enti.consecuenciasIngame(PonerMensajeHud);   
                  if(ArrayGameObject->at(numGameObject)->efectoColision(enti,*ArrayGameObject)){
                        enti.consecuenciasIngame(ArrayGameObject->at(numGameObject)->getPower());
                        ArrayGameObject->at(numGameObject)->getImage().eliminarNode();
                        ArrayGameObject->erase(ArrayGameObject->begin() + numGameObject);                       
                    }                   
                }else{
                  enti.consecuenciasIngame(QuitarMensajeHud);
                }
     }
            

    
}

void fisicas::moverEntidadOptimizado(bala &enti, float frame){   
   

    enti.setPositionLast(enti.getposition());
    enti.setRotationLast(enti.getRotation());

    std::vector<vector3d> puntosLast=enti.getPuntos();
    vector3d posicionSiguiente=myMotorF::move(enti.getposition(),enti.getvelocity());  
    vector3d rotacionSiguiente=myMotorF::move(enti.getRotation(),enti.getVelocidadRotacion());  

    enti.setPuntos(myMotorF::getPuntos(posicionSiguiente,enti.getHitBox(),enti.getRotation()));

    int numGameObject=colisionConEntidades(enti.getposition(),enti.getposition(),enti.getPuntos(),enti.getRegion());
  
    
      if(noGameObject!=numGameObject){        
        bool muerte=enti.efectoColision(*ArrayEntity->at(numGameObject),*ArrayGameObject);
        if (muerte)
        enti.setTipo(muerto); 
      }
      enti.setPosition(posicionSiguiente);
      enti.setRotation(rotacionSiguiente);
      enti.setRegion(myMotorF::getRegion(enti.getPuntos()));

      
    
      
  }


int fisicas::colisionConEntidades(vector3d &posicionLast,vector3d &posicionSiguiente,std::vector<vector3d> &puntos,std::vector<vector2d> &regiones){
 
  
  

  for(std::vector<std::unique_ptr<entity>>::size_type i=0; i<ArrayEntity->size();i++){
    if(myMotorF::coincidenRegiones(regiones,ArrayEntity->at(i)->getRegion())){
      if(!esLaMismaEntidad(posicionLast,ArrayEntity->at(i)->getposition())){     
        if(myMotorF::colision(posicionSiguiente,puntos,ArrayEntity->at(i)->getposition(),ArrayEntity->at(i)->getPuntos())){
          return i;
        }
        
      }
    }
  }
  return noGameObject;


}

int fisicas::colisionConGameObject(vector3d &posicionLast,vector3d &posicionSiguiente,std::vector<vector3d> &puntos,std::vector<vector2d> &regiones){
  for(std::vector<std::unique_ptr<entity>>::size_type i=0; i<ArrayGameObject->size();i++){    
    if(myMotorF::coincidenRegiones(regiones,ArrayGameObject->at(i)->getRegion())){
      if(!esLaMismaEntidad(posicionLast,ArrayGameObject->at(i)->getposition())){        
        if(myMotorF::colision(posicionSiguiente,puntos,ArrayGameObject->at(i)->getposition(),ArrayGameObject->at(i)->getPuntos())){
          return i;
        }
        
      }
    }
  }
    return noGameObject;
}








bool fisicas::esLaMismaEntidad(vector3d & pos1, vector3d& pos2){
  if(pos1.X==pos2.X && pos1.Y==pos2.Y && pos1.Z==pos2.Z)
  return true;

  return false;
}



std::vector<vector3d> fisicas::getPuntos(vector3d &posicion, vector3d &hitboxinit, vector3d &rotacion){
  return myMotorF::getPuntos( posicion,hitboxinit,rotacion);
}

 std::vector<vector2d> fisicas::getRegiones(std::vector<vector3d> &puntos){
   return myMotorF::getRegion(puntos);


 }

 


