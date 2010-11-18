#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGl/glu.h>
#include <SDL/SDL_audio.h>
#else //linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_audio.h>
#include <string>
#include <cstdlib>
#include "SoundManager.h"
#endif
#define NUM_SOUNDS 20
using namespace std;
SoundManager::SoundManager(){
	toPlay = new string[20];
	count = 0;
	muted = 0;
}

SoundManager::~SoundManager(){}

void SoundManager::play(){
	for(int i = 0; i < count; i++)
		PlaySound(toPlay[i].c_str());
}

void SoundManager::enqueue(string aSound){
	toPlay[count++] = aSound;
}

void SoundManager::mute(){
	SDL_PauseAudio(muted);
	muted = !muted;
}

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
		fprintf(stderr, "couldn't laod 5s: %sn", file, SDL_GetError());
		exit(0);
	}
	SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16, 2, 44100);
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
