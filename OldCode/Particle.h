#ifndef TheShots
#define TheShots

#include "Player.h"

#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <SDL/SDL_audio.h>
#else // Linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_audio.h>
#endif


class Particle{
	float x, y;
	int image;
	GLUquadricObj *quadratic;

public:
	Particle();
	void	updateShot(float startX, float startY, int image, Player *ship);
	void  draw();
	float getX();
	float getY();
	void  collision(Player *ship);
	
};

#endif
