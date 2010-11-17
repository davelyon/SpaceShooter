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
#endif
