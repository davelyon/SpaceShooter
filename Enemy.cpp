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
	movementPattern = (rand()%5)+1;

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
	movementPattern = (rand()%5)+1;
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
void Enemy::update(int ticks){
float movement = ((float)ticks/1000.0f)*2.00f;
	switch(movementPattern){
		case 1:
			square(movement);
			break;
		case 2:
			vertical(movement);
			break;
		case 3:
			sideways(movement);
			break;
		case 4:
			diamond(movement);
			break;
		case 5:
			diagonal(movement);
			break;
		default:
			sideways(movement);
			break;

	}
} void 	Enemy::draw() 	{
#ifndef SERVER_COMPILE_FLAG
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(location_x,location_y, -48.0f);
	//glRotatef(0.0f, 0.0f, 0.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_SRC_ALPHA);
	
	//glScalef(0.5f, 0.5f, 1.0f);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
	glEnd();
#endif
}
bool 	Enemy::collideWith(Actor *anActor) {return false;}

void Enemy::circle(float movement){}
void Enemy::diamond(float movement){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = start_y_loc;
	if(!spot){
		if(x-sX < 2 && y-sY < 2){
			location_x+= movement;
			location_y+= movement;
		}
		else if(x-sX < 4 && y-sY > 0){
			location_x+= movement;
			location_y-= movement;
		}else
			spot = true;
	}
	if(spot){
		if(x-sX > 2 && y-sY > -2){
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
		if(x-sX < 2){
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
		if(x-sX < 2){
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
		if(x-sX < 2){
			location_x+=movement;
		}
		else if(y-sY< 2){
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
