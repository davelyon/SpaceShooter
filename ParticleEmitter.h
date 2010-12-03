/*
 *  ParticleEmitter.h
 *  SpaceRedux
 *
 *  Created by Dave Lyon on 11/30/10.
 *  Copyright 2010 Northern Michigan University. All rights reserved.
 *
 */

#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include "SDL_image.h"
#else // Linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL_image.h"
#endif

#include "Textures.h"

#define MAX_PARTICLES 300
#define TRUE 1
#define FALSE 0
static GLfloat colors[12][3] =
{
	{ 1.0f,  0.5f,  0.5f},
	{ 1.0f,  0.75f, 0.5f},
	{ 1.0f,  1.0f,  0.5f},
	{ 0.75f, 1.0f,  0.5f},
	{ 0.5f,  1.0f,  0.5f},
	{ 0.5f,  1.0f,  0.75f},
	{ 0.5f,  1.0f,  1.0f},
	{ 0.5f,  0.75f, 1.0f},
	{ 0.5f,  0.5f,  1.0f},
	{ 0.75f, 0.5f,  1.0f},
	{ 1.0f,  0.5f,  1.0f},
	{ 1.0f,  0.5f,  0.75f}
};

typedef struct {
	int   active; /* Active (Yes/No) */
	float life;   /* Particle Life   */
	float fade;   /* Fade Speed      */
	
	float r;      /* Red Value       */
	float g;      /* Green Value     */
	float b;      /* Blue Value      */
	
	float x;      /* X Position      */
	float y;      /* Y Position      */
	float z;      /* Z Position      */
	
	float xi;     /* X Direction     */
	float yi;     /* Y Direction     */
	float zi;     /* Z Direction     */
	
	float xg;     /* X Gravity       */
	float yg;     /* Y Gravity       */
	float zg;     /* Z Gravity       */
} particle;

class ParticleEmitter {
public:
	// Constructor [Should be private... but not working >.<]
	ParticleEmitter();
	
	// Create a 'laser' particle a the specified location
	void emitLaser(float xloc, float yloc);
	
	// Create an 'explosion' particle at the specified location [Usually the location of a collision]
	void emitExploder(float xloc, float yloc);
	
	// Called by gameloop to render all active particles
	void renderParticles(int tick, float ship_x, float ship_y);
	
	
private:
	particle particles[MAX_PARTICLES];
	void ResetParticle( int num, int color, float xDir, float yDir, float zDir );
	void renderSetup(void);
	void renderTeardown(void);
	
	static ParticleEmitter *singletonInstance;
	
	int rainbow;   /* Toggle rainbow effect                              */
	
	float slowdown; /* Slow Down Particles                                */
	float xspeed;          /* Base X Speed (To Allow Keyboard Direction Of Tail) */
	float yspeed;          /* Base Y Speed (To Allow Keyboard Direction Of Tail) */
	float zoom;   /* Used To Zoom Out                                   */
	
	GLuint loop;           /* Misc Loop Variable                                 */
	GLuint col;        /* Current Color Selection                            */

};
