#pragma once

#include "../treeTask.hpp"

class blackboard;
struct enemyHeard : public treeTask {


public:
/*
    Comprueba si se ha escuchado algún ruido
    Importante. Esta decisión es un poco trampa porque nunca va a permitir continuar a la ia
    desde este punto. Ya que la comprobación anterior (ver alguien en el angulo de vision) llamará
    a esta tarea si falla. Esta tarea siempre fallará y llevará a generar waypoint
    El truco es que esta tarea pone como waypoint el sitio donde escuchó ruido, y el bot irá a ese sitio.
*/
   virtual bool run(blackboard *data) override;
};