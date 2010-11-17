#include "Player.h"


Player::Player(int playerNumber) {
	this->pointValue = 0;
	this->owner = playerNumber;
	
	this->isLiving = true;
	this->health = 50;
	
	this->location_x = 0.0f;
	this->location_y = 0.0f;
}

Player::~Player() {}

void 	Player::update(int ticks, int movedir) {
	
	float movPixels = ((float)ticks/1000.0f) * 0.22;
	
	switch (movedir) {
		case MOVE_NONE:
			break;
		case MOVE_RIGHT:
			location_x += movPixels;
			break;
		case MOVE_LEFT:
			location_x -= movPixels;
			break;
		case MOVE_UP:
			location_y += movPixels;
			break;
		case MOVE_DOWN:
			location_y -= movPixels;
			break;
		default:
			break;
	}
	
}
void 	Player::draw() { 	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	glTranslatef(location_x,location_y, -8.0f);
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
	
	SDL_GL_SwapBuffers();
}
bool 	Player::collideWith(Actor *anActor) {return false;}
int 	Player::points() 		{ return 0;}

// **********
// Enemy
// **********

Enemy::Enemy(int pointValue) {
	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	
}
Enemy::~Enemy() {
	
}

void 	Enemy::update() {}
void 	Enemy::draw() 	{}
bool 	Enemy::collideWith(Actor *anActor) {return false;}

