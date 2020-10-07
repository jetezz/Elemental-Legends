
#include "changeWeapon.hpp"
#include "../blackboard.hpp"
/*
*Cambia el arma a la más atractiva disponible
*/
bool changeWeapon::run(blackboard *data){

    if(!&data->b_bot->getArma()){
        cout << "ERROR::NOARMA" << endl;
        return true;
    }
    auto ammo = data->b_bot->getArma().getMunicion();
    for(int i = ammo.size()-1; i>=0; i--){
        if(ammo.at(i)>0 && i!=PowerCura){ //Importante. El arma no puede ser la 5 ya que esta es la cura.
            data->b_bot->getArma().setTipo(i);
            return true;
        }
    }

    return true;
}
