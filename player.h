#ifndef TheShip
#define TheShip
class player {
	float xPosition;
	float yPosition;
	int image;
	int score;
	public:	
	player(float x, float y, int score, int pic);
	//void initializePlayer();
	void issueCommand(/*needs a key event*/);
	void drawPlayer();
};
#endif
	
