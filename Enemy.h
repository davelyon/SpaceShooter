#ifndef TheEnemy
#define TheEnemy
#include "Actor.h"
#include <string>
class Enemy : Actor
{
public:
	Enemy(int uniqueID, int x, int y, int health, int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update();
	void 	draw();
	bool 	collideWith(Actor *anActor);
	std::string toString();
private:
	int health;
	float location_x;
	float location_y;	
};

#endif
