#ifndef TheEnemy
#define TheEnemy
#include "../Actor.h"
#include <string>
using namespace std;
class Enemy : Actor
{
public:
	Enemy();
	Enemy(int uniqueID, float xI, float yI, int health, int pointValue);
	virtual ~Enemy();
	
	// Actions
	void 	update(int uID, float xI, float y, int health, int pointValue);
	void update(int tick);
	void 	draw();
	bool 	collideWith(Actor *anActor);
	string toString();
private:
	int uniqueID;
	int myHealth;
	int movementPattern;
	float start_x_loc;
	float start_y_loc;
	float location_x;
	float location_y;	
	bool spot;
	void square(float movement);
	void circle(float movement);
	void diagonal(float movement);
	void diamond(float movement);
	void sideways(float movement);
	void vertical(float movement);

};

#endif
