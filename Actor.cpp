#include "actor.h"

Actor::Actor() {}
Actor::~Actor() {}

void Actor::update() 	{ return; }	// This should be overwritten
void Actor::draw() 		{ return; }	// This should be overwritten

bool Actor::collideWith(Actor *anActor) {
	// This should be overwritten by anything that can actually collide
	return false;
}

int Actor::points()			{ return pointValue; 	}
int Actor::belongsTo() 	{ return owner;				}
bool Actor::living()		{	return isLiving;			}

