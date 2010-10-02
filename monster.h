#ifndef Killers
#define Killers
class monster {
	int xPosition;
	int yPosition;
	int image;
	int value;
	
	monster();
	void setupMonster();
	void placeMonster();
	void followRules();
};
#endif
	
