#ifndef TheEnemy
#define TheEnemy
#include "Actor.h"

class Enemy : Actor
{
public:
	Enemy(int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update();
	void 	draw();
	bool 	collideWith(Actor *anActor);
private:
	int health;
	float location_x;
	float location_y;	
};

#endif