#include "Enemy.h"

Enemy::Enemy(){

	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = -5.0f;

}

Enemy::Enemy(int uniqueID, int x, int y, int health, int pointValue) {
	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = -5.0f;
	this->location_y = -5.0f;
}

Enemy::~Enemy() {
	
}
std::string Enemy::toString(){

	return "Needs Implementation";

}
void 	Enemy::update(int uID, int x, int y, int health, int pointValue) {
	this->location_x += 0.0002f;
	this->location_y += 0.0002f;
	
}
void 	Enemy::draw() 	{
	

}
bool 	Enemy::collideWith(Actor *anActor) {return false;}

//	glLoadIdentity();
//	
//	glTranslatef(location_x,location_y, -8.0f);
//	glRotatef( 45, 0.0f, -1.0f, 0.0f );
//	float corners = .2;
//	float top = .75;
//	float stretch = -0.2;
//	glBegin( GL_TRIANGLES );             /* Drawing Using Triangles       */
//	glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
//	glVertex3f(  0.0f,  top,  0.0f ); /* Top Of Triangle (left)       */  
//	glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */   
//	glVertex3f( -corners, stretch,  corners ); /* Left Of Triangle (left)      */
//	glColor3f(   0.0f,  0.2f,  0.0f ); /* Set The Color To Green           */   
//	glVertex3f(  corners, 0.0f,  corners ); /* Right Of Triangle (left)     */
//	
//	
//	glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
//	glVertex3f(  0.0f,  top,  0.0f ); /* Top Of Triangle (right)       */ 
//	glColor3f(   0.0f,  0.2f,  0.0f ); /* Set The Color To Green           */   
//	glVertex3f(  corners, 0.0f,  corners ); /* Left Of Triangle (right)     */
//	glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */    
//	glVertex3f(  corners, stretch, -corners ); /* Right Of Triangle (right)      */
//	
//	glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
//	glVertex3f(  0.0f,  top,  0.0f ); /* Top Of Triangle (bottom)       */  
//	glColor3f(   0.0f,  0.5f,  0.0f ); /* Set The Color To Green           */       
//	glVertex3f(  corners, stretch, -corners ); /* Left Of Triangle (bottom)      */
//	glVertex3f( -corners, stretch,  corners ); /* Right Of Triangle (bottom)     */
//	
//	
//	glColor3f(   0.0f,  0.2f,  0.0f ); 
//	glVertex3f(  corners, 0.0f,  corners ); 
//	glColor3f(   0.0f,  0.5f,  0.0f );   
//	glVertex3f(  corners, stretch, -corners );
//	glVertex3f( -corners, stretch,  corners );
//	glEnd( );

