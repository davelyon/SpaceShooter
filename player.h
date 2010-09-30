#ifndef TheShip
#define TheShip
class player {
	int xPosition;
	int yPosition;
	int image;
	int score;
	GameBoard *currentBoard;
	
	player(){score = 0;}
	startPlayer();
	issueCommand(/*needs a key event*/);
};
#endif
	
