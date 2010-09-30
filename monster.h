#ifndef Killers
#define Killers
class monster {
	int xPosition;
	int yPosition;
	int image;
	int value;
	GameBoard *currentBoard;
	
	monster();
	setupMonster();
	placeMonster();
	followRules();
};
#endif
	
