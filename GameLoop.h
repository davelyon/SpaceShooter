/*
 *  GameLoop.h
 *  SpaceRedux
 *
 *  Created by Dave Lyon on 11/16/10.
 *  Copyright 2010 Northern Michigan University. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef MAC_OS_X_VERSION_MIN_REQUIRED
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

#include "Player.h"

class GameLoop
{
public:
	GameLoop ();
	virtual ~GameLoop ();
	
	void start();
	void pause();
	void end();
	
	
	
//private:
	
	void run();
	
	void handleKeyInput();
	void tickLevel();
	void tickActors();
	void drawScene();
	
	void pauseWait();
	
	int tick;
	
	int pausedBeganTick;
	
	bool paused;
	bool running;
		
	Player *player1;
	
	
};

