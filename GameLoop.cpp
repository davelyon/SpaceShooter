#include "GameLoop.h"
#include <iostream>

GameLoop::GameLoop(){
	realtick = 0;
	paused = true;
	running = true;
	player1 = new Player(1);
	soundManager = SoundManager::Instance();
	partEmitter = new ParticleEmitter();
	monster1 = new Enemy(0,1,-1,0,100);
//	for(int i = 0; i < 100; i++)
//		crazies[i] = new Enemy();
	client = new Client();
	client->TellPlayerAmount(2);
	size = client->GetArraySize();
	if(client->noServer)
		size = client->LineCount("level1.txt");
	for(int i = 0; i < size; i++)
		crazies[i] = new Enemy();
	if(client->noServer){
		cout << "NoServerCall" << endl;
		client->NoServerCall(size, crazies, "level1.txt");
	}else
		client->GetEnemyList(crazies);
	if(TTF_Init() == -1) {
		printf("Failed to start SDL_TTF!\n");
		exit(4);
	}
#ifdef MAC_OSX_BUILD_MODE	
	font = TTF_OpenFont("/Users/dave/Code/LevelCode/Anonymous_Pro.ttf", 18);
#else
	font = TTF_OpenFont("/home/msherman/videoGames/hold/SpaceShooter/Anonymous_Pro.ttf", 18);
#endif
	if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    exit(7);
	}
	
}

GameLoop::~GameLoop(){
	delete player1;
}

void GameLoop::start() {
	SDL_GL_SwapBuffers();

	while(paused) 
		displayTextScreen((char *)"Press Start");
	
	while(running) {
		
		int copy = SDL_GetTicks();
		tick =  copy - realtick;
		realtick = copy;
				
		paused ? displayTextScreen((char *)"Game Paused") : run();
	}
}

void GameLoop::run() {
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
					if(!paused)
						movePlayer = MOVE_DOWN;
					break;
				case SDLK_UP:
					if(!paused)
						movePlayer = MOVE_UP;
					break;
				case SDLK_LEFT:
					if(!paused)
						movePlayer = MOVE_LEFT;
					break;
				case SDLK_RIGHT:
					if(!paused)
						movePlayer = MOVE_RIGHT;
					break;
				case SDLK_SPACE:
					if(!paused)
						player1->shoot(realtick);
					//soundManager->PlaySound("/Users/dave/Code/SpaceRedux/laser2.wav");
					break;
				case SDLK_p:
					paused = !paused;
					break;
				case SDLK_RETURN:
					paused = false;
					break;
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					player1->holdPosition(TRUE);
					break;
				case SDLK_ESCAPE:
					running = -1;
					exit(1);
					break;
				default:
					break;
			} else if (event.type==SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_RSHIFT:
					case SDLK_LSHIFT:
						player1->holdPosition(FALSE);
						break;

				}
			}
	}
	
}

void GameLoop::tickLevel() 
{
	
}

void GameLoop::tickActors() 
{
	player1->update(tick, movePlayer);
	float * b;
	b = client->Position(player1->getX(), player1->getY());
	player1->otherPlayer.x = b[0];
	player1->otherPlayer.y = b[1];
	monster1->update(tick);
	for(int i = 0; i < size; i++)
		crazies[i]->update(tick);
}

void GameLoop::drawScene() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	partEmitter->renderParticles(0, player1->getX(), player1->getY());
	player1->draw();
	monster1->draw();
//	for(int i = 0; i < size; i++)
//		crazies[i]->draw();

	SDL_Color color = {255,255,255};
	SDL_Rect location ;
	location.x = 10;
	location.y = 766;
	char text[100];
	int fps = SDL_GetTicks() - realtick;
	sprintf(text, "Player 1: %09d FPS: %.2f", tick, (fps > 0) ? 1000.0f / (float)fps : 0.0f );
	SDL_GL_RenderText(text, font, color, &location);
	
	
	SDL_GL_SwapBuffers();

}

/*void GameLoop::pauseWait() {
	handleKeyInput();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();

	SDL_Rect location ;
	location.x = 270;
	location.y = 350;
	SDL_Color color = {255,255,255};
	char * GamePause= new char[13];
	strcpy(GamePause, "Game Paused.");
	SDL_GL_RenderText(GamePause, font, color, &location);
	SDL_Delay(100); // Render menu @ 10fps
	SDL_GL_SwapBuffers();

}*/

void GameLoop::displayTextScreen(char * displayText) {
	handleKeyInput();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	SDL_Rect location ;
	location.x = 270;
	location.y = 350;
	SDL_Color color = {255,255,255};
	SDL_GL_RenderText(displayText, font, color, &location);
	SDL_Delay(100); // Render menu @ 10fps
	SDL_GL_SwapBuffers();
	
	
}
