/* this is the main */
#include "monster.h"
#include "particle.h"
#include "player.h"
#include <iostream>
#include <string.h>

//linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL_audio.h>

/* all the global variables needed */
player *ship = new player(0,-2.0,0,NULL); 
particle* shots[100];
int firstShot = 0;
int lastShot = 0;
bool threeD = false;
GLUquadricObj *quadratic;
using namespace std;
void drawImages();
void draw3d();
float xMove = 0;
float yMove = 0;
float movement = .1;
float crap = 0;
int main (int argc, char **argv){
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_SetVideoMode(640,480,0,SDL_OPENGL);
	SDL_WM_SetCaption("Circles",NULL);

	glViewport (0,0,640,480);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45,640.0/480,0.1,100);
//	gluOrtho2D(0,640,0,480);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
//	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable (GL_DEPTH_TEST);
	glClearColor (1,1,1,0);
	quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
	for(int i = 0; i < 100; i++)
		shots[i] = NULL;
	bool done = false;
	int TC = 0;
	while (!done) {
		if (SDL_GetTicks()%70 == 00) {
			TC = SDL_GetTicks();
			if(firstShot != lastShot)
				for(int i = firstShot; i < lastShot; i++)
					shots[i]->updateShot(shots[i]->getX(), shots[i]->getY()+0.1, 0, ship);
		if(!threeD)
			drawImages();
		else
			draw3d();
		}
		SDL_Event event;
		while (SDL_PollEvent (&event)) {
			if (event.type==SDL_KEYDOWN)
				switch(event.key.keysym.sym){
					case(SDLK_ESCAPE):
						done = true;
						break;
					case(SDLK_w):
						yMove=movement;
						break;
					case(SDLK_s):
						yMove= -movement;
						break;
					case(SDLK_a):
						xMove= movement;
						break;
					case(SDLK_d):
						xMove= -movement;
						break;
					default:
						ship->issueCommand(&event.key.keysym);
						break;
				}
		}
	}
	SDL_Quit ();
	return 0;
}
/* Game Board Methods */
void drawImages(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	ship->draw();
	for(int i = 0; i < 100; i++){
		if(shots[i]==NULL)
			break;
		shots[i]->draw();
	}
	SDL_GL_SwapBuffers();
}
void draw3d(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
    glTranslatef(0.0+xMove,0.0,-4.0+yMove);

    glRotatef( crap, 0.0f, 0.0f, 1.0f );
	glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
    gluCylinder(quadratic,1.0f,1.0f,2.5f,32,32);
    	glLoadIdentity();
    glTranslatef(0.0+xMove,0.0,-6.5+yMove);
    glRotatef( crap, 0.0f, 0.0f, 1.0f );
    glColor3f(   1.0f,  1.0f,  0.0f ); 
    gluCylinder(quadratic,1.0f,1.0f,2.5f,32,32);
    	glLoadIdentity();
    glTranslatef(0.0+xMove,0.0,-9.0+yMove);
    glRotatef( crap, 0.0f, 0.0f, 1.0f );
    glColor3f(   1.0f,  0.0f,  1.0f ); 
    gluCylinder(quadratic,1.0f,1.0f,2.5f,32,32);
    glBegin(GL_QUADS);
    	glColor3f(0.0f, 1.0f, 0.0f);
    	glVertex3f(-1.0f, 0.0f, 1.0f);
    	glVertex3f(1.0f, 0.0f, 1.0f);
    	glVertex3f(1.0f, 1.0f, 1.0f);
    	glVertex3f(-1.0f, 1.0f, 1.0f);
    glEnd();
    	glLoadIdentity();
    glTranslatef(0.0+xMove,0.0,-11.5+yMove);
    glRotatef( crap, 0.0f, 0.0f, 1.0f );
    glColor3f(   0.0f,  0.0f,  1.0f ); 
    gluCylinder(quadratic,1.0f,1.0f,2.5f,32,32);

    if(yMove>0)
    	yMove+=.2;
    if(xMove>0)
    	xMove+=.2;
	if(yMove<0)
    	yMove-=.2;
    if(xMove<0)
    	xMove-=.2;
    	crap+=.5;
    SDL_GL_SwapBuffers();
}

/* player methods */
player::player(float x, float y, int initScore, int pic){
	xPosition = x;
	yPosition = y;
	score = initScore;
	image = pic;
}
void player::draw(){
	glLoadIdentity();
	glTranslatef(xPosition, yPosition, -8.0f);
	glRotatef( 45, 0.0f, -1.0f, 0.0f );
	float corners = .2;
	float top = .75;
	float stretch = -0.2;
    glBegin( GL_TRIANGLES );             /* Drawing Using Triangles       */
      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  top,  0.0f ); /* Top Of Triangle (left)       */  
      glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */   
      glVertex3f( -corners, stretch,  corners ); /* Left Of Triangle (left)      */
      glColor3f(   0.0f,  0.2f,  0.0f ); /* Set The Color To Green           */   
      glVertex3f(  corners, 0.0f,  corners ); /* Right Of Triangle (left)     */
      

      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  top,  0.0f ); /* Top Of Triangle (right)       */ 
      glColor3f(   0.0f,  0.2f,  0.0f ); /* Set The Color To Green           */   
      glVertex3f(  corners, 0.0f,  corners ); /* Left Of Triangle (right)     */
      glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */    
      glVertex3f(  corners, stretch, -corners ); /* Right Of Triangle (right)      */
      
      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  top,  0.0f ); /* Top Of Triangle (bottom)       */  
      glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */       
      glVertex3f(  corners, stretch, -corners ); /* Left Of Triangle (bottom)      */
      glVertex3f( -corners, stretch,  corners ); /* Right Of Triangle (bottom)     */
      

      glColor3f(   0.0f,  0.2f,  0.0f ); 
      glVertex3f(  corners, 0.0f,  corners ); 
      glColor3f(   0.0f,  0.5f,  0.0f );   
      glVertex3f(  corners, stretch, -corners );
      glVertex3f( -corners, stretch,  corners );
    glEnd( );

     
    
}
void player::updateScore(int addition){
	score+=addition;
}
void player::issueCommand(SDL_keysym *keysym){
	
	switch ( keysym->sym )
	{
		case(SDLK_UP):
			yPosition+=.2;
			blargh += .2;
			break;
		case(SDLK_DOWN):
			yPosition-=.2;
			blargh -= .2;
			break;
		case(SDLK_RIGHT):
			xPosition+=.2;
			break;
		case(SDLK_LEFT):
			xPosition-=.2;
			break;
		case(SDLK_SPACE):
			if(lastShot != 99){
				shots[lastShot] = new particle();
				shots[lastShot++]->updateShot(0.1+xPosition, 0.5+yPosition, 0, ship);
			}
			break;
		default:
			break;
	}
}

float player::getX(){
	return xPosition;
}

/* particle methods */
particle::particle(){
	x = 0;
	y = 0;
	image = 0;
}
void particle::updateShot(float startX, float startY, int image, player *ship){
	x = startX;
	y = startY;
	image = image;
	collision(ship);
}
void particle::draw(){
	glColor3f(   0.0f,  0.0f,  0.0f );
	/* left shot */
	glLoadIdentity();
	glTranslatef(x, y, -8.0f); 
    gluSphere(quadratic,0.02f,32,32);
    
    /* right shot */
    glLoadIdentity();
    glTranslatef(x-0.2, y, -8.0f); 
    gluSphere(quadratic,0.02f,32,32);
}
float particle::getX(){
	return x;
}
float particle::getY(){
	return y;
}
void particle::collision(player *ship){
	if(true)
		ship->updateScore(10);
}





