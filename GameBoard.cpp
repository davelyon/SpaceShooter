/* this is the main */
#include "monster.h"
#include "particle.h"
#include "player.h"
#include <iostream>
#include <string.h>

/* all the global variables needed */
player *ship = new player(0,0,0,NULL);
using namespace std;

int main (int argc, char **argv){
	player->drawPlayer();
	return 0;
}


/* player methods */
player::player(float x, float y, int score, int pic){
	xPosition = x;
	yPosition = y;
	this.score = score;
	image = pic;
}
void player::drawPlayer(){
	glLoadIdentity();
	glTranslatef(0.0f, -2.0f, -8.0f)
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
