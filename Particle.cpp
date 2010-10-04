#include "Particle.h"
#include "Player.h"

Particle::Particle(){
	x = 0;
	y = 0;
	image = 0;
}

void Particle::updateShot(float startX, float startY, int image, Player *ship){
	x = startX;
	y = startY;
	image = image;
	this->collision(ship);
}

void Particle::draw(){
	glColor3f(   0.0f,  0.0f,  0.0f );
	/* left shot */
	glLoadIdentity();
	glTranslatef(x, y, -8.0f); 
    gluSphere(quadratic,0.02f,32,32);
    
    /* right shot */
    glLoadIdentity();
    glTranslatef(x-0.2, y, -8.0f); 
    gluSphere(quadratic,0.02f,32,32);
}
float Particle::getX(){
	return x;
}
float Particle::getY(){
	return y;
}
void Particle::collision(Player *ship){
	if(true)
		ship->updateScore(10);
}
