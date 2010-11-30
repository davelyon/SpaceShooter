#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop(){
	tick = SDL_GetTicks();
	paused = false;
	running = true;
		
	player1 = new Player(1);
	monster1 = new Enemy(100);
}

GameLoop::~GameLoop(){
	delete player1;
}

void GameLoop::start() {

	while(running) {
		paused ? pauseWait() : run();
	}
}

void GameLoop::run() {

	tick = 100;
	
	handleKeyInput();
	tickLevel();
	tickActors();
	drawScene();
}

void GameLoop::handleKeyInput() 
{
	
	SDL_Event event;
	while (SDL_PollEvent (&event)) {
		if (event.type==SDL_KEYDOWN)
			switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					player1->update(tick, MOVE_DOWN);
					break;
				case SDLK_UP:
					player1->update(tick, MOVE_UP);
					break;
				case SDLK_LEFT:
					player1->update(tick, MOVE_LEFT);
					break;
				case SDLK_RIGHT:
					player1->update(tick, MOVE_RIGHT);
					break;
				case SDLK_p:
					paused = !paused;
				case SDLK_ESCAPE:
					running = -1;
					break;
				default:
					break;
			}
	}
	
}

void GameLoop::tickLevel() 
{
}

void GameLoop::tickActors() 
{
	monster1->update();
}

void GameLoop::drawScene() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	player1->draw();
	monster1->draw();

	SDL_GL_SwapBuffers();

}

void GameLoop::pauseWait() {
	handleKeyInput();
}
