#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
#include <SDL/SDL_audio.h>
#include <string>
#include "SoundManager.h"
#else //linux includes
#include <SDL/SDL_audio.h>
#include <string>
#include "SoundManager.h"
#endif
#define NUM_SOUNDS 20
using namespace std;

SoundManager* SoundManager::singletonInstance = NULL;

void mixaudio2(void *unused, Uint8 *stream, int len) {
	SoundManager::Instance()->mixaudio(unused, stream,len);
}


SoundManager *SoundManager::Instance() {
	if(singletonInstance == NULL) {
		singletonInstance = new SoundManager;
	}
	return singletonInstance;
}

SoundManager::SoundManager(){
	
	SDL_AudioSpec fmt;
	
  /* Set 16-bit stereo audio at 22Khz */
  fmt.freq = 22050;
  fmt.format = AUDIO_S16;
  fmt.channels = 2;
  fmt.samples = 4096; /* A good value for games */
  fmt.callback = &mixaudio2;
  fmt.userdata = NULL;
	
	memset(sounds,0,sizeof sounds);
	
  /* Open the audio device and start playing sound! */
  if ( SDL_OpenAudio(&fmt, NULL) < 0 ) {
    fprintf(stderr, "Unable to open audio: %sn", 
						SDL_GetError());
		exit(1);
  } 
	
	SDL_PauseAudio (0);
}

SoundManager::~SoundManager(){}


void SoundManager::mixaudio(void *unused, Uint8 *stream, int len){
	int i;
	Uint32 amount;
	for (i=0; i<NUM_SOUNDS; ++i) {
		amount = (sounds[i].dlen-sounds[i].dpos);
		if(amount > len){
			amount = len;
		}
		SDL_MixAudio(stream, &sounds[i].data[sounds[i].dpos], amount, SDL_MIX_MAXVOLUME);
		sounds[i].dpos += amount;
	}
}

void SoundManager::PlaySound(const char *file){
	int index;
	SDL_AudioSpec wave;
	Uint8 *data;
	Uint32 dlen;
	SDL_AudioCVT cvt;

	for ( index=0; index<NUM_SOUNDS; ++index){
		if(sounds[index].dpos == sounds[index].dlen){
			break;
		}
	}
	if(index == NUM_SOUNDS)
		return;

	if(SDL_LoadWAV(file, &wave, &data, &dlen) == NULL){
		fprintf(stderr, "couldn't load %s: %s \n", file, SDL_GetError());
		exit(0);
	}
	SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16, 1, 44100);
	cvt.buf = (Uint8 *)malloc(dlen*cvt.len_mult);
	memcpy(cvt.buf, data, dlen);
	cvt.len == dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);

	if(sounds[index].data){
		free(sounds[index].data);
	}
	SDL_LockAudio();
	sounds[index].data = cvt.buf;
	sounds[index].dlen = cvt.len_cvt;
	sounds[index].dpos = 0;
	SDL_UnlockAudio();
}
