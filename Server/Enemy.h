#ifndef TheEnemy
#define TheEnemy
#include "../Actor.h"
#include <string>


class Enemy : Actor
{
public:
	Enemy();
	Enemy(int uniqueID, float x, float y, int health, int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update(int uID, float x, float y, int health, int pointValue);
	void update();
	void 	draw();
	bool 	collideWith(Actor *anActor);
	void toString(char * output);
private:
	int uniqueID;
	int myHealth;
	float location_x;
	float location_y;	
	GLuint texture;
};

#endif
