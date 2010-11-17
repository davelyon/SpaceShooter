/* this is the main */
#include "Monster.h"
#include "Particle.h"
#include "Player.h"
#include <iostream>
#include <string.h>


#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
//linux includes
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

/* all the global variables needed */
Player *ship = new Player(0,-2.0,0,NULL); 
Particle* shots[100];

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

void glInit() {
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
}

int main (int argc, char **argv){
	
	glInit();
	
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
	
	float crap = 0; //Why? 

	
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
