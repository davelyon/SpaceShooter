#include "Actor.h"

Actor::Actor() {}
Actor::~Actor() {}

void Actor::update() 	{ return; }	// This should be overwritten
void Actor::draw() 		{ return; }	// This should be overwritten

void Actor::takeDamage() {return;}

bool Actor::collideWith(Actor *anActor) {
	// This should be overwritten by anything that can actually collide
	return false;
}

int Actor::points()			{ return pointValue; 	}
int Actor::belongsTo() 	{ return owner;				}
float Actor::getX()				{ return 0;}
float Actor::getY()				{ return 0;}
bool Actor::living()		{	return isLiving;}
