#ifndef TheGameLoop
#define TheGameLoop
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
#include <GL/glu.h>
#include <SDL/SDL_audio.h>
#endif

#include "Client.h"
#include "Player.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleEmitter.h"

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
	
	int realtick;
	int tick;
	
	int pausedBeganTick;
	
	bool paused;
	bool running;
		
	Player *player1;
	Enemy *monster1;
	Enemy *crazies[100];
	Client *client;
	SoundManager *soundManager;
	ParticleEmitter *partEmitter;
	
	int movePlayer;
	
};
#endif
