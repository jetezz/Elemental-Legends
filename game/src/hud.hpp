#pragma once



#include <iostream>
#include "motor_grafico/fachadaIrrlicht.hpp"

class arma;

class hud{

public:
//FUNCIONES
hud();


void actualizarArmaNeutral(arma &pla);
void actualizarArmaAgua(arma &pla);
void actualizarArmaAire(arma &pla);
void actualizarArmaFuego(arma &pla);
void actualizarArmaTierra(arma &pla);
void actualizarPowerVida(arma &pla);
void actualizarArmaAnterior(arma &pla);
void actualizarTier(vector <int> tier);
void actualizarTier1(int pos,int num);
void actualizarTier2(int pos,int num);
void actualizarTier3(int pos,int num);
void activarMensaje();
void desactivarMensaje();
void actualizarCargador(int num);
void actualizarVida(int num);


//VARIABLES


//CONSTANTES
    
private:
int armaActiva      {0};
int armaAnterior    {0};
bool actualizado    {false};

bool armaNeutral {true};
bool armaNeutralb {false};

bool armaAgua {false};
bool armaAguab {false};

bool armaAire {false};
bool armaAireb {false};

bool armaFuego {false};
bool armaFuegob {false};

bool armaTierra {false};
bool armaTierrab {false};

bool powerVida{false};
bool powerVidab{false};


bool mensaje {false};
bool tier1 {false};
bool tier2 {false};
bool tier3 {false};
bool tier4 {false};

fachadaIrrlicht *fachada = fachadaIrrlicht::getFachada();
void (hud::*punteroFuncionesActualizar[6])(arma &pla);    
};



