#ifndef TheTextures
#define TheTextures
#ifdef MAC_OSX_BUILD_MODE
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <math.h>
#else // Linux includes
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL_image.h"
#include <math.h>
#endif


#ifdef MAC_OSX_BUILD_MODE
#define PLAYER1 "/Users/dave/Code/SpaceRedux/ship3s.bmp"
#define PLAYER2 "/Users/dave/Code/SpaceRedux/ship3s.bmp"
#define PARTICLE "/Users/dave/Code/SpaceRedux/particle.bmp"
#else
#define PLAYER1 "./ship3s.bmp"
#define PLAYER2 "./ship3s.bmp"
#define PARTICLE "./particle.bmp"
#endif

GLuint ship_texture();
GLuint part_texture();
GLuint load_texture(const char* file);
void SDL_GL_RenderText(char *text, 
											 TTF_Font *font,
											 SDL_Color color,
											 SDL_Rect *location);
int nextpoweroftwo(int x);


#endif
