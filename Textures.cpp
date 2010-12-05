#include "Textures.h"

GLuint load_texture(const char* file)
{
//	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
//	int initted=IMG_Init(flags);
//	if(initted&flags != flags) {
//    printf("IMG_Init: Failed to init required jpg and png support!\n");
//    printf("IMG_Init: %s\n", IMG_GetError());
//    // handle error
//	}
//	
	SDL_Surface* surface;// = IMG_Load(file);
//	if(!surface) {
//    printf("IMG_Load: %s %s\n", file,IMG_GetError());
//    // handle error
//	}
	GLuint texture;
//	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
//	glGenTextures(1, &texture);
//	glBindTexture(GL_TEXTURE_2D, texture);
//	glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
//	//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
//	
//	SDL_FreeSurface(surface);
//	return texture;
	
	
	
	/* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
	if ( ( surface = SDL_LoadBMP( "data/particle.bmp" ) ) )
	{
		/* Create The Texture */
		glGenTextures( 1, &texture );
		
		/* Typical Texture Generation Using Data From The Bitmap */
		glBindTexture( GL_TEXTURE_2D, texture );
		
		/* Generate The Texture */
		glTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w,
								 surface->h, 0, GL_BGR,
								 GL_UNSIGNED_BYTE, surface->pixels );
		
		/* Linear Filtering */
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	}
	
	return texture;
}
