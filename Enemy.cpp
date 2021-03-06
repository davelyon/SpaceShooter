#include "Enemy.h"
#include <iostream>
#include <ctime>

using namespace std;
Enemy::Enemy(){

	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = 0.0f;
	this->start_x_loc = this->location_x;
	this->location_y = 0.0f;
	this->start_y_loc = this->location_y;
#ifndef SERVER_COMPILE_FLAG
	this->texture = enem_texture();
#endif	
	uniqueID = 0;
	myHealth = 1;
	movementPattern = (rand()%4)+1;
	spot = false;
}

Enemy::Enemy(int uID, float xI, float yI, int health, int pointValue) {
	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	if(xI < -2.0f)
		xI = -2.0f;
	if(xI > 2.0f)
		xI = 2.0f;
	
	
	this->isLiving = true;
	this->location_x = xI ;
	this->start_x_loc = this->location_x;
	this->location_y = yI ;
	this->start_y_loc = this->location_y;
#ifndef SERVER_COMPILE_FLAG
	this->texture = enem_texture();
#endif
	uniqueID = uID;
	myHealth = 1;
	movementPattern = (rand()%4)+1;
	
	spot = false;
}

Enemy::~Enemy() {
	
}
string Enemy::toString(){
	string output = "";
	char * a;
	sprintf(a, "%d %f %f %d %d", uniqueID, this->location_x, this->location_y, myHealth, this->pointValue);
	output = a;
	delete[] a;
	return output;
}
void 	Enemy::update(int uID, float xI, float yI, int health, int pointValue) {
	if(xI < -2.0f)
		xI = -2.0f;
	else if(xI > 2.0f)
		xI = 2.0f;
	else
		this->location_x = xI;
	this->start_x_loc = this->location_x;
	this->location_y = yI;
	this->start_y_loc = this->location_y;
	uniqueID = uID;
	//myHealth = health +1;
	this->pointValue = pointValue;
}
void Enemy::update(int ticks){
float movement = ((float)ticks/1000.0f);
float screenMove = ((float)ticks/1000.0f) * -.5f;
	location_y += screenMove;
	start_y_loc += screenMove;
	switch(movementPattern){
		case 1:
			square(movement);
			break;
		case 2:
			diagonal(movement);
			break;
		case 3:
			sideways(movement);
			break;
		case 4:
			diamond(movement);
			break;
		default:
			sideways(movement);
			break;

	}
}
void 	Enemy::draw() 	{
#ifndef SERVER_COMPILE_FLAG
	if (this->myHealth <= 0) {
		return;
	}
	
	if(location_y > 2.9f)
		return;	
	if(location_y < -2.9f)
		return;
	

	glPushMatrix();
	glTranslatef(location_x,location_y, -8.0f);
	glScalef(0.2f, 0.2f, 1.0f);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, this->texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
	glEnd();
	glFinish();
	
	glPopMatrix();

#endif
}
bool Enemy::collideWith(Actor *anActor) {
	
	if (myHealth <= 0) {
		return false;
	}
	
	float x = anActor->getX();
	float y = anActor->getY();
	
	bool killedByPlayer = anActor->collideWith(this);;
	
	if (killedByPlayer) {
		// ADD TO SCORE
		this->myHealth = 0;
		return true;
	}
	
	if ( x < (location_x - 0.35f) || x > (location_x + 0.35f)){
		return false;
	}else if ( y < (location_y - 0.7f) || y > (location_y + 0.7f)){
		return false;
	}
	
	anActor->takeDamage();
	
	this->myHealth = 0;
	return true;

}

void Enemy::circle(float movement){}
void Enemy::diamond(float movement){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = start_y_loc;
	if(!spot){
		if(x-sX < .5 && y-sY < .5){
			location_x+= movement;
			location_y+= movement;
		}
		else if(x-sX < 1 && y-sY > 0){
			location_x+= movement;
			location_y-= movement;
		}else
			spot = true;
	}
	if(spot){
		if(x-sX > .5 && y-sY > -.5){
			location_x -= movement;
			location_y -= movement;
		}
		else if( x > sX && y < sY){
			location_x -= movement;
			location_y += movement;
			if(x-0.1 == sX)
				spot = false;
		}
		else
			spot = false;
	}
}
void Enemy::vertical(float movement){
	float y = location_y;
	float sY = start_y_loc;
	if(!spot){
		if(y-sY < 2){
			location_y+= movement;
		}
		else
			spot = true;
	}
	if(spot){
		if(y-sY > 0){
			location_y-= movement;
		}else
			spot = false;
	}
}
void Enemy::sideways(float movement){
	float x = location_x;
	float sX = start_x_loc;
	if(!spot){
		if(x-sX < 1){
			location_x+= movement;
		}
		else
			spot = true;
	}
	if(spot){
		if(x-sX > 0){
			location_x-=movement;
		}else
			spot = false;
	}
}
void Enemy::diagonal(float movement){
	float x = location_x;
	float sX = start_x_loc;
	if(!spot){
		if(x-sX < 1){
			location_x+=movement;
			location_y+=movement;
		}
		else
			spot = true;
	}
	if(spot){
		if(x-sX > 0){
			location_x-=movement;
			location_y-=movement;
		}else
			spot = false;
	}
}
void Enemy::square(float movement){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = start_y_loc;
	if(!spot){
		if(x-sX < 1){
			location_x+=movement;
		}
		else if(y-sY< 1){
			location_y+=movement;
		}else
			spot = true;
	}
	if(spot){
		if(x-sX > 0){
			location_x-=movement;
		}
		else if(y-sY > 0)
			location_y-=movement;
		else
			spot = false;
	}
}

float Enemy::getX() { return location_x; } 
float Enemy::getY() { return location_y; } 
