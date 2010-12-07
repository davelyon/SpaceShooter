/*
 *  ParticleEmitter.cpp
 *  SpaceRedux
 *
 *  Created by Dave Lyon on 11/30/10.
 *  Copyright 2010 Northern Michigan University. All rights reserved.
 *
 */

#include "ParticleEmitter.h"

ParticleEmitter* ParticleEmitter::singletonInstance = NULL;

ParticleEmitter* ParticleEmitter::Instance() {
	if( singletonInstance == NULL )
		singletonInstance = new ParticleEmitter();
	 return singletonInstance;
}

ParticleEmitter::ParticleEmitter() {
	rainbow = TRUE;    /* Toggle rainbow effect                              */
	texture = part_texture();
	slowdown = 4.0f; /* Slow Down Particles                                */
	zoom = -8.0f;   /* Used To Zoom Out                                   */
	col = 0;
	exploderCounter = 0;
	
	/* Reset all the shipParticles */
	for ( loop = 0; loop < MAX_PARTICLES; loop++ )
	{
		int color = ( loop + 1 ) / ( MAX_PARTICLES / 12 );
		float xi, yi, zi;
		xi =  ( float )( ( rand( ) % 50 ) - 26.0f ) * 10.0f;
		yi = zi = ( float )( ( rand( ) % 50 ) - 25.0f ) * 10.0f;
		
		ResetParticle( loop, color, xi, yi, zi );
  }
}

void	ParticleEmitter::emitLaser(float xloc, float yloc) {
}

void	ParticleEmitter::emitExploder(float xloc, float yloc) {

}

void	ParticleEmitter::renderParticles(int tick, float ship_x, float ship_y){
	glPushMatrix();
	glTranslatef(ship_x, ship_y-0.5f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glScalef(0.3f, 0.3f, 1.0f);
	/* Modify each of the shipParticles */
	for ( loop = 0; loop < MAX_PARTICLES; loop++ )
	{
		if ( shipParticles[loop].active )
		{
			/* Grab Our Particle X Position */
			float x = shipParticles[loop].x;
			/* Grab Our Particle Y Position */
			float y = shipParticles[loop].y;
			/* Particle Z Position + Zoom */
			float z = shipParticles[loop].z + zoom;
			
			/* Draw The Particle Using Our RGB Values,
			 * Fade The Particle Based On It's Life
			 */
			glColor4f( shipParticles[loop].r,
								shipParticles[loop].g,
								shipParticles[loop].b,
								shipParticles[loop].life );
			
			/* Build Quad From A Triangle Strip */
			glBegin( GL_TRIANGLE_STRIP );
			/* Top Right */
			glTexCoord2d( 1, 1 );
			glVertex3f( x + 0.5f, y + 0.5f, z );
			/* Top Left */
			glTexCoord2d( 0, 1 );
			glVertex3f( x - 0.5f, y + 0.5f, z );
			/* Bottom Right */
			glTexCoord2d( 1, 0 );
			glVertex3f( x + 0.5f, y - 0.5f, z );
			/* Bottom Left */
			glTexCoord2d( 0, 0 );
			glVertex3f( x - 0.5f, y - 0.5f, z );
			glEnd();
						
			/* Move On The X Axis By X Speed */
			shipParticles[loop].x += shipParticles[loop].xi /
			( slowdown * 1000 );
			/* Move On The Y Axis By Y Speed */
			shipParticles[loop].y += shipParticles[loop].yi /
			( slowdown * 1000 );
			/* Move On The Z Axis By Z Speed */
			shipParticles[loop].z += shipParticles[loop].zi /
			( slowdown * 1000 );
			
			/* Take Pull On X Axis Into Account */
			shipParticles[loop].xi += shipParticles[loop].xg;
			/* Take Pull On Y Axis Into Account */
			shipParticles[loop].yi += shipParticles[loop].yg;
			/* Take Pull On Z Axis Into Account */
			shipParticles[loop].zi += shipParticles[loop].zg;
			
			/* Reduce shipParticles Life By 'Fade' */
			shipParticles[loop].life -= shipParticles[loop].fade;
			
			/* If the particle dies, revive it */
			if ( shipParticles[loop].life < 0.0f )
			{
				float xi, yi, zi;
				xi = xspeed +
				( float )( ( rand( ) % 60 ) - 32.0f );
				yi = yspeed +
				( float)( ( rand( ) % 60 ) - 30.0f );
				zi = ( float )( ( rand( ) % 60 ) - 30.0f );
				ResetParticle( loop, col, xi, yi, zi );
			}
		}
	}
	glPopMatrix();
}


void	ParticleEmitter::renderSetup(void) {

}

void	ParticleEmitter::renderTeardown(void) {
	
}
void ParticleEmitter::ResetParticle( int num, int color, float xDir, float yDir, float zDir )
{
	/* Make the particels active */
	shipParticles[num].active = TRUE;
	/* Give the shipParticles life */
	shipParticles[num].life = 1.0f;
	/* Random Fade Speed */
	shipParticles[num].fade = ( float )( rand( ) %100 ) / 1000.0f + 0.003f;
	/* Select Red Rainbow Color */
	shipParticles[num].r = colors[rand() % 3][0];
	/* Select Green Rainbow Color */
	shipParticles[num].g = colors[rand() % 3][1];
	/* Select Blue Rainbow Color */
	shipParticles[num].b = colors[rand() % 3][2];
	/* Set the position on the X axis */
	shipParticles[num].x = 0.0f;
	/* Set the position on the Y axis */
	shipParticles[num].y = 0.0f;
	/* Set the position on the Z axis */
	shipParticles[num].z = 0.0f;
	/* Random Speed On X Axis */
	shipParticles[num].xi = xDir;
	/* Random Speed On Y Axi */
	shipParticles[num].yi = yDir;
	/* Random Speed On Z Axis */
	shipParticles[num].zi = zDir;
	/* Set Horizontal Pull To Zero */
	shipParticles[num].xg = 0.0f;
	/* Set Vertical Pull Downward */
	shipParticles[num].yg = -0.8f;
	/* Set Pull On Z Axis To Zero */
	shipParticles[num].zg = 0.0f;
	
	return;
}

