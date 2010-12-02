#ifndef TheEnemy
#define TheEnemy
#include "Actor.h"
#include <string>
#include "Textures.h"
class Enemy : Actor
{
public:
	Enemy();
	Enemy(int uniqueID, int x, int y, int health, int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update(int uID, int x, int y, int health, int pointValue);
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
