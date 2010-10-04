#include "Player.h"

Player::Player(float x, float y, int initScore, int pic){
	xPosition = x;
	yPosition = y;
	score = initScore;
	image = pic;
}
void Player::draw(){
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
void Player::updateScore(int addition){
	score+=addition;
}
void Player::issueCommand(SDL_keysym *keysym){
	
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
//			if(lastShot != 99){
//				shots[lastShot] = new Particle();
//				shots[lastShot++]->updateShot(0.1+xPosition, 0.5+yPosition, 0, ship);
//			}
			break;
		default:
			break;
	}
}

float Player::getX(){
	return xPosition;
}
