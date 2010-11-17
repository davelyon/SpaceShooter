#include "Actor.h"

#define OWNER_P1 1
#define OWNER_P2 2
#define OWNER_GAME 3

#define MOVE_NONE		0
#define MOVE_RIGHT	1
#define MOVE_LEFT		2
#define MOVE_UP			3
#define MOVE_DOWN		4

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
};

class Enemy : Actor
{
	Enemy(int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update();
	void 	draw();
	bool 	collideWith(Actor *anActor);

};