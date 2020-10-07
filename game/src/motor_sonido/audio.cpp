#include "audio.hpp"
#include <memory>

//CAMBIAR LOS NEW Y DEMAS COSAS QUE NO PUEDEN HABER

//con esto se inicializa el sistema fmod y se crea
Implementation::Implementation(){
    mpStudioSystem = NULL;
    CAudioEngine::ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem) );
    CAudioEngine::ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));

    mpSystem = NULL;
    CAudioEngine::ErrorCheck(mpStudioSystem->getCoreSystem(&mpSystem));
   
}

//destructor para limpiar fmod y asegurarnos de que no dejamos nada
Implementation::~Implementation(){
    CAudioEngine::ErrorCheck(mpStudioSystem->unloadAll());
    CAudioEngine::ErrorCheck(mpStudioSystem->release());
}

//vemos si el canal ha parado de reproducir, si ha parado lo destruimos
// y limpiamos el canal.
void Implementation::Update(){
    vector<ChannelMap::iterator> pStoppedChannels;
    for(auto it=mChannels.begin(), itEnd = mChannels.end(); it !=itEnd; ++it){
        bool bIsPlaying = false;
        it->second->isPlaying(&bIsPlaying);
        if(!bIsPlaying){
            pStoppedChannels.push_back(it);
        }
    }
    for(auto& it : pStoppedChannels){
        mChannels.erase(it);
    }
    CAudioEngine::ErrorCheck(mpStudioSystem->update());
}

std::unique_ptr<Implementation> sgpImplementation = nullptr;

//implementacion, llamadas a update
void CAudioEngine::Init(){
    sgpImplementation = std::make_unique<Implementation>();
}

void CAudioEngine::Update(){
    sgpImplementation->Update();
}

//se define el sonido, si es 3d, los loop y demás
//despues se carga el sonido y se guarda en el sound map
void CAudioEngine::Loadsound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream){
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName); //busca el sonido
    if(tFoundIt != sgpImplementation->mSounds.end()) //si no lo encuentra sale
        return;
    
    FMOD_MODE eMode = FMOD_DEFAULT;
    eMode |= b3d ? FMOD_3D : FMOD_2D;
    eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

    FMOD::Sound* pSound = nullptr;
    CAudioEngine::ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
    if(pSound)
        sgpImplementation->mSounds[strSoundName] = pSound;
}

//unload sounds
void CAudioEngine::UnLoadsound(const std::string& strSoundName){
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);//busca el sonido
    if(tFoundIt == sgpImplementation->mSounds.end())//si no lo encuentra es que no esta y sale
        return;

    CAudioEngine::ErrorCheck(tFoundIt->second->release());//para ver si da error o no
    sgpImplementation->mSounds.erase(tFoundIt);//elimina el sonido 
}

//primero se comprueba si el sonido está en el sound map
//si no está ha habido un error y no podemos activar el sonido
//si encontramos el sonido, creamos un nuevo canal y activamos el sonido, pero empieza pausado
//si todo es correcto actualizamos todos los posibles parametros como
//volumen, posicion y unpause del sonido
//finalmente devolvemos el id del canal para referenciarlo despues
int CAudioEngine::PlaySound(const string& strSoundName, const Vector3& vPosition, float fVolumedB){
    int nChannelID = sgpImplementation->mnNextChannelId++;//tenemos el id del canal
    auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);//buscamos el sonido
    if(tFoundIt == sgpImplementation->mSounds.end()){///////////////DUDO DE QUE ESTO ESTE BIEN
        Loadsound(strSoundName); //se carga el sonido //CREO QUE AQUI DEBERIA IR EL RETURN Y FUERA EL LOADSOUND
        tFoundIt = sgpImplementation->mSounds.find(strSoundName);
        if(tFoundIt == sgpImplementation->mSounds.end())//si no se encuentra
            return nChannelID;//devuelve el canal

    }

    FMOD::Channel* pChannel = nullptr;
    CAudioEngine::ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
    if(pChannel){
        FMOD_MODE currMode;
        tFoundIt->second->getMode(&currMode);//se cqarga el modo
        if(currMode & FMOD_3D){
            FMOD_VECTOR position = VectorToFmod(vPosition);//se convierte a vector fmod y se obtiene la posicion
            CAudioEngine::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));//se comprueba que no da error
        }
        CAudioEngine::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));//se cambia de dB a volumen y se asigna comprobando si da error
        CAudioEngine::ErrorCheck(pChannel->setPaused(false));//se activa el sonido comprobando si da error
        sgpImplementation->mChannels[nChannelID]= pChannel;
    }
    return nChannelID;
}

//poner la posicion del sonido, se indica de que canal y la posicion que tiene que poner
void CAudioEngine::SetChannel3Position(int nChannelId, const Vector3& vPosition){
    auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);//busca el canal
    if(tFoundIt == sgpImplementation->mChannels.end())
        return;

    FMOD_VECTOR position = VectorToFmod(vPosition);//pone la posicion
    CAudioEngine::ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

//poner volumen al canal
void CAudioEngine::SetChannelvolume(int nChannelId, float fVolumedB){
    auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
    if(tFoundIt == sgpImplementation->mChannels.end())
        return;

    CAudioEngine::ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
}

