#include "Player.h"
#include "Textures.h"


Player::Player(int playerNumber) {
	
	//generateTextures();
	
	this->pointValue = 0;
	this->owner = playerNumber;
	
	this->isLiving = true;
	this->health = 50;
	
	this->location_x = 0.0f;
	this->location_y = 0.0f;
	
	this->texture = load_texture(PLAYER1);
	
	this->numLasers = 0;
}

Player::~Player() {}

void 	Player::update(int ticks, int movedir) {
	
	float movPixels = ((float)ticks/1000.0f) * 2.00f;
		
	if(movedir == MOVE_NONE)
		movedir = last_move;
	else 
		last_move = movedir;
	
	switch (movedir) {
		case MOVE_RIGHT:
			location_x += movPixels;
			break;
		case MOVE_LEFT:
			location_x -= movPixels;
			break;
		case MOVE_UP:
			location_y += movPixels;
			break;
		case MOVE_DOWN:
			location_y -= movPixels;
			break;
		default:
			break;
	}
	
	for (int i = 0; i < numLasers; i++) {
		lasers[i].y += ((float)ticks/1000.0f) * 4.66f;
	}
}
void 	Player::draw() { 	
	glLoadIdentity();
	glTranslatef(location_x,location_y, -24.0f);
	glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_ONE, GL_SRC_ALPHA);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
	glEnd();
	
	// end player drawing 

	// start laser drawing
	
	for (int i = 0; i < numLasers; i++) {
		glLoadIdentity();
		glTranslatef(lasers[i].x,lasers[i].y, -48.0f);
		glRotatef(135.0f, 0.0f, 0.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_ONE, GL_SRC_ALPHA);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
		glEnd();
		
	}
	
	glEnable(GL_DEPTH_TEST);
	
}
bool 	Player::collideWith(Actor *anActor) {return false;}
int 	Player::points() 		{ return 0;}

void Player::shoot(int ticks) {
	if (numLasers == MAX_LASERS) numLasers = 0;
	
	lasers[numLasers].x = this->location_x - 0.45f;
	lasers[numLasers].y = this->location_y + 0.75f;
	
	++numLasers;
}
float Player::getX(){
	return location_x;
}
float Player::getY(){
	return location_y;
}
