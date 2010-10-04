#ifndef TheShip
#define TheShip
#include <SDL/SDL.h>
#include "particle.h"
class player {
	float xPosition;
	float yPosition;
	int image;
	int score;
	public:	
	player(float x, float y, int score, int pic);
	void issueCommand(SDL_keysym *keysym, particle *shots, int startShot, int endShot);
	void draw();
	void updateScore(int add);
};
#endif
	