//cargar bancos 
void CAudioEngine::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags){
     auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
    if (tFoundIt != sgpImplementation->mBanks.end())
        return;
    FMOD::Studio::Bank* pBank;
    CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
    if (pBank) {
        sgpImplementation->mBanks[strBankName] = pBank;
    }
}


//PRUEBA
/*void CAudioEngine::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags){
   auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
    if(tFoundIt != sgpImplementation->mBanks.end())//!=
        return;

    FMOD::Studio::Bank* masterBank = NULL;
    CAudioEngine::ErrorCheck( sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank) );

}*/

//cargar strings de bancos
void CAudioEngine::LoadBankStrings(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags){
     auto tFoundIt = sgpImplementation->mBanks.find(strBankName);
    if (tFoundIt != sgpImplementation->mBanks.end())
        return;
    FMOD::Studio::Bank* pBank;
    CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));
    if (pBank) {
        sgpImplementation->mBanks[strBankName] = pBank;
    }
}

//cargar eventos: eventdescription->informacion del evento, eveninstance->activar el evento
void CAudioEngine::LoadEvent(const std::string& strEventName){
    auto tFoundit = sgpImplementation->mEvents.find(strEventName);
    if (tFoundit != sgpImplementation->mEvents.end())
        return;
    FMOD::Studio::EventDescription* pEventDescription = NULL;
    CAudioEngine::ErrorCheck(sgpImplementation->mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
    if (pEventDescription){
        FMOD::Studio::EventInstance* pEventInstance = NULL;
        CAudioEngine::ErrorCheck(pEventDescription->createInstance(&pEventInstance));
        if (pEventInstance){
            sgpImplementation->mEvents[strEventName] = pEventInstance;
        }
    }
    
}

//activamos el evento/play the event
void CAudioEngine::PlayEvent(const string &strEventName){
     auto tFoundit = sgpImplementation->mEvents.find(strEventName);
    if (tFoundit == sgpImplementation->mEvents.end()){
        LoadEvent(strEventName);
        tFoundit = sgpImplementation->mEvents.find(strEventName);
        if (tFoundit == sgpImplementation->mEvents.end())
            return;
    }
    tFoundit->second->start();
}

//parar evento
void CAudioEngine::StopEvent(const string &strEventName, bool bImmediate){
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

    FMOD_STUDIO_STOP_MODE eMode;
    eMode = bImmediate ? FMOD_STUDIO_STOP_IMMEDIATE : FMOD_STUDIO_STOP_ALLOWFADEOUT;
    CAudioEngine::ErrorCheck(tFoundIt->second->stop(eMode));
}

//saber si un evento se está ejecutando o no
bool CAudioEngine::IsEventPlaying(const string &strEventName) const {
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if (tFoundIt == sgpImplementation->mEvents.end())
        return false;

    FMOD_STUDIO_PLAYBACK_STATE* state = NULL;
    if (tFoundIt->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING) {
        return true;
    }
    return false;
}

//get parameters
void CAudioEngine::GeteventParameter(const string &strEventName, const char *strParameterName, float * parameter){
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

    
    //auto *pParameter = nullptr;
   // FMOD::Studio::System* pParameter;
    //pParameter->getParameterByName(strParameterName, parameter);
    //FMOD::Studio::ParameterInstance* pParameter = NULL;
    CAudioEngine::ErrorCheck(tFoundIt->second->getParameterByName(strParameterName, parameter));
    //CAudioEngine::ErrorCheck(pParameter->getValue(parameter));
}

//set parameters
void CAudioEngine::SetEventParameter(const string &strEventName, const char *strParameterName, float fValue){
    auto tFoundIt = sgpImplementation->mEvents.find(strEventName);
    if(tFoundIt == sgpImplementation->mEvents.end())
        return;

   // FMOD::Studio::ParameterInstance * pParameter = NULL;
    //CAudioEngine::ErrorCheck(tFoundIt->second->getParameter(strParameterName.c_str(), &pParameter));
    //CAudioEngine::ErrorCheck(pParameter->setValue(fValue));
     CAudioEngine::ErrorCheck(tFoundIt->second->setParameterByName(strParameterName, fValue));
}

//convertir nuestro vector en vector de fmod
FMOD_VECTOR CAudioEngine::VectorToFmod(const Vector3& vPosition){
    FMOD_VECTOR fVec;
    fVec.x = vPosition.x;
    fVec.y = vPosition.y;
    fVec.z = vPosition.z;
    return fVec;
}

//cambier de db al volumen
float CAudioEngine::dbToVolume(float db){
    return powf(10.0f, 0.05f * db);
}

//cambiar de volumen a db
float CAudioEngine::VolumeTodb(float volume){
    return 20.0f * log10f(volume);
}

//para saber si hay errores, no cargan bien los sonidos, etc
int CAudioEngine::ErrorCheck(FMOD_RESULT result){
    if(result != FMOD_OK){
        cout << "FMOD ERROR (" << result <<")" << endl;
        return 1;
    }
    //cout << "FMOD all good" << endl;
    return 0;
}

//para limpiar todo y eliminar la implementacion
void CAudioEngine::Shutdown(){
    sgpImplementation = nullptr;
}


void CAudioEngine::AudioUpdate(CAudioEngine* engine) {
	while (1){
		engine->Update();
	}
}

void CAudioEngine::pruebacargarsonido(){

}