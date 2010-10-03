#ifndef TheShots
#define TheShots
class particle{
	float x, y;
	int image;
public:
	particle();
	void updateShot(float startX, float startY, int image);
	void draw();
};

#endif
