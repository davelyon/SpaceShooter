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
#define PLAYER1 "/Users/dave/Code/SpaceRedux/ship2.png"
#define PLAYER2 "/Users/dave/Code/SpaceRedux/ship2.png"
#define PARTICLE "/Users/dave/Code/SpaceRedux/particle.bmp"
#else
#define PLAYER1 "/home/msherman/videoGames/hold/SpaceShooter/ship.png"
#define PLAYER2 "/home/msherman/videoGames/hold/SpaceShooter/ship.png"
#define PARTICLE "/home/msherman/videoGames/hold/SpaceShooter/particle.bmp"
#endif

GLuint load_texture(const char* file);
#endif
