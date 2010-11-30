#ifndef TheActualPlayer
#define TheActualPlayer
#include "Actor.h"

class Player : Actor 
{
public:
	Player(int playerNumber);
	~Player();
	
	// Actions
	void 	update(int ticks, int movdir);
	void 	draw();
	bool 	collideWith(Actor *anActor);
	int 	points();
	
private:
	int health;
	float location_x;
	float location_y;
	GLint texture[1];
};

#endif
