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
	static SoundManager* Instance();
	~SoundManager();

	struct sample {
		Uint8 *data;
		Uint32 dpos;
		Uint32 dlen;
	}sounds[20];

	void PlaySound(const char *file);
	void set(sample asdf[20]);
	
	SoundManager();

private:
	static SoundManager* singletonInstance;
	
};

#endif
