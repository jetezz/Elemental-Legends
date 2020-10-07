

#include "debugRender.hpp"
#include "motor_grafico/fachadaIrrlicht.hpp"
#include "estados/StateIngame.hpp"


/*
*RenderDebug renderiza las físicas del juego para debugearlas
* @param ArrayEntity Es el array de entidades, se necesita para recorrer cada una y pintar su debug.
*/

void renderDebug(std::vector<unique_ptr <entity>> &ArrayEntity){
  fachadaIrrlicht * fachada = fachadaIrrlicht::getFachada(); 

  for(std::vector<std::unique_ptr<entity> >::size_type i=0;i<ArrayEntity.size();i++){
    //START: Si la entidad tiene un punto al que moverse, pinta una línea desde ella al punto.
    if(ArrayEntity.at(i)->hasWaypointToMove()){
    fachada->drawLine(ArrayEntity.at(i)->getposition(),ArrayEntity.at(i)->getWayPoint(),vector3d(50,20,50));
    }
    //END
  }
  
  int Arma = ArrayEntity.at(StateIngame::idCam)->getArma().gettipo();
  auto municion = ArrayEntity.at(StateIngame::idCam)->getArma().getMunicion();
  
  //START:: Aquí imprimimos información INDIVIDUAL de la entidad que está en la cámara.
  cout << "Soy: " << ArrayEntity.at(StateIngame::idCam).get() << endl;
  cout << "Mi vida: " << ArrayEntity.at(StateIngame::idCam)->getlife() << endl;
  cout << "Altura: " << ArrayEntity.at(StateIngame::idCam)->getposition().Y << endl;
  cout << "Tengo wayPoint: " << ArrayEntity.at(StateIngame::idCam)->hasWaypointToMove() << endl;
  cout << "Arma: ";
    switch (Arma)
    {
    case 0:
      cout << "[Varita común]" << endl;
      break;
    case 1:
      cout << "[Distorsionador]" << endl;
      break;
    case 2:
      cout << "[Tira y Afloja]" << endl;
      break;
    case 3:
      cout << "[Kaboom]" << endl;
      break;
    case 4:
      cout << "[Disrruptor]" << endl;
      break;
    case 5:
      cout << "[Medkit]" << endl;
      break;

    default:
      break;
    }

  cout << "Ammo: [" << municion.at(0) << "|" << municion.at(1) << "|" << municion.at(2) << "|" << municion.at(3) << "|" << municion.at(4) << "]" << endl;
  cout << "hasMedkit: [" << municion.at(5) << "]" << endl;
  if(ArrayEntity.at(StateIngame::idCam)->getData()){
    cout << "Closest Target: " << ArrayEntity.at(StateIngame::idCam)->getData()->b_closestEnemyInRange << endl;
    cout << "Atacando: " << ArrayEntity.at(StateIngame::idCam)->getData()->atacando << endl;
    cout << "Target Distance: " << ArrayEntity.at(StateIngame::idCam)->getData()->closestEnemyDistance << endl;
    
  }
  cout << "-------------------------------------------" << endl;
  //END
 
}








