
#ifndef TheShip
#define TheShip

#ifdef MAC_OS_X_VERSION_MIN_REQUIRED

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <SDL/SDL_audio.h>
#else // Linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <glu.h>
#include <SDL/SDL_audio.h>
#endif


class Player {
	float xPosition;
	float yPosition;
	int image;
	int score;
	public:	
	Player(float x, float y, int score, int pic);
	void issueCommand(SDL_keysym *keysym);
	void draw();
	void updateScore(int add);
	float getX();
};
#endif
	
