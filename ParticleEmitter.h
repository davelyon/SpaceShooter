/*
 *  ParticleEmitter.h
 *  SpaceRedux
 *
 *  Created by Dave Lyon on 11/30/10.
 *  Copyright 2010 Northern Michigan University. All rights reserved.
 *
 */

#define MAX_PARTICLES 1000

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
	void renderParticles(int tick);
	
	
private:
	particle particles[MAX_PARTICLES];
	
	void renderSetup(void);
	void renderTeardown(void);
	
	static ParticleEmitter *singletonInstance;

};