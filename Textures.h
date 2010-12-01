#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
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


#define PLAYER1 "/Users/dave/Code/SpaceRedux/ship.png"
#define PLAYER2 "/Users/dave/Code/SpaceRedux/ship.png"

static GLuint localShipTexture = -1;
static GLuint remoteShipTexture= -1;

void generateTextures(void);
GLuint load_texture(const char* file);


