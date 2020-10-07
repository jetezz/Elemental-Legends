#include "motor_fisicas/myMotorF.hpp"
#include "entity/entity.hpp"
#include "entity/gameObject.hpp"
#include "motor_grafico/mynode.hpp"
#include "CONSTANTES.hpp"
#include <iostream>



vector3d myMotorF::move(vector3d &position, vector3d &velocidad){
   

    return vector3d(position.X+velocidad.X,position.Y+velocidad.Y,position.Z+velocidad.Z);
}




bool myMotorF::colision(vector3d &posicion1,std::vector<vector3d> &puntos1,vector3d &posicion2,std::vector<vector3d> &puntos2){
    
    bool compruebaX=false;//se inicializa a falso para que se compruebe con cada entidad
    bool compruebaY=false;
    bool compruebaZ=false;            
           
    float distanciaAX=0;
    float distanciaBX=0;
    float disCentrosX=0;

    float distanciaAY=0;
    float distanciaBY=0;
    float disCentrosY=0;

    float distanciaAZ=0;
    float distanciaBZ=0;
    float disCentrosZ=0;

    vector3d centroA=posicion1;
    vector3d centroB=posicion2;

                //Calculo con proyeccion en X

                //Conseguimos el punto minimo y maximo de todos los puntos en el eje x de ambos objetos y luego sacamos la distancia entra ambos 
                //despues solo tenemos que compara si la distancia entre centros es mayor o menor que la suma de las deistancias entre esos puntos para saber si 
                //los objetos estan colisionando o no .

                // la proyeccion de puntos y la comprobacion de distancias de hace igual para cada eje .
                
    distanciaAX = gistancia(puntos1,ejex);//Get distance nos devuelve la distancia entre ambos puntos / 2 
 
    distanciaBX = gistancia(puntos2,ejex);
                
    disCentrosX= abs(centroA.X-centroB.X);//nos da la diferencia de los puntos centrales proyectados en x 

    if(disCentrosX<(distanciaAX+distanciaBX)){ //comprueba si hay posible colision
            
        compruebaX=true;// si es asi pone a true las cosas
    }
                
                //Calculo con proyeccion en y ( igual que x)

    distanciaAY = gistancia(puntos1,ejey);
    distanciaBY = gistancia(puntos2,ejey);
                
    disCentrosY= abs(centroA.Y-centroB.Y);

    if(disCentrosY<(distanciaAY+distanciaBY)){
                
        compruebaY=true;
    }
                
                //Calculo con proyeccion en z (igual que x)

    distanciaAZ = gistancia(puntos1,ejez);
    distanciaBZ = gistancia(puntos2,ejez);
                
    disCentrosZ= abs(centroA.Z-centroB.Z);

    if(disCentrosZ<(distanciaAZ+distanciaBZ)){
            
        compruebaZ=true;
    }
                

                //Comprobamos si existe la colision en las 3 proyecciones , en caso de que asi sea mete la entiodad en ObjColision=i para devolverlo
    if(compruebaX==true && compruebaY==true && compruebaZ==true){//colisiona
        return true;
    
    }
                 
        
    return false;
    
}

