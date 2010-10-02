#ifndef TheShip
#define TheShip
class player {
	int xPosition;
	int yPosition;
	int image;
	int score;
		
	player(){score = 0;}
	void startPlayer();
	void issueCommand(/*needs a key event*/);
};
#endif
	
