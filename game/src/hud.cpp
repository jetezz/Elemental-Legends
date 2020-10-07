#include "hud.hpp"
#include "entity/entity.hpp"

hud::hud(){

  punteroFuncionesActualizar [ActualizarArmaNeutral] =&hud::actualizarArmaNeutral;
  punteroFuncionesActualizar [ActualizarArmaAgua] =&hud::actualizarArmaAgua;
  punteroFuncionesActualizar [ActualizarArmaAire] =&hud::actualizarArmaAire;
  punteroFuncionesActualizar [ActualizarArmaFuego] =&hud::actualizarArmaFuego;
  punteroFuncionesActualizar [ActualizarArmaTierra] =&hud::actualizarArmaTierra;
  punteroFuncionesActualizar [ActualizarArmaPowerVida] =&hud::actualizarPowerVida;



    
}




void hud::actualizarArmaNeutral(arma &pla){
    //NEUTRAL
    

    if(pla.getMunicion().at(ArmaNeutral)>0){
        if(pla.gettipo()==ArmaNeutral){

             if(armaNeutralb){
                fachada->hudArmaNeutralb(eliminar);
                armaNeutralb=false;
            }
            if(!armaNeutral){
                fachada->hudArmaNeutral(colocar);
                armaNeutral=true;
                armaActiva=0;
                actualizarCargador(pla.getMunicion().at(ArmaNeutral));
            }
           
        }else{
             if(armaNeutral){
                fachada->hudArmaNeutral(eliminar);
                armaNeutral=false; 
                actualizado=true; 
            }   
            if(!armaNeutralb){
                fachada->hudArmaNeutralb(colocar);
                armaNeutralb=true;
            }
                        
        }
    }else if((armaNeutral || armaNeutral) && pla.getMunicion().at(ArmaNeutral)==0 ){
        if(armaNeutral)
            fachada->hudArmaNeutral(eliminar);
        if(armaNeutralb)
            fachada->hudArmaNeutralb(eliminar);

        armaNeutral=false;
        armaNeutralb=false;
    }
    actualizarArmaAnterior(pla);
}
void hud::actualizarArmaAgua(arma &pla){
    //AGUA
   if(pla.getMunicion().at(ArmaAgua)>0){
        if(pla.gettipo()==ArmaAgua){

            if(armaAguab){
                fachada->hudArmaAguab(eliminar);
                armaAguab=false;
            }

            if(!armaAgua){
                fachada->hudArmaAgua(colocar);
                armaAgua=true;
                armaActiva=1;
                actualizarCargador(pla.getMunicion().at(ArmaAgua));
            }
            
        }else{

            if(armaAgua){
                fachada->hudArmaAgua(eliminar);
                armaAgua=false;
                actualizado=true; 
            }   
            if(!armaAguab){
                fachada->hudArmaAguab(colocar);
                armaAguab=true;
            }
                       
        }
    }else if((armaAgua || armaAguab) && pla.getMunicion().at(ArmaAgua)==0 ){
        if(armaAgua)
            fachada->hudArmaAgua(eliminar);
        if(armaAguab)
            fachada->hudArmaAguab(eliminar);

        armaAgua=false;
        armaAguab=false;
    }
    if(!armaAgua && !armaAguab)
    actualizado=true;

    actualizarArmaAnterior(pla);

}
void hud::actualizarArmaAire(arma &pla){
//AIRE
   if(pla.getMunicion().at(ArmaAire)>0){
        if(pla.gettipo()==ArmaAire){

            if(armaAireb){
                fachada->hudArmaAireb(eliminar);
                armaAireb=false;
               
            }

            if(!armaAire){
                fachada->hudArmaAire(colocar);
                armaAire=true;
                armaActiva=2;
                actualizarCargador(pla.getMunicion().at(ArmaAire));
            }
            
        }else{

            if(armaAire){
                fachada->hudArmaAire(eliminar);
                armaAire=false;
                actualizado=true; 
            }   
            if(!armaAireb){
                fachada->hudArmaAireb(colocar);
                armaAireb=true;
            }
                       
        }
    }else if((armaAire || armaAireb) && pla.getMunicion().at(ArmaAire)==0 ){
        if(armaAire)
            fachada->hudArmaAire(eliminar);
        if(armaAireb)
            fachada->hudArmaAireb(eliminar);

        armaAire=false;
        armaAireb=false;
    }
    if(!armaAire && !armaAireb)
        actualizado=true;
    actualizarArmaAnterior(pla);

}
void hud::actualizarArmaFuego(arma &pla){
//FUEGO
  if(pla.getMunicion().at(ArmaFuego)>0){
        if(pla.gettipo()==ArmaFuego){

            if(armaFuegob){
                fachada->hudArmaFuegob(eliminar);
                armaFuegob=false;
            }

            if(!armaFuego){
                fachada->hudArmaFuego(colocar);
                armaFuego=true;
                armaActiva=3;
                actualizarCargador(pla.getMunicion().at(ArmaFuego));
            }
            
        }else{

            if(armaFuego){
                fachada->hudArmaFuego(eliminar);
                armaFuego=false; 
                actualizado=true; 
            }   
            if(!armaFuegob){
                fachada->hudArmaFuegob(colocar);
                armaFuegob=true;
            }
                       
        }
    }else if((armaFuego || armaFuegob) && pla.getMunicion().at(ArmaFuego)==0 ){  
        if(armaFuego)
            fachada->hudArmaFuego(eliminar);
        if(armaFuegob)
            fachada->hudArmaFuegob(eliminar);

        armaFuego=false;
        armaFuegob=false;
    }
    if(!armaFuego && !armaFuegob)
        actualizado=true;
    actualizarArmaAnterior(pla);

}
void hud::actualizarArmaTierra(arma &pla){
    //TIERRA
 if(pla.getMunicion().at(ArmaTierra)>0){
        if(pla.gettipo()==ArmaTierra){

            if(armaTierrab){
                fachada->hudArmaTierrab(eliminar);
                armaTierrab=false;
            }

            if(!armaTierra){
                fachada->hudArmaTierra(colocar);
                armaTierra=true;
                armaActiva=4;
                actualizarCargador(pla.getMunicion().at(ArmaTierra));
            }
            
        }else{

            if(armaTierra){
                fachada->hudArmaTierra(eliminar);
                armaTierra=false;  
                actualizado=true; 
            }   
            if(!armaTierrab){
                fachada->hudArmaTierrab(colocar);
                armaTierrab=true;
            }
                       
        }
    }else if((armaTierra || armaTierrab) && pla.getMunicion().at(ArmaTierra)==0 ){
        if(armaTierra)
            fachada->hudArmaTierra(eliminar);
        if(armaTierrab)
            fachada->hudArmaTierrab(eliminar);

        armaTierra=false;
        armaTierrab=false;
    }
     if(!armaTierra && !armaTierrab)
        actualizado=true;
    actualizarArmaAnterior(pla);

}
void hud::actualizarPowerVida(arma &pla){
//powerVida
    if(pla.getMunicion().at(PowerCura)>0){
        if(pla.gettipo()==PowerCura){

            if(powerVidab){
                fachada->hudPowerVidab(eliminar);
                powerVidab=false;
            }

            if(!powerVida){
                fachada->hudPowerVida(colocar);
                powerVida=true;
                armaActiva=5;
                actualizarCargador(pla.getMunicion().at(PowerCura));
            }
            
        }else{

            if(powerVida){
                fachada->hudPowerVida(eliminar);
                powerVida=false; 
                actualizado=true; 
            }   
            if(!powerVidab){
                fachada->hudPowerVidab(colocar);
                powerVidab=true;
            }
                       
        }
    }else if((powerVida || powerVidab) && pla.getMunicion().at(PowerCura)==0 ){
        if(powerVida)
            fachada->hudPowerVida(eliminar);
        if(powerVidab)
            fachada->hudPowerVidab(eliminar);

        powerVida=false;
        powerVidab=false;
    }
     if(!powerVida && !powerVidab)
        actualizado=true;        
    actualizarArmaAnterior(pla);

}
void hud::actualizarArmaAnterior(arma &pla){

    if (armaActiva!=armaAnterior){
    if(!actualizado)
    (this->*punteroFuncionesActualizar[armaAnterior])(pla);
    armaAnterior=armaActiva;
    
    }
    actualizado=false;
}
void hud::actualizarTier(vector <int> tier){
    int tie=0;
    int posicionx=444;
   
    for(int i=1;i<tier.size();i++){
        tie=tier.at(i);
        switch (tie)
        {
        case 0:
                    
                    switch (i)
                    {
                    case 1:
                        if(tier1){
                            fachada->elimiraTier(1);
                            tier1=false;
                        }
                        break;
                    case 2:
                        if(tier2){
                            fachada->elimiraTier(2);
                            tier2=false;
                        }    
                        break;
                    case 3:
                        if(tier3){
                            fachada->elimiraTier(3);
                            tier3=false;
                        }
                        break;
                    case 4:
                        if(tier4){
                            fachada->elimiraTier(4);
                            tier4=false;
                        }
                        break;            
                    default:
                        break;
                    
                    }
                    break;
        case 1:

            
                                switch (i)
                                {
                                case 1:
                                
                                    tier1=true;
                                    fachada->hudTier1(posicionx,i);
                                
                                    break;
                                case 2:
                                    
                                    tier2=true;
                                    fachada->hudTier1(posicionx,i);
                                
                                    break;
                                case 3:
                                    
                                    tier3=true;
                                    fachada->hudTier1(posicionx,i);
                                
                                    break;
                                case 4:
                                    
                                    tier4=true;
                                    fachada->hudTier1(posicionx,i);
                                
                                    break;            
                                default:
                                    break;
                                }        
            break;
        case 2:
                                 switch (i)
                                {
                                case 1:
                               
                                    
                                    fachada->hudTier2(posicionx,i);
                                
                                    break;
                                case 2:
                                    
                                    
                                    fachada->hudTier2(posicionx,i);
                                
                                    break;
                                case 3:
                                    
                                  
                                    fachada->hudTier2(posicionx,i);
                                
                                    break;
                                case 4:
                                   
                                   
                                    fachada->hudTier2(posicionx,i);
                                
                                    break;            
                                default:
                                    break;
                                }        
        break;
        case 3:
                                  switch (i)
                                {
                                case 1:
                                
                                    tier1=true;
                                    fachada->hudTier3(posicionx,i);
                                
                                    break;
                                case 2:
                                   
                                    tier2=true;
                                    fachada->hudTier3(posicionx,i);
                                
                                    break;
                                case 3:
                                   
                                    tier3=true;
                                    fachada->hudTier3(posicionx,i);
                                
                                    break;
                                case 4:
                                  
                                    tier4=true;
                                    fachada->hudTier3(posicionx,i);
                                
                                    break;            
                                default:
                                    break;
                                }         
        break;
            
        default:
            break;
        }
        posicionx+=100;
    }
    
}
void hud::actualizarTier1(int pos ,int num){
    fachada->hudTier1(pos,num);
}
void hud::actualizarTier2(int pos, int num){
    fachada->hudTier2(pos,num);    
}
void hud::actualizarTier3(int pos,int num){
    fachada->hudTier3(pos,num);    
}


void hud::activarMensaje(){
    if(!mensaje){
        mensaje=true;
        fachada->activarMensaje();
    }
}
void hud::desactivarMensaje(){
    if(mensaje){
        mensaje=false;
        fachada->desactivarMensaje();
    }



}
void hud::actualizarCargador(int num){
    fachada->numeroBalas(num);
}
void hud::actualizarVida(int num){
    fachada->numeroVida(num);
}
