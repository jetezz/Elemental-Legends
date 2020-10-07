 #include "arma.hpp"
 #include "entity/balas/bala.hpp"
 #include "entity/balas/bala_fuego.hpp"
 #include "entity/balas/bala_tierra.hpp"
 #include "entity/balas/bala_aire.hpp"
 #include "entity/balas/bala_agua.hpp"
 #include "entity/balas/bala_neutral.hpp"
 #include "motor_sonido/audio.hpp"
 #include "ConstantesEfectosIngame.hpp"



    const int64_t retardoArmaNeutral        {250};

    const int64_t retardoArmaAgua           {1500};
    const int64_t retardoArmaAgua2          {800};
    const int64_t retardoArmaAgua3          {400};


    const int64_t retardoArmaAire           {800};
    const int64_t retardoArmaAire2           {400};
    const int64_t retardoArmaAire3           {100};



    const int64_t retardoArmaFuego          {1000};
    const int64_t retardoArmaFuego2          {800};
    const int64_t retardoArmaFuego3          {500};

    const int64_t retardoArmaTierra         {3000};
    const int64_t retardoArmaTierra2         {2500};
    const int64_t retardoArmaTierra3         {2000};
    


    const int recargaNeutral                {50000};
    const int recargaAgua                   {50};
    const int recargaAire                   {10};
    const int recargaFuego                  {5};
    const int recargaTierra                 {1};
    const int recargaVida                   {1};






static CAudioEngine audio;



 arma::arma()
 :arma(0,1)
 {
     
     
     
 }
    
arma::arma(int tip, uint8_t niv){
    tipo=tip;
    nivel=niv;
    setTiempo(std::chrono::system_clock::now());






    punteroMunicion [ArmaNeutral] =&arma::recargarArmaNeutral;
    punteroMunicion [ArmaAgua] =&arma::recargarArmaAgua;
    punteroMunicion [ArmaAire] =&arma::recargarArmaAire;
    punteroMunicion [ArmaFuego] =&arma::recargarArmaFuego;
    punteroMunicion [ArmaTierra] =&arma::recargarArmaTierra;
    punteroMunicion [PowerCura] =&arma::recargarPowerVida;

    municion.resize(TotalPowerUp);
    municion[ArmaNeutral]=0;
    municion[ArmaAgua]=0;
    municion[ArmaAire]=0;
    municion[ArmaFuego]=0;
    municion[ArmaTierra]=0;
    municion[PowerCura]=0;

    tier.resize(TotalPowerUp);
    tier[ArmaNeutral]=0;
    tier[ArmaAgua]=0;
    tier[ArmaAire]=0;
    tier[ArmaFuego]=0;
    tier[ArmaTierra]=0;
    tier[PowerCura]=0;
    
    
    (this->*punteroMunicion[tip])();
    
    punteroDisparo [ArmaNeutral] =&arma::dispararNeutral;
    punteroDisparo [ArmaAgua] =&arma::dispararAgua;
    punteroDisparo [ArmaAire] =&arma::disparaAire;
    punteroDisparo [ArmaFuego] =&arma::dispararFuego;
    punteroDisparo [ArmaTierra] =&arma::dispararTierra;
    punteroDisparo [PowerCura] =&arma::dispararPowerVida;



    punteroActualizarHud[ActualizarArmaNeutral]=&arma::actualizarArmaNeutral;
    punteroActualizarHud[ActualizarArmaAgua]=&arma::actualizarArmaAgua;
    punteroActualizarHud[ActualizarArmaAire]=&arma::actualizarArmaAire;
    punteroActualizarHud[ActualizarArmaFuego]=&arma::actualizarArmaFuego;
    punteroActualizarHud[ActualizarArmaTierra]=&arma::actualizarArmaViento;
    punteroActualizarHud[ActualizarArmaPowerVida]=&arma::actualizarPowerVida;





}

