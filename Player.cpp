#include "Player.h"
#include "Textures.h"


Player::Player(int playerNumber) {
	
	this->pointValue = 0;
	this->owner = playerNumber;
	

	this->health = 1;
	
	this->location_x = 0.0f;
	this->location_y = -2.0f;
	
	this->texture = ship_texture();
	this->texture2 = ship_texture2();
	this->shotTexture = part_texture();
	this->numLasers = 0;
	
	this->isMoving = false;
	this->isLiving = true;
	
	otherPlayer.x = 0;
	otherPlayer.y = 0;
	otherPlayer.score = 0;
	
	for (int i = 0; i < MAX_LASERS; i++) {

		lasers[i].living = false;
		lasers[i].y = 0.0f;
		lasers[i].y = 0.0f;
		lasers[i].accum_rotation = 0.0f;
	}
	
}

Player::~Player() {}

void Player::takeDamage() {
	health -= 1;
	if(health <= 0) {
		isLiving = false;
	}
}

void 	Player::update(int ticks, int movedir) {
		
	for (int i = 0; i < MAX_LASERS; i++) {
		if(lasers[i].y >= 3.0f) {
			lasers[i].living = false;
			continue;
		}
		lasers[i].y += ((float)ticks/1000.0f) * 2.66f;
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
	
	if(isMoving || !isLiving) {
		return;
	}
	
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
	
	
}

void Player::holdPosition(bool should){
	isMoving = should;
}	

void 	Player::draw(bool two) {
	bool firstDraw = true;
	if(!isLiving) {
		firstDraw = false;
	}
	glPushMatrix();
	while(true){
		glPushMatrix();
		if(firstDraw)
			glTranslatef(location_x,location_y,-8.0f);
		else if(two && otherPlayer.x != -10.0)
			glTranslatef(otherPlayer.x, otherPlayer.y, -8.0f);
		glScalef(0.5f, 0.5f, 1.0f);
		
		if (two && !firstDraw) {
			glBindTexture(GL_TEXTURE_2D, this->texture2);
		}else {
			glBindTexture(GL_TEXTURE_2D, this->texture);
		}
		glRotatef(180.0f, 180.0f, 0.0f, 1.0f);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);	
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  0.0f);	
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  0.0f);	
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  0.0f);	
		glEnd();
		if(firstDraw)
			firstDraw = false;
		else
			break;
		glPopMatrix();
	}
	glFinish();
	glPopMatrix();
	if(!isLiving) return;
	glPushMatrix();
	
	glBindTexture(GL_TEXTURE_2D, this->shotTexture);
	glColor4f(0.0f, 0.7f, 0.2f, 0.8f);

	for (int i = 0; i < MAX_LASERS; i++) {
		if ( !lasers[i].living) continue;
		
		float x = lasers[i].x;
		float y = lasers[i].y;
		glPushMatrix();

		glTranslatef(x,y, -8.0f);	
		glRotatef(lasers[i].accum_rotation, 0.0f, 2.0f, 0.0f);
		glScalef(0.1f, 0.2f, 0.1f);
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
		glPopMatrix();
		lasers[i].accum_rotation += (float)( rand() % 4);
	}
	glFinish();
	glPopMatrix();
}
bool 	Player::collideWith(Actor *anActor) {
	
	bool shouldReturn = false;
	for (int i = 0; i < numLasers; i++) {
		float x = anActor->getX();
		float y = anActor->getY();
		if( lasers[i].living ) {
			if (	x > (lasers[i].x - 0.2f) && 
						x < (lasers[i].x + 0.2f) && 
						y <= (lasers[i].y + 0.2f)&&
						y >= (lasers[i].y - 0.2f)
					){
				shouldReturn = true;
				lasers[i].living = false;
				pointValue += 75;
			} 
		}
	}
	
	return shouldReturn;
}
int 	Player::points() 		{ return pointValue;}

void Player::shoot(int ticks) {
	if (numLasers == MAX_LASERS) numLasers = 0;
	lasers[numLasers].x = this->location_x;
	lasers[numLasers].y = this->location_y;
	lasers[numLasers].living = true;
	lasers[numLasers].accum_rotation = 0.0f;
	++numLasers;
}
float Player::getX(){
	return location_x;
}
float Player::getY(){
	return location_y;
}
void Player::setX(float x){
	this->location_x = x;
}
void Player::setY(float y){
	this->location_y = y;
}
