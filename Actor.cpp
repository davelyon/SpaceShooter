#include "Actor.h"



Actor::Actor() {}
Actor::~Actor() {}

void Actor::update() 	{ return; }	// This should be overwritten
void Actor::draw() 		{ return; }	// This should be overwritten

bool Actor::collideWith(Actor *anActor) {
	// This should be overwritten by anything that can actually collide
	return false;
}

int Actor::points()			{ return pointValue; 	}
int Actor::belongsTo() 	{ return owner;				}
bool Actor::living()		{	return isLiving;			}


GLuint load_texture(const char* file)
{
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted=IMG_Init(flags);
	if(initted&flags != flags) {
    printf("IMG_Init: Failed to init required jpg and png support!\n");
    printf("IMG_Init: %s\n", IMG_GetError());
    // handle error
	}
	
	SDL_Surface* surface = IMG_Load(file);
	if(!surface) {
    printf("IMG_Load: %s\n", IMG_GetError());
    // handle error
	}
	GLuint texture;
	//glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	
	SDL_FreeSurface(surface);
	return texture;
}
