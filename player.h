#ifndef TheShip
#define TheShip
class player {
	int xPosition;
	int yPosition;
	int image;
	int score;
		
	player();
	//void initializePlayer();
	void issueCommand(/*needs a key event*/);
	void drawPlayer();
};
#endif
	
