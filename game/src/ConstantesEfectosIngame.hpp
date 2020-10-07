#pragma once

 //consecuencias disparo y hud
   static const int TotalConsecuencias         {12};
   static const int SinConsecuencia            {-1};
   static const int ActualizarArmaNeutral      {0};
   static const int ActualizarArmaAgua         {1};
   static const int ActualizarArmaAire         {2};
   static const int ActualizarArmaFuego        {3};
   static const int ActualizarArmaTierra       {4};
   static const int ActualizarArmaPowerVida    {5};

  
   static const int PonerMensajeHud            {6};
   static const int QuitarMensajeHud           {7};
   static const int ReajustarCargador          {8};
   static const int Curar                      {9};
   static const int ReajustarVida              {10};
   static const int ReajustarTier              {11};

//tipos de powerup o armas
   static const int NoEsUnPowerUp              {-1};
   static const int ArmaNeutral                {0};
   static const int ArmaAgua                   {1};
   static const int ArmaAire                   {2};
   static const int ArmaFuego                  {3};
   static const int ArmaTierra                 {4};
   static const int PowerCura                  {5};

//eliminar objetos o ponerlos en el hub
   static const int colocar                    {1};
   static const int eliminar                   {2};

