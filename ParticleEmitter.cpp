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
<<<<<<< HEAD
	texture = part_texture();
	slowdown = 4.0f; /* Slow Down Particles                                */
	zoom = -8.0f;   /* Used To Zoom Out                                   */
	col = 0;
	exploderCounter = 0;
	
	for(loop = 0; loop < 50; loop++) {
		int color = 1;
		float xi, yi, zi;
		xi =  ( float )( ( rand( ) % 50 ) - 26.0f ) * 10.0f;
		yi = zi = ( float )( ( rand( ) % 50 ) - 25.0f ) * 10.0f;
		ResetLaserParticle(loop, color, xi, yi, zi, true);
	}
	
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

void	ParticleEmitter::renderShipParticles(int tick, float ship_x, float ship_y){
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );
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
}

void	ParticleEmitter::renderLaserParticles(int tick, int laserX, int laserY){
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity( );
	glTranslatef(laserX, laserY, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
	glScalef(0.3f, 0.3f, 1.0f);

	for ( loop = 0; loop < 10; loop++ )
	{
		if ( laserParticles[loop].active )
		{
			/* Grab Our Particle X Position */
			float x = laserParticles[loop].x;
			/* Grab Our Particle Y Position */
			float y = laserParticles[loop].y;
			/* Particle Z Position + Zoom */
			float z = laserParticles[loop].z + zoom;
			
			/* Draw The Particle Using Our RGB Values,
			 * Fade The Particle Based On It's Life
			 */
			glColor4f( laserParticles[loop].r,
								laserParticles[loop].g,
								laserParticles[loop].b,
								laserParticles[loop].life );
			
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
			laserParticles[loop].x += laserParticles[loop].xi /
			( slowdown * 1000 );
			/* Move On The Y Axis By Y Speed */
			laserParticles[loop].y += laserParticles[loop].yi /
			( slowdown * 1000 );
			/* Move On The Z Axis By Z Speed */
			laserParticles[loop].z += laserParticles[loop].zi /
			( slowdown * 1000 );
			
			
			/* Reduce laserParticles Life By 'Fade' */
			laserParticles[loop].life -= laserParticles[loop].fade;
			
			/* If the particle dies, revive it */
			/* If the particle dies, revive it */
			if ( shipParticles[loop].life < 0.0f )
			{
				float xi, yi, zi;
				xi = xspeed +
				( float )( ( rand( ) % 60 ) - 32.0f );
				yi = yspeed +
				( float)( ( rand( ) % 60 ) - 30.0f );
				zi = ( float )( ( rand( ) % 60 ) - 30.0f );
				ResetLaserParticle( loop, col, xi, yi, zi, true );
			}
		}
	}
	
	printf("Done with frickin' lasers\n");
	glFinish();

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

void ParticleEmitter::ResetLaserParticle( int num, int color, float xDir, float yDir, float zDir, bool living )
{
	laserParticles[num].active = living;
	/* Give the laserParticles life */
	laserParticles[num].life = 1.0f;
	/* Random Fade Speed */
	laserParticles[num].fade = ( float )( rand( ) %100 ) / 1000.0f + 0.003f;
	/* Select Red Rainbow Color */
	laserParticles[num].r = colors[rand() % 3][0];
	/* Select Green Rainbow Color */
	laserParticles[num].g = colors[rand() % 3][1];
	/* Select Blue Rainbow Color */
	laserParticles[num].b = colors[rand() % 3][2];
	/* Set the position on the X axis */
	laserParticles[num].x = 0.0f;
	/* Set the position on the Y axis */
	laserParticles[num].y = 0.0f;
	/* Set the position on the Z axis */
	laserParticles[num].z = 0.0f;
	/* Random Speed On X Axis */
	laserParticles[num].xi = xDir;
	/* Random Speed On Y Axi */
	laserParticles[num].yi = yDir;
	/* Random Speed On Z Axis */
	laserParticles[num].zi = zDir;
	/* Set Horizontal Pull To Zero */
	laserParticles[num].xg = 0.0f;
	/* Set Vertical Pull Downward */
	laserParticles[num].yg = -0.8f;
	/* Set Pull On Z Axis To Zero */
	laserParticles[num].zg = 0.0f;
	
	return;
}
