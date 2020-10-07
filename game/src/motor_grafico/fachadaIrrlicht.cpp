#include "fachadaIrrlicht.hpp"
#include "irrlicht/driverChoice.h"
#include "motor_grafico/mynode.hpp"
#include "motor_grafico/vector3d.hpp"
#include <math.h>
#include <string>




fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();

/////////////////////////////////
/////funciones clase fachada/////
/////////////////////////////////







fachadaIrrlicht::~fachadaIrrlicht()
{
	
}

void fachadaIrrlicht::cambiarPosicion(vector3d& vec,MyNode_t& img,vector3d& rotacion){
    
    img.getNode()->setPosition(vec.transformar());
    img.setRotation(rotacion);


    
    
    img.getNode()->updateAbsolutePosition();   
    img.setPoints();
    
    
 //img.getNode()->setScale(tran.transformar());

}

void fachadaIrrlicht::updateMouse(){
    
	if(device && device->isWindowFocused()){
        auto oldPos = device->getCursorControl()->getPosition();
		device->getCursorControl()->setPosition(0.5f,0.5f);
        auto newPos = device->getCursorControl()->getPosition();
        receiver.reset(oldPos.X, oldPos.Y, newPos.X,newPos.Y);
    }
	
            
}
void fachadaIrrlicht::setMouseVisibility(bool i){
 
        device->getCursorControl()->setVisible(i);

}
float fachadaIrrlicht::getMouseDx(){
	return receiver.MouseState.Dx;
}

float fachadaIrrlicht::getMouseDy(){
	return receiver.MouseState.Dy;
}

/////////////////////
///tipos de objetos//
/////////////////////

