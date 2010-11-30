#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop(){
	realtick = 0;
	paused = false;
	running = true;
		
	player1 = new Player(1);
	monster1 = new Enemy(100);
	soundManager = new SoundManager();
}

GameLoop::~GameLoop(){
	delete player1;
}

void GameLoop::start() {

	while(running) {
		
		int copy = SDL_GetTicks();
		tick =  copy - realtick;
		realtick = copy;
				
		paused ? pauseWait() : run();
	}
}

void GameLoop::run() {
	printf("Tick: %d Real Tick %d \n", tick, realtick);
	
	handleKeyInput();
	tickLevel();
	tickActors();
	drawScene();
	soundManager->play();
	SDL_Delay(10);
}

void GameLoop::handleKeyInput() 
{
	
	SDL_Event event;
	while (SDL_PollEvent (&event)) {
		if (event.type==SDL_KEYDOWN)
			switch (event.key.keysym.sym) {
				case SDLK_DOWN:
					movePlayer = MOVE_DOWN;
					break;
				case SDLK_UP:
					movePlayer = MOVE_UP;
					break;
				case SDLK_LEFT:
					movePlayer = MOVE_LEFT;
					break;
				case SDLK_RIGHT:
					movePlayer = MOVE_RIGHT;
					break;
				case SDLK_SPACE:
					player1->shoot(realtick);
					soundManager->PlaySound("/Users/dave/Code/SpaceRedux/laser2.wav");
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
	player1->update(tick, movePlayer);
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
