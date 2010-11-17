#include <iostream>
#include <string.h>


#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
//linux includes
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <OpenGL/glu.h>
#include <SDL/SDL_audio.h>
#else // Linux includes
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <glu.h>
#include <SDL/SDL_audio.h>
#endif

#include "GameLoop.h"

static void createSurface (int fullscreen)
{
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	SDL_SetVideoMode(640,480,0,SDL_OPENGL);
	SDL_WM_SetCaption("Space Peaux Peaux",NULL);
	SDL_EnableKeyRepeat(1, 1);
	
}

static void initGL ()
{
	glViewport (0,0,640,480);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (45,640.0/480,0.1,100);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glEnable (GL_DEPTH_TEST);
	glClearColor (1,1,1,0);	
}

static void mainLoop ()
{
	
	GameLoop *gameLoop = new GameLoop();
	gameLoop->start();

}

int main(int argc, char *argv[])
{
    // Create GL context
    createSurface (0);
    
    // Init GL state
    initGL ();
    
    // Draw, get events...
    mainLoop ();
    
    // Cleanup
	SDL_Quit();
	
    return 0;
}
