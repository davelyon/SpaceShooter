#include "Player.h"


Player::Player(int playerNumber) {
	this->pointValue = 0;
	this->owner = playerNumber;
	
	this->isLiving = true;
	this->health = 50;
	
	this->location_x = 0.0f;
	this->location_y = 0.0f;
	
	this->texture[0] = load_texture("/Users/dave/Code/SpaceRedux/ship.bmp");
	
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
	glBindTexture(GL_TEXTURE_2D, this->texture[0]);
	
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
		glBindTexture(GL_TEXTURE_2D, this->texture[0]);
			
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
		glEnd();
		
	}
	
	
}
bool 	Player::collideWith(Actor *anActor) {return false;}
int 	Player::points() 		{ return 0;}

void Player::shoot(int ticks) {
	if (numLasers == MAX_LASERS) numLasers = 0;
	
	lasers[numLasers].x = this->location_x - 0.45f;
	lasers[numLasers].y = this->location_y + 0.75f;
	
	++numLasers;
}

