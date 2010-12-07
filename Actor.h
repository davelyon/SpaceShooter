#ifndef TheActors
#define TheActors


#ifdef MAC_OSX_BUILD_MODE
#ifndef SERVER_COMPILE_FLAG
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <SDL/SDL_audio.h>
#include "SDL_image.h"
#endif
#else // Linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_audio.h>
#include "SDL/SDL_image.h"
#endif

#define OWNER_P1 1
#define OWNER_P2 2
#define OWNER_GAME 3

#define MOVE_NONE		0
#define MOVE_RIGHT		1
#define MOVE_LEFT		2
#define MOVE_UP			3
#define MOVE_DOWN		4




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
	virtual void takeDamage();
	// Information
	virtual int 	points();
	virtual int 	belongsTo(); // Who owns this? 1,2 are players, 3 is 'game'
	virtual bool 	living();
	
	virtual float getX();
	virtual float getY();
	int pointValue;
	int owner;
	
	bool isLiving;
	
};

#endif
