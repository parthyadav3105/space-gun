#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED


#include<al.h>
#include<alc.h>
#include<iostream>
#include<fstream.h>

using namespace std;






class WAV_FILE
{public:
    int channels;
    int sample_rate;
    int bps;
    int size;
    char* data;

    void load_wav(const char* fn);
    WAV_FILE()     {data=NULL; size=0;bps=0;sample_rate=0;channels=0;}
    ~WAV_FILE()    {if(data!=NULL)     delete[] data;}
};







class AUDIO
     {         static ALCdevice* device;
                static ALCcontext* context;
                unsigned int bufferid;
                unsigned int sourceid;

    public:
               static void Init();
               static void terminate();
               AUDIO();
               ~AUDIO();
               void load(const char* file_name);
               void play( )                                         {alSourcePlay(sourceid);}
               void pause()                                      {alSourcePause(sourceid); }
               void volume(float v)                     {alSourcef(sourceid,AL_GAIN,v/100.0);}
               void loop(bool l)                               {alSourcei(sourceid,AL_LOOPING,l);}
      };





#endif // AUDIO_H_INCLUDED
