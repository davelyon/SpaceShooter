#ifndef AudibleMagic
#define AudibleMagic

#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
#include <SDL/SDL_audio.h>
#include <string>
#else //linux includes
#include <SDL/SDL_audio.h>
#include <string>
#endif
using namespace std;

class SoundManager{
	public:
		SoundManager();
		~SoundManager();
		void play(); // plays sounds
		void enqueue(string aSound);
		void mute(); //disable all sound output
		struct sample {
			Uint8 *data;
			Uint32 dpos;
			Uint32 dlen;
		}sounds[20];
		string *toPlay;
		int count;
		int muted;
		void mixaudio(void *unused, Uint8 *stream, int len);
		void PlaySound(const char *file);
};

#endif
