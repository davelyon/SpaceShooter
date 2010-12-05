#ifndef TheTextures
#define TheTextures
#ifdef MAC_OSX_BUILD_MODE
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include "SDL_image.h"
#else // Linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL/SDL_image.h"
#endif


#ifdef MAC_OSX_BUILD_MODE
#define PLAYER1 "/Users/dave/Code/SpaceRedux/ship3.bmp"
#define PLAYER2 "/Users/dave/Code/SpaceRedux/ship3.bmp"
#define PARTICLE "/Users/dave/Code/SpaceRedux/particle.bmp"
#else
#define PLAYER1 "/home/msherman/videoGames/hold/SpaceShooter/ship3.png"
#define PLAYER2 "/home/msherman/videoGames/hold/SpaceShooter/ship3.png"
#define PARTICLE "/home/msherman/videoGames/hold/SpaceShooter/particle.bmp"
#endif

GLuint load_texture(const char* file);
#endif
