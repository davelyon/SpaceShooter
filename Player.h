#ifndef TheActualPlayer
#define TheActualPlayer
#define MAX_LASERS 60

#include "Actor.h"
#include "Enemy.h"


struct laser_shot {
	float x;
	float y;
	float accum_rotation;
	float living;
};
struct SecondPlayer{
	float x;
	float y;
	int score;
};

class Player : Actor 
{
public:
	Player(int playerNumber);
	~Player();
	
	// Actions
	void 	update(int ticks, int movdir);
	void 	draw(bool two);
	void	shoot(int ticks);
	bool 	collideWith(Actor *anActor);
	int 	points();
	float getX();
	float getY();
	void takeDamage();
	void setX(float x);
	void setY(float y);
	inline bool living() {return isLiving;};
	void holdPosition(bool should);
	SecondPlayer otherPlayer;
	
	
private:
	int health;
	float location_x;
	float location_y;
	GLuint texture;
	GLuint texture2;
	GLuint shotTexture;

	int numLasers;
	struct laser_shot lasers[MAX_LASERS];
	int last_move;
	
	bool isMoving;
};

#endif