int arma::disparar(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador){
    int consecuencia=SinConsecuencia;
if(municion[tipo]>0){
    
    consecuencia=(this->*punteroDisparo[tipo])(ArrayDeBalas,pos,rot,disparador,tier.at(tipo),disparador->getDayo());  //todos los disparos tienen una consecuencia esa la recojo y la devuelvo al entity 
    return consecuencia;
}else{
    
    tier.at(tipo)=0;  
    tipo=0;  
}
    consecuencia=(this->*punteroActualizarHud[tipo])();
    return consecuencia;

    
}


bool arma::efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject){

    return false;
}
//Devuelve true o false si es un objeto recogible.
bool arma::isPickeable(){
    return false;
}

int arma::dispararNeutral(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador,int tier, float& dayo){

   

        if(std::chrono::system_clock::now()-getTiempo() >std::chrono::milliseconds(retardoArmaNeutral)){
        ///////////////////////prueba sonido////////////////////////////////


            //audio.LoadEvent("event:/Efectos/Disparo Default");

            audio.PlayEvent("event:/Efectos/Disparo Default");

            audio.Update();


        //////////////////////////////////////////////////////////
        std::unique_ptr<bala_neutral> aux ;
        aux = std::make_unique<bala_neutral>(pos,rot,disparador, tier,dayo);      
        ArrayDeBalas.emplace_back(std::move(aux));
        setTiempo(std::chrono::system_clock::now());
        municion[ArmaNeutral]--;
        }
        return ReajustarCargador;
}
int arma::dispararAgua(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador,int tier,float& dayo){
    
int64_t tiempo=0;
switch (tier)
{
case 1:
    tiempo=retardoArmaAgua;
    break;
case 2:
    tiempo=retardoArmaAgua2;
    break;
case 3:
    tiempo=retardoArmaAgua3;
    break;
default:
    break;
}
 
    

  if(std::chrono::system_clock::now()-getTiempo() >std::chrono::milliseconds(tiempo)){

       ///////////////////////prueba sonido////////////////////////////////


            //audio.LoadEvent("event:/Efectos/Disparo Agua");

            audio.PlayEvent("event:/Efectos/Disparo Agua");

            audio.Update();


        //////////////////////////////////////////////////////////

       for(int i =0; i<10; i++){ 
        std::unique_ptr<bala_agua> aux ;
        aux = std::make_unique<bala_agua>(pos,rot,disparador,tier,dayo);    
        ArrayDeBalas.emplace_back(std::move(aux));       
    }
    setTiempo(std::chrono::system_clock::now());
    municion[ArmaAgua]-=10;

    

}
return ReajustarCargador;
}
int arma::disparaAire(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador,int tier,float& dayo){

int64_t tiempo=0;
switch (tier)
{
case 1:
    tiempo=retardoArmaAire;
    break;
case 2:
    tiempo=retardoArmaAire2;
    break;
case 3:
    tiempo=retardoArmaAire3;
    break;
default:
    break;
}
 if(std::chrono::system_clock::now()-getTiempo() >std::chrono::milliseconds(tiempo)){

      ///////////////////////prueba sonido////////////////////////////////


            //audio.LoadEvent("event:/Efectos/Disparo Aire");

            audio.PlayEvent("event:/Efectos/Disparo Aire");

            audio.Update();


        //////////////////////////////////////////////////////////
        
        std::unique_ptr<bala_aire> aux ;
        aux = std::make_unique<bala_aire>(pos,rot,disparador, tier, dayo);      
        ArrayDeBalas.emplace_back(std::move(aux));
        setTiempo(std::chrono::system_clock::now());
        municion[ArmaAire]--;
        
        
    }
     return ReajustarCargador;
}
int arma::dispararFuego(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador, int tier,float& dayo){
int64_t tiempo=0;
switch (tier)
{
case 1:
    tiempo=retardoArmaFuego;
    break;
case 2:
    tiempo=retardoArmaFuego2;
    break;
case 3:
    tiempo=retardoArmaFuego3;
    break;
default:
    break;
}
  if(std::chrono::system_clock::now()-getTiempo() >std::chrono::milliseconds(tiempo)){

       ///////////////////////prueba sonido////////////////////////////////


            //audio.LoadEvent("event:/Efectos/Disparo Fuego");

            audio.PlayEvent("event:/Efectos/Disparo Fuego");

            audio.Update();


        //////////////////////////////////////////////////////////
        
        std::unique_ptr<bala_fuego> aux ;
        aux = std::make_unique<bala_fuego>(pos,rot,disparador,tier,dayo);     
        ArrayDeBalas.emplace_back(std::move(aux));
        setTiempo(std::chrono::system_clock::now());
        municion[ArmaFuego]--;
       
        
    }
     return ReajustarCargador;
}
int arma::dispararTierra(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot,entity* disparador, int tier,float& dayo){
int64_t tiempo=0;
switch (tier)
{
case 1:
    tiempo=retardoArmaTierra;
    break;
case 2:
    tiempo=retardoArmaTierra2;
    break;
case 3:
    tiempo=retardoArmaTierra3;
    break;
default:
    break;
}

  if(std::chrono::system_clock::now()-getTiempo() >std::chrono::milliseconds(tiempo)){

       ///////////////////////prueba sonido////////////////////////////////


            //audio.LoadEvent("event:/Efectos/Disparo Tierra");

            audio.PlayEvent("event:/Efectos/Disparo Tierra");

            audio.Update();


        //////////////////////////////////////////////////////////
        
        std::unique_ptr<bala_tierra> aux ;
        aux = std::make_unique<bala_tierra>(pos,rot,disparador,tier,dayo);      
        ArrayDeBalas.emplace_back(std::move(aux));
        setTiempo(std::chrono::system_clock::now());
        municion[ArmaTierra]--;
        
       
        
    }
     return ReajustarCargador;
}
int arma::dispararPowerVida(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador,int tier, float&dayo){

        municion[PowerCura]--;
        return Curar;
}





