#include "Enemy.h"
#include <iostream>
#include <ctime>


Enemy::Enemy(){

	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = -5.0f;
	this->start_x_loc = this->location_x;
	this->location_y = -5.0f;
	this->start_y_loc = this->location_y;
#ifndef SERVER_COMPILE_FLAG
	this->texture = load_texture(PLAYER2);
#endif	
	uniqueID = 0;
	myHealth = 0;

}

Enemy::Enemy(int uID, float xI, float yI, int health, int pointValue) {
	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = xI;
	this->start_x_loc = this->location_x;
	this->location_y = yI;
	this->start_y_loc = this->location_y;
#ifndef SERVER_COMPILE_FLAG
	this->texture = load_texture(PLAYER2);
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
	this->start_x_loc = this->location_x;
	this->location_y = yI;
	this->start_y_loc = this->location_y;
	uniqueID = uID;
	myHealth = health;
	this->pointValue = pointValue;
}
void Enemy::update(){
/*	int direction = (rand()%4)+1;
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
	}*/
	diamond();
}
void 	Enemy::draw() 	{
#ifndef SERVER_COMPILE_FLAG
	glLoadIdentity();
	glTranslatef(location_x,location_y, -24.0f);
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_ONE, GL_SRC_ALPHA);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
	glEnd();
#endif
}
bool 	Enemy::collideWith(Actor *anActor) {return false;}

void Enemy::circle(){}
void Enemy::diamond(){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = location_y;
	if( x < 0)
		x *=-1;
	if( y < 0)
		y *=-1;
	if( sX < 0)
		sX *=-1;
	if( sY < 0)
		sY *=-1;
		if(sX+1 > x && sY+1 > y && !spot){
			location_x+= 0.1f;
			location_y+= 0.1f;
		}
		else if(sX+2 > x && y > sY && !spot){
			location_x+= 0.1f;
			location_y-= 0.1f;
			if(x-sX == sX+1.9)
				spot = true;
		}
		else if(x > sX+1 && y > sY-1 && spot){
			location_x-= 0.1f;
			location_y-= 0.1f;
		}else if(x>sX && y < sY && spot){
			location_x-=0.1f;
			location_y+=0.1f;
			if(x - sX == .1)
				spot = false;
		}
		/*if(x-sX < 4 && spot){
			location_x+= 0.1f;
			location_y-= 0.1f;
			if(x-sX == 3.9)
				spot = false;
		}else if(spot){
			location_x-= 0.1f;
			location_y+= 0.1f;
			if(x-sX == 2.1)
				spot = false;
		}*/
}
void Enemy::diagonal(){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = location_y;
	if(!spot){
		if(x-sX < 2){
			location_x+= 0.1f;
			location_y+= 0.1f;
		}
		else
			spot = true;
	}
	if(spot){
		if(x-sX > 0){
			location_x-=0.1f;
			location_y-=0.1f;
		}else
			spot = false;
	}
}
void Enemy::square(){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = location_y;
	if(!spot){
		if(y-sX < 2){
			location_x+= 0.1f;
		}
		/*else if(y-sY< 2){
			location_y+=0.1f;
			printf("y: %f\n", location_y);*/
		else
			spot = true;
	}
	if(spot){
		if(x-sX > 0){
			location_x-=0.1f;
		}
		/*else if(y-sY > 0)
			location_y-=0.1f;*/
		else
			spot = false;
	}
}