/*
*Pinta una línea desde el punto inicial al final
* @param PosInicial es el punto inicial de la linea
* @param PosFin es el punto final de la linea
* @param color es el color que tendrá la linea. Un vector3d con RGB
*/
void fachadaIrrlicht::drawLine(vector3d posInicial, vector3d posFin, vector3d color){
   driver->draw3DLine(posInicial.transformar(),posFin.transformar(),irr::video::SColor(color.X,color.Y,color.Z,255));
}


 void fachadaIrrlicht::createmapa(int tam){
	node = smgr->addCubeSceneNode(tam);//dibuja un cubo
    
    node->setPosition(vector3d(0,-tam/2,0).transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/tierra2.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	
}

 irr::scene::ISceneNode* fachadaIrrlicht::createEnemy(vector3d &vec,vector3d &hit){
	node = smgr->addCubeSceneNode(hit.X);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/wall.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}


 irr::scene::ISceneNode* fachadaIrrlicht::createBulletNeutral(vector3d &vec,vector3d &hit){
	node = smgr->addCubeSceneNode(hit.X);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/neutral2.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}

 irr::scene::ISceneNode* fachadaIrrlicht::createBulletFuego(vector3d &vec,vector3d &hit){
	node = smgr->addCubeSceneNode(hit.X);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/Fuego2.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}
 irr::scene::ISceneNode* fachadaIrrlicht::createBulletAgua(vector3d &vec,vector3d &hit){
	node = smgr->addCubeSceneNode(hit.X);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/agua2.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}
 irr::scene::ISceneNode* fachadaIrrlicht::createBulletTierra(vector3d &vec,vector3d &hit){
	node = smgr->addCubeSceneNode(hit.X);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/tierra2.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}
 irr::scene::ISceneNode* fachadaIrrlicht::createBulletAire(vector3d &vec,vector3d &hit){
	node = smgr->addCubeSceneNode(hit.X);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/viento2.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}

 irr::scene::ISceneNode* fachadaIrrlicht::createCofre(vector3d &vec,vector3d& hit){
	node = smgr->addCubeSceneNode(5);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/chest.jpg"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}
 irr::scene::ISceneNode* fachadaIrrlicht::createVida(vector3d &vec,vector3d& hit){
	node = smgr->addCubeSceneNode(2);//dibuja un cubo

    node->setPosition(vec.transformar());
    node->setMaterialTexture(0, driver->getTexture("resources/powerVida2.png"));
    node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	
	
	return node;
}

bool TestRayOBBIntersection(
	vector3d origen,
    vector3d fin,
    MyNode_t& nodo
){  

    glm::vec3 pInicio {};

    pInicio.x = origen.X;
    pInicio.y = origen.Y;
    pInicio.z = origen.Z;

    glm::vec3 pFinal {};

    
    pFinal.x = fin.X;
    pFinal.y = fin.Y;
    pFinal.z = fin.Z;

    //Punto medio
    glm::vec3 midLinea = (pInicio + pFinal);
    midLinea.x = midLinea.x * 0.5;
    midLinea.y = midLinea.y * 0.5;
    midLinea.z = midLinea.z * 0.5;
    
    //Dirección
    glm::vec3 dir = glm::normalize(pFinal - pInicio);
    
    auto dx = pFinal.x-pInicio.x;
    auto dy = pFinal.y-pInicio.y;
    auto dz = pFinal.z-pInicio.z;

    //Media distancia
    auto halfDistance = sqrtf(dx*dx+dy*dy+dz*dz) * 0.5;

    glm::vec3 AABBmin {};
    AABBmin.x = nodo.getMinAABB().X;
    AABBmin.y = nodo.getMinAABB().Y;
    AABBmin.z = nodo.getMinAABB().Z;

    glm::vec3 AABBmax {};
    AABBmax.x = nodo.getMaxAABB().X;
    AABBmax.y = nodo.getMaxAABB().Y;
    AABBmax.z = nodo.getMaxAABB().Z;

    auto e = AABBmax - AABBmin; //Box extent
    e.x  = e.x * 0.5;
    e.y  = e.y * 0.5;
    e.z  = e.z * 0.5;

    auto t = AABBmax + AABBmin; //Box Center - linea center
    t.x  = t.x * 0.5;
    t.y  = t.y * 0.5;
    t.z  = t.z * 0.5;
    t = t - midLinea;

        if ((fabs(t.x) > e.x + halfDistance * fabs(dir.x)) ||
            (fabs(t.y) > e.y + halfDistance * fabs(dir.y)) ||
            (fabs(t.z) > e.z + halfDistance * fabs(dir.z)) )
            return false;

		auto r = e.y * fabs(dir.z) + e.z * fabs(dir.y);
		if (fabs(t.y*dir.z - t.z*dir.y) > r )
			return false;

		r = e.x * fabs(dir.z) + e.z * fabs(dir.x);
		if (fabs(t.z*dir.x - t.x*dir.z) > r )
			return false;

        r = e.x * fabs(dir.z) + e.y * fabs(dir.x);
        if (fabs(t.x*dir.y - t.y*dir.x) > r)
            return false;

		return true;

}
/////HUD

void fachadaIrrlicht::initHud(){
    
    background->clear();
    initTier();
    env = device->getGUIEnvironment();
    ajustarPantalla();
    hudPantalla= env->addImage(driver->getTexture("resources/hud/HUD720.png"),	irr::core::position2d<int>(100+relativox,425+relativoy*2));
                                //mira = env->addImage(driver->getTexture("resources/hud/Mira720.png"),	irr::core::position2d<int>(580+relativox,340+relativoy));
    hudArmaNeutral(1);
    hudMunicion();
    balas=env->addStaticText(L"100000", irr::core::rect<irr::s32>(240+relativox,670+relativoy*2,1000,1000));
    vida=env->addStaticText(L"Vida = 20", irr::core::rect<irr::s32>(590+relativox,600+relativoy*2,1000,1000));
    env->addStaticText(L"1", irr::core::rect<irr::s32>(379+relativox,706+relativoy*2,1000,1000));
    env->addStaticText(L"2", irr::core::rect<irr::s32>(479+relativox,706+relativoy*2,1000,1000));
    env->addStaticText(L"3", irr::core::rect<irr::s32>(579+relativox,706+relativoy*2,1000,1000));
    env->addStaticText(L"4", irr::core::rect<irr::s32>(679+relativox,706+relativoy*2,1000,1000));
    env->addStaticText(L"5", irr::core::rect<irr::s32>(779+relativox,706+relativoy*2,1000,1000));
    env->addStaticText(L"Q", irr::core::rect<irr::s32>(979+relativox,706+relativoy*2,1000,1000));
    env->addStaticText(L"<---------TAB---------->", irr::core::rect<irr::s32>(568+relativox,620+relativoy*2,1000,1000));

    
    
}





//HUD ARMAS
void fachadaIrrlicht::hudArmaNeutral(uint8_t opcion){

    if(opcion==1){
        ArmaNeutral= env->addImage(driver->getTexture("resources/hud/Basico720.png"),	irr::core::position2d<int>(350+relativox,640+relativoy*2));
    }
    else{
        ArmaNeutral->remove();
    }

}
void fachadaIrrlicht::hudArmaNeutralb(uint8_t opcion){
    
    if(opcion==1){
        ArmaNeutral= env->addImage(driver->getTexture("resources/hud/Basico720n.png"),	irr::core::position2d<int>(350+relativox,640+relativoy*2));
    }
    else{
        ArmaNeutral->remove();
    }

}
void fachadaIrrlicht::hudArmaAgua(uint8_t opcion){
    if(opcion==1){
        ArmaAgua= env->addImage(driver->getTexture("resources/hud/Rafaga720.png"),	irr::core::position2d<int>(450+relativox,640+relativoy*2));
    }
    else{
        ArmaAgua->remove();
    }

}
void fachadaIrrlicht::hudArmaAguab(uint8_t opcion){
    if(opcion==1){
        ArmaAgua= env->addImage(driver->getTexture("resources/hud/Rafaga720n.png"),	irr::core::position2d<int>(450+relativox,640+relativoy*2));
    }
    else{
        ArmaAgua->remove();
    }

}

void fachadaIrrlicht::hudArmaAire(uint8_t opcion){
    if(opcion==1){
        ArmaAire= env->addImage(driver->getTexture("resources/hud/Vaiven720.png"),	irr::core::position2d<int>(550+relativox,640+relativoy*2));
      }
    else{
        ArmaAire->remove();
    }
}

void fachadaIrrlicht::hudArmaAireb(uint8_t opcion){
    if(opcion==1){
        ArmaAire= env->addImage(driver->getTexture("resources/hud/Vaiven720n.png"),	irr::core::position2d<int>(550+relativox,640+relativoy*2));
      }
    else{
        ArmaAire->remove();
    }
}
void fachadaIrrlicht::hudArmaFuego(uint8_t opcion){
    if(opcion==1){
        ArmaFuego= env->addImage(driver->getTexture("resources/hud/Explosion720.png"),	irr::core::position2d<int>(650+relativox,640+relativoy*2));
      }
    else{
        ArmaFuego->remove();
    }
}
void fachadaIrrlicht::hudArmaFuegob(uint8_t opcion){
    if(opcion==1){
        ArmaFuego= env->addImage(driver->getTexture("resources/hud/Explosion720n.png"),	irr::core::position2d<int>(650+relativox,640+relativoy*2));
      }
    else{
        ArmaFuego->remove();
    }
}
void fachadaIrrlicht::hudArmaTierra(uint8_t opcion){
    if(opcion==1){
        ArmaTierra= env->addImage(driver->getTexture("resources/hud/Sniper720.png"),	irr::core::position2d<int>(750+relativox,640+relativoy*2));
      }
    else{
        ArmaTierra->remove();
    }

}

void fachadaIrrlicht::hudArmaTierrab(uint8_t opcion){
    if(opcion==1){
        ArmaTierra= env->addImage(driver->getTexture("resources/hud/Sniper720n.png"),	irr::core::position2d<int>(750+relativox,640+relativoy*2));
      }
    else{
        ArmaTierra->remove();
    }

}
void fachadaIrrlicht::hudMunicion(){
    env->addImage(driver->getTexture("resources/hud/Municion720.png"),	irr::core::position2d<int>(170+relativox,650+relativoy*2));
}


//HUD POWERUP
void fachadaIrrlicht::hudPowerVida(uint8_t opcion){
    if(opcion==1){
        powerVida= env->addImage(driver->getTexture("resources/hud/Curacion720.png"),	irr::core::position2d<int>(950+relativox,640+relativoy*2));
      }
    else{
        powerVida->remove();
    }

}
void fachadaIrrlicht::hudPowerVidab(uint8_t opcion){
    if(opcion==1){
        powerVida= env->addImage(driver->getTexture("resources/hud/Curacion720n.png"),	irr::core::position2d<int>(950+relativox,640+relativoy*2));
      }
    else{
        powerVida->remove();
    }

}
//HUD TIER
void fachadaIrrlicht::initTier(){
    primtier1=false;
    primtier2=false;
    primtier3=false;
    primtier4=false;
}
void fachadaIrrlicht::elimiraTier(int num){
    
             switch (num)
            {
            case 1:
                tier1->remove();
                primtier1=false;
                break;
            case 2:
                tier2->remove();
                primtier2=false;
                
                break;
            case 3:
                tier3->remove();
                primtier3=false;               
                break;
            case 4:
                tier4->remove();
                primtier4=false;               
                break;            
            default:
                break;
}
}

void fachadaIrrlicht::hudTier1(int pos,int num){
    
        switch (num)
        {
        case 1:
            if(!primtier1){
                tier1=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
                primtier1=true;
            }
            tier1->remove();
            tier1=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
        break;
        case 2:
          if(!primtier2){
                tier2=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
                primtier2=true;
            }
            tier2->remove();    
            tier2=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
         break;
         case 3:
         if(!primtier3){
                tier3=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
                primtier3=true;
            }
            tier3->remove();
            tier3=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
         break;
         case 4:
           if(!primtier4){
                tier4=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
                primtier4=true;
            }
            tier4->remove();
            tier4=env->addImage(driver->getTexture("resources/hud/bronce720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
        break;
        
        default:
            break;
        }
       
     
    
}
void fachadaIrrlicht::hudTier2(int pos,int num){
  
        
        switch (num)
        {
        case 1:
            tier1->remove();
            tier1=env->addImage(driver->getTexture("resources/hud/plata720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
        break;
        case 2:
            tier2->remove();
            tier2=env->addImage(driver->getTexture("resources/hud/plata720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
         break;
         case 3:
            tier3->remove();
            tier3=env->addImage(driver->getTexture("resources/hud/plata720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
         break;
         case 4:
            tier4->remove();
            tier4=env->addImage(driver->getTexture("resources/hud/plata720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
        break;
        
        default:
            break;
        }
      
   
    
}

void fachadaIrrlicht::hudTier3(int pos,int num){
    
        
          switch (num)
        {
        case 1:
            tier1->remove();
            tier1=env->addImage(driver->getTexture("resources/hud/oro720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
        break;
        case 2:
            tier2->remove();
            tier2=env->addImage(driver->getTexture("resources/hud/oro720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
         break;
         case 3:
            tier3->remove();
            tier3=env->addImage(driver->getTexture("resources/hud/oro720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
         break;
         case 4:
            tier4->remove();
            tier4=env->addImage(driver->getTexture("resources/hud/oro720.png"),	irr::core::position2d<int>(pos+relativox,634+relativoy*2));
        break;
        
        default:
            break;
        }
    
    
    
}



//HUD MENSAJES
void fachadaIrrlicht::activarMensaje(){
    
    mensaje= env->addImage(driver->getTexture("resources/pulsae.png"),	irr::core::position2d<int>(600+relativox,500+relativoy*2)); 

} 



void fachadaIrrlicht::desactivarMensaje(){
    mensaje->remove();

}


void fachadaIrrlicht::numeroBalas(int num){
    balas->remove();

    string s=to_string(num);
    std::wstring widestr = std::wstring(s.begin(), s.end());
    const wchar_t* widecstr = widestr.c_str();
   
  
  balas=env->addStaticText(widecstr, irr::core::rect<irr::s32>(240+relativox,670+relativoy*2,1000,1000));

}

void fachadaIrrlicht::numeroVida(int num){
    string s="Vida = ";
    vida->remove();

    s+=to_string(num);
    std::wstring widestr = std::wstring(s.begin(), s.end());
    const wchar_t* widecstr = widestr.c_str();
   
  
  vida=env->addStaticText(widecstr, irr::core::rect<irr::s32>(590+relativox,600+relativoy*2,1000,1000));

}
void fachadaIrrlicht::activarMensajeIntro(){
    intro=env->addImage(driver->getTexture("resources/intro.png"),	irr::core::position2d<int>(600+relativox,450+relativoy*2)); 

}
void fachadaIrrlicht::estadisticaTiempo(float num){
    string s= "Tiempo=";
    s+=to_string(num);
    s +="s";
    std::wstring widestr = std::wstring(s.begin(), s.end());
    const wchar_t* widecstr = widestr.c_str();
   
  background->addStaticText(widecstr, irr::core::rect<irr::s32>(120,200,250,500));
 
}
void fachadaIrrlicht::estadisticaKills(int num){
    string s= "kills=";
     s +=to_string(num);   
    std::wstring widestr = std::wstring(s.begin(), s.end());
    const wchar_t* widecstr = widestr.c_str();
   
  
  estKills=env->addStaticText(widecstr, irr::core::rect<irr::s32>(120,400,250,500));
}


//para poner la imagen de fondo inicial, más adelante será un vídeo
void fachadaIrrlicht::ajustarPantalla(){

    int anchoaux=driver->getScreenSize().Width;
    int altoaux=driver->getScreenSize().Height;
    if(anchoInicial!=altoaux || altoInicial!=anchoaux){
        relativox=driver->getScreenSize().Width;
        relativoy=driver->getScreenSize().Height;
        anchoInicial=driver->getScreenSize().Width;
        altoInicial=driver->getScreenSize().Height;
        relativox-=1280;
        relativoy-=720;
        relativox++;
        relativoy++;
        relativox=relativox/2;
        relativoy=relativoy/2;
}
    }

    
 
void fachadaIrrlicht::crearinterfaceinicio(){
    ajustarPantalla();
    
       
    background = device->getGUIEnvironment();
    background->addImage(driver->getTexture("resources/menuPrincipal/Cartel Elemental Legends720.png"), irr::core::position2d<int>(0+relativox,0+relativoy));
}
void fachadaIrrlicht::crearinterfaceinicio2(){
    ajustarPantalla();
    background->clear();
    
       
    background = device->getGUIEnvironment();
    background->addImage(driver->getTexture("resources/menuPrincipal/Cartel Elemental Legends720.png"), irr::core::position2d<int>(0+relativox,0+relativoy));
}

//para poner la imagen de fondo y de los botones en el menu
void fachadaIrrlicht::crearinterfacemenu(){ 
    ajustarPantalla();
    background->clear();

   
    background->addImage(driver->getTexture("resources/menuPrincipal/Fondo menu seleccion2.png"), irr::core::position2d<int>(relativox,relativoy));
    background->addImage(driver->getTexture("resources/menuPrincipal/boton Jugar.png"), irr::core::position2d<int>(300,120));
    background->addImage(driver->getTexture("resources/56661091-créditos-icono-botón-de-internet-sobre-fondo-blanco-.jpg"), irr::core::position2d<int>(300,220));
    background->addImage(driver->getTexture("resources/56660392-icono-salir-botón-de-internet-sobre-fondo-blanco-.jpg"), irr::core::position2d<int>(300,320));
}
//para cambiar la imagen de la opcion seleccionada
void fachadaIrrlicht::selectOption(int option){    
    ajustarPantalla();
    background->clear();
    

    
    background->addImage(driver->getTexture("resources/menuPrincipal/Fondo menu seleccion2.png"), irr::core::position2d<int>(0+relativox,0+relativoy));
    switch (option)
    {
    case 1:
        background->addImage(driver->getTexture("resources/menuPrincipal/boton jugar720on.png"), irr::core::position2d<int>(550+relativox,120+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton credito720.png"), irr::core::position2d<int>(550+relativox,240+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton multij720.png"), irr::core::position2d<int>(550+relativox,360+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton salir720.png"), irr::core::position2d<int>(550+relativox,480+relativoy));

        break;
    case 2: 
        background->addImage(driver->getTexture("resources/menuPrincipal/boton jugar720.png"), irr::core::position2d<int>(550+relativox,120+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton credito720on.png"), irr::core::position2d<int>(550+relativox,240+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton multij720.png"), irr::core::position2d<int>(550+relativox,360+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton salir720.png"), irr::core::position2d<int>(550+relativox,480+relativoy));

        break;
    case 3:
        background->addImage(driver->getTexture("resources/menuPrincipal/boton jugar720.png"), irr::core::position2d<int>(550+relativox,120+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton credito720.png"), irr::core::position2d<int>(550+relativox,240+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton multij720on.png"), irr::core::position2d<int>(550+relativox,360+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton salir720.png"), irr::core::position2d<int>(550+relativox,480+relativoy));

        break;
    case 4:
        background->addImage(driver->getTexture("resources/menuPrincipal/boton jugar720.png"), irr::core::position2d<int>(550+relativox,120+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton credito720.png"), irr::core::position2d<int>(550+relativox,240+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton multij720.png"), irr::core::position2d<int>(550+relativox,360+relativoy));
        background->addImage(driver->getTexture("resources/menuPrincipal/boton salir720on.png"), irr::core::position2d<int>(550+relativox,480+relativoy));
        
        break;
    default:
        break;
    }

    
}



//para poner la imagen de fondo y del personaje inicial
void fachadaIrrlicht::crearinterfacepersonajes(){ 
    background->clear();///////////ANYADIR LAS FOTOS///////////////////////
   // background2 = device->getGUIEnvironment();
    background->addImage(driver->getTexture("resources/fondopersonajes.png"), irr::core::position2d<int>(1,1));
    background->addImage(driver->getTexture("resources/aire.jpg"), irr::core::position2d<int>(225,60));
    background->addImage(driver->getTexture("resources/flechasizquierda.png"), irr::core::position2d<int>(100,220));
    background->addImage(driver->getTexture("resources/flechasderecha.png"), irr::core::position2d<int>(500,220));
   //background->addImage(driver->getTexture("resources/56661091-créditos-icono-botón-de-internet-sobre-fondo-blanco-.jpg"), irr::core::position2d<int>(300,220));
   // background->addImage(driver->getTexture("resources/56660392-icono-salir-botón-de-internet-sobre-fondo-blanco-.jpg"), irr::core::position2d<int>(300,320));
}

//para cambiar la imagen del personajes escogido
void fachadaIrrlicht::selectCharacter(int option){

    
    ajustarPantalla();
    background->clear();

    background->addImage(driver->getTexture("resources/menuSeleccion/FondoSeleccion780.png"), irr::core::position2d<int>(relativox,relativoy));
    background->addImage(driver->getTexture("resources/menuSeleccion/flex I720.png"), irr::core::position2d<int>(150+relativox,300+relativoy));
    background->addImage(driver->getTexture("resources/menuSeleccion/flex D720.png"), irr::core::position2d<int>(1000+relativox,300+relativoy));

    

   
    

    if(option==0){
         background->addImage(driver->getTexture("resources/menuSeleccion/Aire720.png"), irr::core::position2d<int>(350+relativox,180+relativoy));
    }else if(option==1){
        background->addImage(driver->getTexture("resources/menuSeleccion/Fuego720.png"), irr::core::position2d<int>(350+relativox,180+relativoy));
    }else if(option==2){
        background->addImage(driver->getTexture("resources/menuSeleccion/Tierra720.png"), irr::core::position2d<int>(350+relativox,180+relativoy));
    }else if(option==3){
        background->addImage(driver->getTexture("resources/menuSeleccion/Luz720.png"), irr::core::position2d<int>(350+relativox,180+relativoy));
    }else if(option==4){
         background->addImage(driver->getTexture("resources/menuSeleccion/Oscuridad720.png"), irr::core::position2d<int>(350+relativox,180+relativoy));
    }else if(option==5){
         background->addImage(driver->getTexture("resources/menuSeleccion/Agua720.png"), irr::core::position2d<int>(350+relativox,180+relativoy));
    }
    
}

void fachadaIrrlicht::createGameOver(float tiempo, int muertes,bool vitoria){
    ajustarPantalla();
    background->clear();

    
    background->addImage(driver->getTexture("resources/menuPrincipal/Fondo menu seleccion2.png"), irr::core::position2d<int>(0+relativox,0+relativoy));

    string s= "Tiempo=";
    s+=to_string(tiempo);
    s +="s";
    std::wstring widestr = std::wstring(s.begin(), s.end());
    const wchar_t* widecstr = widestr.c_str();
   
    background->addStaticText(widecstr, irr::core::rect<irr::s32>(120+relativox,500+relativoy,250,1000));


    s= "kills=";
    s +=to_string(muertes);   
    widestr = std::wstring(s.begin(), s.end());
    widecstr = widestr.c_str();
   
  
    background->addStaticText(widecstr, irr::core::rect<irr::s32>(120+relativox,600+relativoy,250,1000));
    background->addImage(driver->getTexture("resources/intro.png"),	irr::core::position2d<int>(600+relativox,450+relativoy));

    if(vitoria){
    background->addImage(driver->getTexture("resources/menuGameOver/ganado720.png"), irr::core::position2d<int>(175+relativox,40+relativoy));
    }
    else{
     background->addImage(driver->getTexture("resources/menuGameOver/Perdido720.png"), irr::core::position2d<int>(175+relativox,40+relativoy));   
    }

}


bool pointIntersectsNode(const vector3d& p, MyNode_t& nodo)
{   
    auto MinEdge = nodo.getMinAABB();
    auto MaxEdge = nodo.getMaxAABB();

	return (p.X >= MinEdge.X && p.X <= MaxEdge.X &&
		p.Y >= MinEdge.Y && p.Y <= MaxEdge.Y &&
		p.Z >= MinEdge.Z && p.Z <= MaxEdge.Z);
}