////RECARGAR

void arma::recargarArmaNeutral(){
   municion.at(ArmaNeutral)=recargaNeutral;
   
}
void arma::recargarArmaAgua(){
    municion.at(ArmaAgua)+=recargaAgua;
    if(tier.at(ArmaAgua)<3)
    ++tier.at(ArmaAgua);
   
    

}
void arma::recargarArmaAire(){
    municion.at(ArmaAire)+=recargaAire;
     if(tier.at(ArmaAire)<3)
    ++tier.at(ArmaAire);
    

}
void arma::recargarArmaFuego(){
    municion.at(ArmaFuego)+=recargaFuego;
     if(tier.at(ArmaFuego)<3)
    ++tier.at(ArmaFuego);


}
void arma::recargarArmaTierra(){
    municion.at(ArmaTierra)+=recargaTierra;
     if(tier.at(ArmaTierra)<3)
    ++tier.at(ArmaTierra);


}
void arma::recargarPowerVida(){
    if(municion.at(PowerCura)==0)
    municion.at(PowerCura)=recargaVida;
    
}


int arma::actualizarArmaNeutral(){
return ActualizarArmaNeutral;
}
int arma::actualizarArmaAgua(){
return ActualizarArmaAgua;
}
int arma::actualizarArmaAire(){
return ActualizarArmaAire;
}
int arma::actualizarArmaFuego(){
return ActualizarArmaFuego;
}
int arma::actualizarArmaViento(){
return ActualizarArmaTierra;
}
int arma::actualizarPowerVida(){
return ActualizarArmaPowerVida;
}


//////////////
///SET////////
/////////////

void arma::setTipo(uint8_t tip){
     tipo=tip;
 }
void arma::setMunicion(int tipo){
    (this->*punteroMunicion[tipo])();
 }
 void arma::setTier(vector <int> tie){
     tier=tie;
 }
  void arma::setEntidad(entity* entidad){
      ent=entidad;
  }

/////////
 ///get/
 ////////

vector<int> arma::getMunicion(){
return municion;
 }
 int arma::gettipo(){
     return tipo;
 }
 vector<int> arma::getTier(){
     return tier;
 }
 entity* arma::getEntidad(){
     return ent;
 }