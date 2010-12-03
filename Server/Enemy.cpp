#include "Enemy.h"
#include <iostream>
#include <ctime>


Enemy::Enemy(){

	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = -5.0f;
	this->location_y = -5.0f;
#ifndef SERVER_COMPILE_FLAG
	this->texture = -1;
#endif	
	uniqueID = 0;
	myHealth = 0;

}

Enemy::Enemy(int uID, float xI, float yI, int health, int pointValue) {
	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = (float)xI;
	this->location_y = (float)yI;
#ifndef SERVER_COMPILE_FLAG
	this->texture = -1;
#endif
	uniqueID = uID;
	myHealth = health;
}

Enemy::~Enemy() {
	
}
void Enemy::toString(char * output){
	sprintf(output, "%d %f %f %d %d", uniqueID, this->location_x, this->location_y, myHealth, this->pointValue);
}
void 	Enemy::update(int uID, float xI, float yI, int health, int pointValue) {
	this->location_x = xI;
	this->location_y = yI;
	uniqueID = uID;
	myHealth = health;
	this->pointValue = pointValue;
}
void Enemy::update(){
	int direction = (rand()%4)+1;
	switch(direction){
		case 1:
			this->location_x += 0.2f;
			this->location_y += 0.2f;
			break;
		case 2:
			this->location_x += 0.2f;
			this->location_y -= 0.2f;
			break;
		case 3:
			this->location_x -= 0.2f;
			this->location_y += 0.2f;
			break;
		case 4:
			this->location_x -= 0.2f;
			this->location_y -= 0.2f;
			break;
	}
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

