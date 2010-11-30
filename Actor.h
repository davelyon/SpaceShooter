#ifndef TheActors
#define TheActors

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

#define OWNER_P1 1
#define OWNER_P2 2
#define OWNER_GAME 3

#define MOVE_NONE		0
#define MOVE_RIGHT		1
#define MOVE_LEFT		2
#define MOVE_UP			3
#define MOVE_DOWN		4

#include "SDL_image.h"



class Actor
{
public:
	Actor ();
	Actor (Actor &actor);
	virtual ~Actor ();

	// Actions
	virtual void 	update();
	virtual void 	draw();
	virtual bool 	collideWith(Actor *anActor);
	
	// Information
	virtual int 	points();
	virtual int 	belongsTo(); // Who owns this? 1,2 are players, 3 is 'game'
	virtual bool 	living();
		
	int pointValue;
	int owner;
	
	bool isLiving;
	
};

GLuint load_texture(const char *file);
#endif
