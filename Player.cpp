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
	this->shotTexture = load_texture(PARTICLE);
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
		lasers[i].accum_rotation += ((float)ticks/1000.0f) * 2.0f;
	}
	
	if(location_x > 2.4f) {
		location_x = 2.4f;
	}
	
	if(location_x < -2.4f) {
		location_x = -2.4f;
	}
	
	if(location_y > 2.9f) {
		location_y = 2.9f;
	}
	
	if(location_y < -2.9f) {
		location_y = -2.9f;
	}
	
}
void 	Player::draw() {
	glLoadIdentity();
	glTranslatef(location_x,location_y,-8.0f);
	glScalef(0.5f, 0.5f, 1.0f);
	
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	glBindTexture(GL_TEXTURE_2D, this->texture);
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
	glEnd();
	glFlush();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	

	
	glBindTexture(GL_TEXTURE_2D, this->shotTexture);
	glColor4f(0.0f, 0.7f, 0.0f, 0.8f);
	//
	for (int i = 0; i < numLasers; i++) {
				
		float x = lasers[i].x;
		float y = lasers[i].y;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(x,y, -8.0f);	
		glScalef(0.2f, 0.2f, 0.2f);
		glRotatef(lasers[i].accum_rotation, 1.0f, 0.0f, 0.0f);
		glRotatef(lasers[i].accum_rotation, 0.0f, 1.0f, 0.0f);
		glRotatef(lasers[i].accum_rotation, 0.0f, 0.0f, 0.6f);
		glBegin(GL_QUADS);
		
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  -1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f,  -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f,  -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  -1.0f);	// Top Left Of The Texture and Quad
			// Back Face
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
			// Top Face
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
			// Bottom Face
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			// Right face
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left Of The Texture and Quad
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Bottom Left Of The Texture and Quad
			// Left Face
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Top Left Of The Texture and Quad
		glEnd();
	}
	
	
}
bool 	Player::collideWith(Actor *anActor) {return false;}
int 	Player::points() 		{ return 0;}

void Player::shoot(int ticks) {
	if (numLasers == MAX_LASERS) numLasers = 0;
	printf("Shot from...(%f,%f)", location_x, location_y);
	
	lasers[numLasers].x = this->location_x;
	lasers[numLasers].y = this->location_y;
	
	++numLasers;
}
float Player::getX(){
	return location_x;
}
float Player::getY(){
	return location_y;
}
