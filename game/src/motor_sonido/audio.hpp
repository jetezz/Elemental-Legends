#pragma once

#include <fmod_studio.hpp>
//#include "../lib/fmodstudio/api/studio/inc/fmod_studio.hpp"
#include <fmod.hpp>
//#include "../lib/fmodstudio/api/core/inc/fmod.hpp"
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

//posible cambiar por vector3d
//sirve para saber donde se situa el sonido
struct Vector3{
    float x;
    float y;
    float z;
};



//contiene  la mayoria de llamadas a fmod api
struct Implementation {


    Implementation();//con esto se inicializa el sistema fmod y se crea
    ~Implementation();//destructor para limpiar fmod y asegurarnos de que no dejamos nada

    void Update();//vemos si el canal ha parado de reproducir, si ha parado lo destruimos y limpiamos el canal.
    FMOD::Studio::System* mpStudioSystem;
    FMOD::System* mpSystem;

    int mnNextChannelId;

    typedef map<string, FMOD::Sound*> SoundMap;
    typedef map<int, FMOD::Channel*> ChannelMap;
    typedef map<string, FMOD::Studio::EventInstance*> EventMap;
    typedef map<string, FMOD::Studio::Bank*> BankMap;

    BankMap mBanks;
    EventMap mEvents;
    SoundMap mSounds;
    ChannelMap mChannels;

};

class CAudioEngine{

    public:
        //funciones
        static void Init();
        static void Update();
        static void Shutdown();
        static int ErrorCheck(FMOD_RESULT result);//saber que se ha cargado bien, para controlar los errores
        
        void LoadBank(const string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
        void LoadBankStrings(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
        void LoadEvent(const string& strEventName);
        void Loadsound(const string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
        void UnLoadsound(const string& strSoundName);
        void Set3dListenerandOrientation(const Vector3& vPos = Vector3{0, 0, 0}, float fVolumedB = 0.0f);
        int  PlaySound(const string& strSoundName, const Vector3& vPos = Vector3{0, 0, 0}, float fVolumedB = 0.0f);
        void PlayEvent(const string& strEventName);
        void StopChannel(int nchannelId);
        void StopEvent(const string& strEventName, bool bImmediate = false);
        void GeteventParameter(const string& strEventName, const char* strEvedntParameter, float* parameter);
        void SetEventParameter(const string& strEventName, const char* strParameterName, float fValue);
        void StopallChannels();
        void SetChannel3Position(int nChannelId, const Vector3& vPosition);
        void SetChannelvolume(int nChannelId, float fVolumedB);
        void IsPlaying(int nChannelId) const;
        bool IsEventPlaying(const string& strEventName) const;
        float dbToVolume(float db);
        float VolumeTodb(float volume);
        FMOD_VECTOR VectorToFmod(const Vector3& vPosition);

        void AudioUpdate(CAudioEngine* engine) ;
        void pruebacargarsonido();
};


