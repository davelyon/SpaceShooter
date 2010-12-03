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

ParticleEmitter::ParticleEmitter() {
	rainbow = TRUE;    /* Toggle rainbow effect                              */
	
	slowdown = 2.0f; /* Slow Down Particles                                */
	zoom = -40.0f;   /* Used To Zoom Out                                   */
	col = 0;
	
	/* Reset all the particles */
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
	
	glLoadIdentity( );
	glTranslatef(ship_x, ship_y, -24.0f);
	glBindTexture(GL_TEXTURE_2D, load_texture(PARTICLE));
	/* Modify each of the particles */
	for ( loop = 0; loop < MAX_PARTICLES; loop++ )
	{
		if ( particles[loop].active )
		{
			/* Grab Our Particle X Position */
			float x = particles[loop].x;
			/* Grab Our Particle Y Position */
			float y = particles[loop].y;
			/* Particle Z Position + Zoom */
			float z = particles[loop].z + zoom;
			
			/* Draw The Particle Using Our RGB Values,
			 * Fade The Particle Based On It's Life
			 */
			glColor4f( particles[loop].r,
								particles[loop].g,
								particles[loop].b,
								particles[loop].life );
			
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
			particles[loop].x += particles[loop].xi /
			( slowdown * 1000 );
			/* Move On The Y Axis By Y Speed */
			particles[loop].y += particles[loop].yi /
			( slowdown * 1000 );
			/* Move On The Z Axis By Z Speed */
			particles[loop].z += particles[loop].zi /
			( slowdown * 1000 );
			
			/* Take Pull On X Axis Into Account */
			particles[loop].xi += particles[loop].xg;
			/* Take Pull On Y Axis Into Account */
			particles[loop].yi += particles[loop].yg;
			/* Take Pull On Z Axis Into Account */
			particles[loop].zi += particles[loop].zg;
			
			/* Reduce Particles Life By 'Fade' */
			particles[loop].life -= particles[loop].fade;
			
			/* If the particle dies, revive it */
			if ( particles[loop].life < 0.0f )
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
}

void	ParticleEmitter::renderSetup(void) {

}

void	ParticleEmitter::renderTeardown(void) {
	
}
void ParticleEmitter::ResetParticle( int num, int color, float xDir, float yDir, float zDir )
{
	/* Make the particels active */
	particles[num].active = TRUE;
	/* Give the particles life */
	particles[num].life = 1.0f;
	/* Random Fade Speed */
	particles[num].fade = ( float )( rand( ) %100 ) / 1000.0f + 0.003f;
	/* Select Red Rainbow Color */
	particles[num].r = colors[color][0];
	/* Select Green Rainbow Color */
	particles[num].g = colors[color][1];
	/* Select Blue Rainbow Color */
	particles[num].b = colors[color][2];
	/* Set the position on the X axis */
	particles[num].x = 0.0f;
	/* Set the position on the Y axis */
	particles[num].y = 0.0f;
	/* Set the position on the Z axis */
	particles[num].z = 0.0f;
	/* Random Speed On X Axis */
	particles[num].xi = xDir;
	/* Random Speed On Y Axi */
	particles[num].yi = yDir;
	/* Random Speed On Z Axis */
	particles[num].zi = zDir;
	/* Set Horizontal Pull To Zero */
	particles[num].xg = 0.0f;
	/* Set Vertical Pull Downward */
	particles[num].yg = -0.8f;
	/* Set Pull On Z Axis To Zero */
	particles[num].zg = 0.0f;
	
	return;
}
