#ifndef TheEnemy
#define TheEnemy
#include "Actor.h"
#include <string>

#ifndef SERVER_COMPILE_FLAG
#include "Textures.h"
#endif

class Enemy : Actor
{
public:
	Enemy();
	Enemy(int uniqueID, float xI, float yI, int health, int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update(int uID, float xI, float y, int health, int pointValue);
	void update();
	void 	draw();
	bool 	collideWith(Actor *anActor);
	void toString(char * output);
private:
	int uniqueID;
	int myHealth;
	float location_x;
	float location_y;	
#ifndef SERVER_COMPILE_FLAG
	GLuint texture;
#endif
};

#endif
