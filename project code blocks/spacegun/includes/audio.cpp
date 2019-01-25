
#include<audio.h>

ALCdevice* AUDIO::device=NULL;
ALCcontext* AUDIO::context=NULL;




bool isBigEndian()
{
        int a=1;
        return !((char*)&a)[0];
}




int convertToInt(char* buffer,int len)
{
        int a=0;
        if(!isBigEndian())
                for(int i=0;i<len;i++)
                        ((char*)&a)[i]=buffer[i];
        else
                for(int i=0;i<len;i++)
                        ((char*)&a)[3-i]=buffer[i];
        return a;
}




void WAV_FILE::load_wav(const char* fn)
{
        char buffer[4];
        ifstream in(fn,ios::binary);
        if(in==NULL)
        {
            cout<<"ERROR:: FILE MISSING:: "<<fn<<endl;
            return;
        }
                        in.read(buffer,4);
                        if(strncmp(buffer,"RIFF",4)!=0)
                                {  cout<<"ERROR:: FILE :: "<<fn<<endl;
                                    cout << "Description::  this is not a valid WAVE file"  << endl;
                                  return;
                                }

                        in.read(buffer,4);
                        in.read(buffer,4);      //WAVE
                        in.read(buffer,4);      //fmt
                        in.read(buffer,4);      //16
                        in.read(buffer,2);      //1
                        in.read(buffer,2);
                        channels=convertToInt(buffer,2);
                        in.read(buffer,4);
                        sample_rate=convertToInt(buffer,4);
                        in.read(buffer,4);
                        in.read(buffer,2);
                        in.read(buffer,2);
                        bps=convertToInt(buffer,2);
                        in.read(buffer,4);      //data
                        in.read(buffer,4);
                        size=convertToInt(buffer,4);
                        data=new char[size];
                        in.read(data,size);
}





AUDIO::AUDIO()
{
    alGenBuffers(1,&bufferid);
    alGenSources(1,&sourceid);
}


AUDIO::~AUDIO()
{   alDeleteSources(1,&sourceid);
    alDeleteBuffers(1,&bufferid);
}


void AUDIO::Init()
            {
                device=alcOpenDevice(NULL);
                if(device==NULL)
                            {
                                  cout<<"ERROR:: AUDIO_INIT ::  cannot open sound card"<<endl;
                                  return;
                            }
                context=alcCreateContext(device,NULL);
                if(context==NULL)
                            {
                                   cout<<"ERROR:: AUDIO_INIT :: cannot open context"<<endl;
                                   return;
                            }
                alcMakeContextCurrent(context);
            }



void AUDIO::terminate()
            {
                alcDestroyContext(context);
                alcCloseDevice(device);
            }




void AUDIO::load(const char* file_name)
            {
                WAV_FILE file;
                file.load_wav(file_name);
                unsigned int format;
                if(file.channels==1)
                    format= (file.bps==8)?AL_FORMAT_MONO8:AL_FORMAT_MONO16;
                if(file.channels==2)
                    format= (file.bps==8)?AL_FORMAT_STEREO8:AL_FORMAT_STEREO16;

                alBufferData(bufferid,format,file.data,file.size,file.sample_rate);
                alSourcei(sourceid,AL_BUFFER,bufferid);
            }







