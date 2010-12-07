#include "Enemy.h"
#include <iostream>
#include <ctime>


Enemy::Enemy(){

	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
	
	this->isLiving = true;
	this->location_x = 0.0f;
	this->start_x_loc = this->location_x;
	this->location_y = 0.0f;
	this->start_y_loc = this->location_y;
	this->texture = 0;
	uniqueID = 0;
	myHealth = 0;
	movementPattern = (rand()%5)+1;
	spot = false;
}

Enemy::Enemy(int uID, float xI, float yI, int health, int pointValue) {
	this->pointValue = pointValue;
	this->owner = OWNER_GAME;
		
	this->isLiving = true;
	this->location_x = xI ;
	this->start_x_loc = this->location_x;
	this->location_y = yI ;
	this->start_y_loc = this->location_y;
	this->texture = 0;
	uniqueID = uID;
	myHealth = health;
	movementPattern = (rand()%5)+1;
	
	spot = false;
}

Enemy::~Enemy() {
	
}
string Enemy::toString(){
	string output = "";
	char * a = new char[50];
	sprintf(a, "%d %f %f %d %d\0", uniqueID, this->location_x, this->location_y, myHealth, this->pointValue);
	output = a;
	delete[] a;
	return output;

}
void 	Enemy::update(int uID, float xI, float yI, int health, int pointValue) {
	if(xI < -2.0f)
		xI = -2.0f;
	if(xI > 2.0f)
		xI = 2.0f;
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
//	square(movement);
}
void 	Enemy::draw() 	{
}
bool 	Enemy::collideWith(Actor *anActor) {return false;}

void Enemy::circle(float movement){}
void Enemy::diamond(float movement){
	float x = location_x;
	float sX = start_x_loc;
	float y = location_y;
	float sY = start_y_loc;
	if(!spot){
		if(x-sX < 1 && y-sY < 1){
			location_x+= movement;
			location_y+= movement;
		}
		else if(x-sX < 2 && y-sY > 0){
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
