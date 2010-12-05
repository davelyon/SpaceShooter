#ifndef TheActualPlayer
#define TheActualPlayer
#include "Actor.h"
#define MAX_LASERS 30

struct laser_shot {
	float x;
	float y;
	float accum_rotation;
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
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	
	void holdPosition(bool should);
	
	
private:
	int health;
	float location_x;
	float location_y;
	GLuint texture;
	GLuint shotTexture;

	int numLasers;
	struct laser_shot lasers[MAX_LASERS];
	int last_move;
	
	bool isMoving;
};

#endif