float myMotorF::gistancia(std::vector<vector3d> &puntos1,int eje){
    float distancia=0;
    float max=0;
    float min=0;
    switch (eje)
    {
    case ejex:
        min=puntos1.at(0).X;
        max=puntos1.at(4).X;
        distancia=(max/2)-(min/2);
        break;
    case ejey:
        min=puntos1.at(0).Y;
        max=puntos1.at(1).Y;
        distancia=(max/2)-(min/2);
        
        break;
    case ejez:
        min=puntos1.at(0).Z;
        max=puntos1.at(2).Z;
        distancia=(max/2)-(min/2);
        break;
    default:
        break;
    }
    
    return distancia;
}



  



 vector<vector3d> myMotorF::getPuntos(vector3d &posicion, vector3d &hitboxinit, vector3d &rotacion){
     std::vector<vector3d> puntos;
     puntos.resize(8);

    vector3d hitbox=calcularHitBox(posicion,hitboxinit,rotacion);

    puntos[0]=vector3d(posicion.X-(hitbox.X/2),posicion.Y-(hitbox.Y/2),posicion.Z-(hitbox.Z/2));
    puntos[1]=vector3d(posicion.X-(hitbox.X/2),posicion.Y+(hitbox.Y/2),posicion.Z-(hitbox.Z/2));
    puntos[2]=vector3d(posicion.X-(hitbox.X/2),posicion.Y-(hitbox.Y/2),posicion.Z+(hitbox.Z/2));
    puntos[3]=vector3d(posicion.X-(hitbox.X/2),posicion.Y+(hitbox.Y/2),posicion.Z+(hitbox.Z/2));
    puntos[4]=vector3d(posicion.X+(hitbox.X/2),posicion.Y-(hitbox.Y/2),posicion.Z-(hitbox.Z/2));
    puntos[5]=vector3d(posicion.X+(hitbox.X/2),posicion.Y+(hitbox.Y/2),posicion.Z-(hitbox.Z/2));
    puntos[6]=vector3d(posicion.X+(hitbox.X/2),posicion.Y-(hitbox.Y/2),posicion.Z+(hitbox.Z/2));
    puntos[7]=vector3d(posicion.X+(hitbox.X/2),posicion.Y+(hitbox.Y/2),posicion.Z+(hitbox.Z/2));

    return puntos;

 }
 vector3d myMotorF::calcularHitBox(vector3d &posicion, vector3d &hitbox, vector3d &rotacion){

    std::vector<vector3d> puntosHitBox2d;
    puntosHitBox2d.resize(4);

    puntosHitBox2d[0]=vector3d(hitbox.X/2,0,hitbox.Z/2);
    puntosHitBox2d[1]=vector3d(hitbox.X/2,0,-hitbox.Z/2);




    float hipo=std::sqrt(pow(puntosHitBox2d[0].X,2)+pow(puntosHitBox2d[0].Z,2));

    float x=0;
    float z=0;

    float x2=0;
    float z2=0;
   

    
    float anguloInicial= atan((puntosHitBox2d[0].X)/(puntosHitBox2d[0].Z));
    //float anguloInicialDeg=(anguloInicial*180)/3.1418;
    float rotacionR=(rotacion.Y*3.1418)/180;
    float anguloR=anguloInicial-rotacionR;
    //float angulo=(anguloR*180)/3.1418;
    


    x=hipo*sin(anguloR);       
    z=hipo*cos(anguloR);


    float anguloInicial2= atan((puntosHitBox2d[1].X)/(puntosHitBox2d[1].Z));
    //float anguloInicialDeg2=(anguloInicial2*180)/3.1418;
    
    float anguloR2=anguloInicial2-rotacionR;
    //float angulo2=(anguloR2*180)/3.1418;

    x2=hipo*sin(anguloR2);       
    z2=hipo*cos(anguloR2);

    puntosHitBox2d[0]=vector3d(x,0,z);
    puntosHitBox2d[1]=vector3d(x2,0,z2);
    puntosHitBox2d[2]=vector3d(-x,0,-z);
    puntosHitBox2d[3]=vector3d(-x2,0,-z2);


    float maximoX=0;
    float minimoX=0;   
    float maximoZ=0;
    float minimoZ=0;
    
    for(int i=0; i<4;i++){
        if(puntosHitBox2d[i].X>maximoX){
            maximoX=puntosHitBox2d[i].X;
        }else if(puntosHitBox2d[i].X<minimoX){
            minimoX=puntosHitBox2d[i].X;
        }
        if(puntosHitBox2d[i].Z>maximoZ){
            maximoZ=puntosHitBox2d[i].Z;
        }
        else if(puntosHitBox2d[i].Z<minimoZ){
            minimoZ =puntosHitBox2d[i].Z;
        }
    }
    return vector3d((minimoX*-1)+maximoX,hitbox.Y,(minimoZ*-1)+maximoZ);

 }

 std::vector<vector2d> myMotorF::getRegion(std::vector<vector3d> &puntos){
    int posicionX {0};
    int posicionZ {0};
    int regionX {0};
    int regionZ {0};
    std::vector<vector2d> regiones;
    vector2d region{};
     
     regiones.reserve(4);

     
     for(auto &punto : puntos){
        posicionX=punto.X;
        posicionZ=punto.Z;
        regionX=posicionX/TamanoRegion;
        regionZ=posicionZ/TamanoRegion;
        region=vector2d(regionX,regionZ);


        if(!existeRegion(regiones,region)){
            regiones.push_back(vector2d(regionX,regionZ));
            
        }
    
     }

    return regiones;
    
     
    
 }


bool myMotorF::existeRegion(std::vector<vector2d> &regiones, vector2d &region){

    for(auto &regionAux : regiones){
             if(regionAux.X==region.X && regionAux.Z == region.Z){
                 return true;
             }
    
    }
return false;
}
bool myMotorF::coincidenRegiones(std::vector<vector2d> &regiones1,std::vector<vector2d> &regiones2){

    for(auto &reg1 : regiones1){
        for(auto &reg2 : regiones2){
            if(reg1.X==reg2.X && reg1.Z==reg2.Z){
                return true;
            }
        }
    }
    
 return false;

}


