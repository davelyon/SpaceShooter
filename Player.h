#ifndef TheActualPlayer
#define TheActualPlayer
#include "Actor.h"


#define MAX_LASERS 30

struct laser_shot {
	float x;
	float y;
};

class Player : Actor 
{
public:
	Player(int playerNumber);
	~Player();
	
	// Actions
	void 	update(int ticks, int movdir);
	void 	draw();
	void	shoot(int ticks);
	bool 	collideWith(Actor *anActor);
	int 	points();
	
	
private:
	int health;
	float location_x;
	float location_y;
	GLuint texture;

	int numLasers;
	struct laser_shot lasers[MAX_LASERS];
	int last_move;
};

#endif
