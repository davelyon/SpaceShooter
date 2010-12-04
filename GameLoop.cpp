#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop(){
	realtick = 0;
	paused = false;
	running = true;
		
	player1 = new Player(1);
	client = new Client();
	soundManager = SoundManager::Instance();
	partEmitter = new ParticleEmitter();
	monster1 = new Enemy(0,5,-5,0,100);
	for(int i = 0; i < 100; i++)
		crazies[i] = new Enemy();
	size = client->GetArraySize();
	client->GetEnemyList(crazies);
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
	//printf("Tick: %d \n", tick);
	handleKeyInput();
	tickLevel();
	tickActors();
	drawScene();
	//SDL_Delay(10);
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
					soundManager->PlaySound("/home/msherman/videoGames/hold/SpaceShooter/laser2.wav");
					break;
				case SDLK_p:
					paused = !paused;
					break;
				case SDLK_ESCAPE:
					running = -1;
					exit(1);
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
	for(int i = 0; i < size; i++)
		crazies[i]->update();
}

void GameLoop::drawScene() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	partEmitter->renderParticles(0, player1->getX(), player1->getY());
	player1->draw();
	monster1->draw();
	for(int i = 0; i < size; i++)
		crazies[i]->draw();

	SDL_GL_SwapBuffers();

}

void GameLoop::pauseWait() {
	handleKeyInput();
}
