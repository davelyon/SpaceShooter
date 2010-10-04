#ifndef Killers
#define Killers
class Monster {
	int xPosition;
	int yPosition;
	int image;
	int value;
	
	Monster();
	void setupMonster();
	void placeMonster();
	void followRules();
};
#endif
	
