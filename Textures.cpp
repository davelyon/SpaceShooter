#include "Textures.h"
#ifdef MAC_OSX_BUILD_MODE
#include "MacBundle.h"
#endif

int nextpoweroftwo(int x)
{
	double logbase2 = log(x) / log(2);
	return round(pow(2,ceil(logbase2)));
}

static GLuint shipTexture = -1;
GLuint ship_texture() {
	if(shipTexture == -1) {
#ifdef MAC_OSX_BUILD_MODE
		shipTexture = load_texture(absoluteBundleResourcePath(PLAYER1));
#else
		shipTexture = load_texture(PLAYER1);
#endif
	}
	return shipTexture;
}

static GLuint enemyTexture = -4;
GLuint enem_texture() {
	if(enemyTexture == -4) {
#ifdef MAC_OSX_BUILD_MODE
		enemyTexture = load_texture(absoluteBundleResourcePath(ENEMY));
#else
		enemyTexture = load_texture(ENEMY);
#endif
	}
	return enemyTexture;
}

static GLuint shipTexture2 = -3;
GLuint ship_texture2() {
	if(shipTexture2 == -1) {
#ifdef MAC_OSX_BUILD_MODE
		shipTexture2 = load_texture(absoluteBundleResourcePath(PLAYER2));
#else
		shipTexture2 = load_texture(PLAYER2);
#endif
	}
	return shipTexture;
}


static GLuint partTexture = -2;
GLuint part_texture() {
	if(partTexture == -2) {
#ifdef MAC_OSX_BUILD_MODE
		partTexture = load_texture(absoluteBundleResourcePath(PARTICLE));
#else
		partTexture = load_texture(PARTICLE);
#endif
	}
	return partTexture;
}


GLuint load_texture(const char* file)
{
	
	SDL_Surface* surface;	GLuint texture;	
	
	
	/* Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit */
	if ( ( surface = SDL_LoadBMP( file ) ) )
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
	SDL_FreeSurface(surface);

	return texture;
}

void SDL_GL_RenderText(char *text, 
											 TTF_Font *font,
											 SDL_Color color,
											 SDL_Rect *location)
{
	
	int vPort[4];
	
	glPushMatrix();
	
	glGetIntegerv(GL_VIEWPORT, vPort);
  
	glMatrixMode(GL_PROJECTION);
	
	glPushMatrix();
	glLoadIdentity();
  
	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	
	SDL_Surface *initial;
	SDL_Surface *intermediary;

	int w,h;
	GLuint texture;
	
	/* Use SDL_TTF to render our text */
	initial = TTF_RenderText_Solid(font, text, color);
	
	/* Convert the rendered text to a known format */
	w = nextpoweroftwo(initial->w);
	h = nextpoweroftwo(initial->h);
	
	intermediary = SDL_CreateRGBSurface(0, w, h, 32, 
																			0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	
	SDL_BlitSurface(initial, 0, intermediary, 0);
	/* Tell GL about our new texture */
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_BGRA, 
							 GL_UNSIGNED_BYTE, intermediary->pixels );
	
	/* GL_NEAREST looks horrible, if scaled... */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	/* prepare to render our texture */
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	/* Draw a quad at location */
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	/* Recall that the origin is in the lower-left corner
	 That is why the TexCoords specify different corners
	 than the Vertex coors seem to. */
	glTexCoord2f(0.0f, 1.0f); 
	glVertex2f(location->x, location->y);
	glTexCoord2f(1.0f, 1.0f); 
	glVertex2f(location->x + w, location->y);
	glTexCoord2f(1.0f, 0.0f); 
	glVertex2f(location->x + w, location->y + h);
	glTexCoord2f(0.0f, 0.0f); 
	glVertex2f(location->x    , location->y + h);
	glEnd();
	
	/* Bad things happen if we delete the texture before it finishes */
	glFinish();
	
	/* return the deltas in the unused w,h part of the rect */
	location->w = initial->w;
	location->h = initial->h;
	
	/* Clean up */
	SDL_FreeSurface(initial);
	SDL_FreeSurface(intermediary);
	glDeleteTextures(1, &texture);
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
}
