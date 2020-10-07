#pragma once



#include <vector>
#include <memory>
#include "motor_grafico/vector3d.hpp"
#include "motor_grafico/mynode.hpp"
#include "entity/gameObject.hpp"


class bala;

class arma : public gameObject{
   public:

    //FUNCIONES
    arma();
    arma(int tipo, uint8_t nivel);
    int disparar(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador);
    bool efectoColision(entity &enti,std::vector<unique_ptr <gameObject>> &ArrayGameObject);
   


    void recargarArmaNeutral();
    void recargarArmaAgua();
    void recargarArmaAire();
    void recargarArmaFuego();
    void recargarArmaTierra();
    void recargarPowerVida();

    int actualizarArmaNeutral();
    int actualizarArmaAgua();
    int actualizarArmaAire();
    int actualizarArmaFuego();
    int actualizarArmaViento();
    int actualizarPowerVida();



    int dispararNeutral(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador, int tier, float& dayo);
    int dispararAgua(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot ,entity* disparador, int tier, float& dayo);
    int disparaAire(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot ,entity* disparador, int tier, float& dayo);
    int dispararFuego(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot ,entity* disparador, int tier, float& dayo);
    int dispararTierra(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot ,entity* disparador, int tier, float& dayo);
    int dispararPowerVida(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot ,entity* disparador, int tier, float& dayo);

   
    bool isPickeable() override; //Devuelve true o false si es un objeto recogible.





    //set
    void setTipo(uint8_t tip);
    void setMunicion(int tipo);
    void setTier( vector <int> tipo);
    void setEntidad(entity* entidad);
    

    //get
    vector <int> getMunicion();
    vector <int> getTier();
    entity* getEntidad();
    int gettipo();

    //variables
  
    

   

    //constantes
    static const int TotalPowerUp       {6};

    //consecuencias del disparo
    
   

    private:

    //FUNCIONES


    //VARIABLES
    
    
   
    int tipo;
    uint8_t nivel{0};    
    vector <int> municion;
    vector <int> tier;
    entity* ent {nullptr};
    void (arma::*punteroMunicion[TotalPowerUp])();                                                                             //delegado tengo las funciones de todos los recargar 
    int (arma::*punteroDisparo[TotalPowerUp])(std::vector<std::unique_ptr <bala>> &ArrayDeBalas, vector3d& pos,vector3d rot, entity* disparador, int tier, float& dayo); //delegado tengo las funciones de disparar de todos los elementos
    int (arma::*punteroActualizarHud[6])();   
   

    //CONSTANTES
    
   
    

};