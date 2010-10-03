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
player *ship = new player(0,0,0,NULL);
using namespace std;
void drawImages();
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
	
	bool done = false;
		while (!done) {
		
			drawImages();
		SDL_Event event;
		while (SDL_PollEvent (&event)) {if (event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE) done = true;}
	}
	SDL_Quit ();
	return 0;
}
void drawImages(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	ship->drawPlayer();
	SDL_GL_SwapBuffers();
}


/* player methods */
player::player(float x, float y, int initScore, int pic){
	xPosition = x;
	yPosition = y;
	score = initScore;
	image = pic;
}
void player::drawPlayer(){
	glLoadIdentity();
	glTranslatef(0.0f, -2.0f, -8.0f);
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
      

      glColor3f(   0.0f,  0.2f,  0.0f ); /* Set The Color To Green           */
      glVertex3f(  corners, 0.0f,  corners ); /* Top Of Triangle (base)       */
      glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */    
      glVertex3f(  corners, stretch, -corners ); /* Left Of Triangle (base)      */
      glVertex3f( -corners, stretch,  corners ); /* Right Of Triangle (base)     */
    glEnd( );  
    
}
