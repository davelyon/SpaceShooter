#include "GameLoop.h"
#include <iostream>
#ifdef MAC_OSX_BUILD_MODE
#include "MacBundle.h"
#define soundFile  "laser_44100hz_16bit_stereo.wav"
#else
#define soundFile  "./laser_44100hz_16bit_stereo.wav"
#endif

GameLoop::GameLoop(){
	levelSpeed = 0;
	realtick = 0;
	movePlayer = MOVE_DOWN;
	ratelimiter = 0;
	paused = true;
	running = true;
	player1 = new Player(1);
	soundManager = SoundManager::Instance();
	partEmitter = new ParticleEmitter();
	secondEmitter = new ParticleEmitter();
//	monster1 = new Enemy(0,-1,-1,0,100);
	if(TTF_Init() == -1) {
		printf("Failed to start SDL_TTF!\n");
		exit(4);
	}
#ifdef MAC_OSX_BUILD_MODE	
	font = TTF_OpenFont(absoluteBundleResourcePath("Anonymous_Pro.ttf"), 18);
#else
	font = TTF_OpenFont("./Anonymous_Pro.ttf", 18);
#endif
	if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    exit(7);
	}
	playersInGame = 0;
		char * one = (char *)malloc(sizeof(char)*21);
		char * two = (char *)malloc(sizeof(char)*21);
		strcpy(one, "Press 1 for 1 player");
		strcpy(two, "Press 2 for 2 player");
	while(true){
		if(playersInGame == 1 || playersInGame ==2)
			break;
		displayTextScreen(one, two);
	}
	free(one);
	free(two);
	//set up client
	displayTextScreen((char *)"loading.");
	client = new Client();
	client->TellPlayerAmount(playersInGame);
	size = client->GetArraySize();
	if(client->noServer){
		char * noServText = (char *)malloc(sizeof(char)*16);
		char * singlText = (char *)malloc(sizeof(char)*19);
		strcpy(noServText, "No Server Found");
		strcpy(singlText, "Loading Local File");
		displayTextScreen(noServText, singlText);
		SDL_Delay(1500);
		free(noServText);
		free(singlText);
		playersInGame = 1;
#ifdef MAC_OSX_BUILD_MODE
		size = client->LineCount(absoluteBundleResourcePath("level1.txt"));
#else
		size = client->LineCount("level1.txt");
#endif
	}
	if(playersInGame == 2)
		displayTextScreen((char *)"loading..");
	for(int i = 0; i < size; i++)
		crazies[i] = new Enemy();
	displayTextScreen((char *)"loading...");
	if(client->noServer)
#ifdef MAC_OSX_BUILD_MODE
		client->NoServerCall(size, crazies, absoluteBundleResourcePath("level1.txt"));
#else
		client->NoServerCall(size, crazies, "level1.txt");
#endif
	else
		client->GetEnemyList(crazies);
		//cout << "ok" << endl;
}

GameLoop::~GameLoop(){
	delete player1;
}

void GameLoop::start() {

	char * startText = (char *)malloc(sizeof(char)*12);
	strcpy(startText, "Press Start");
	while(paused){
		displayTextScreen(startText);
	}

	char * pauseText = (char *)malloc(sizeof(char)*12);
	strcpy(pauseText, "Game Paused");
	while(running) {
		int copy = SDL_GetTicks();
		if(realtick)
			tick =  copy - realtick;
		else
			tick = 30;
		realtick = copy;
		paused ? displayTextScreen(pauseText) : run();
	}
	free(pauseText);
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
	while (SDL_PollEvent(&event)) {
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
					if(!paused){
						player1->shoot(realtick);
#ifdef MAC_OSX_BUILD_MODE
					soundManager->PlaySound(absoluteBundleResourcePath(soundFile));						
#else	
					soundManager->PlaySound(soundFile);
#endif
					break;
				case SDLK_p:
					paused = !paused;
					break;
				case SDLK_RETURN:
					paused = false;
					break;
				case SDLK_RSHIFT:
				case SDLK_LSHIFT:
					player1->holdPosition(true);
					break;
				case SDLK_ESCAPE:
					running = -1;
					exit(1);
					break;
				case SDLK_1:
					playersInGame = 1;
					break;
				case SDLK_2:
					playersInGame = 2;
					break;
				default:
					break;
			} else if (event.type==SDL_KEYUP) {
				switch (event.key.keysym.sym) {
					case SDLK_RSHIFT:
					case SDLK_LSHIFT:
						player1->holdPosition(false);
						break;
				}
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
	levelSpeed +=1.0f;
	if(playersInGame == 2 && ratelimiter + 50 <= realtick){
		ratelimiter = realtick;
		
		float * b;
		b = client->Position(player1->getX(), player1->getY());

		player1->otherPlayer.x = b[0];
		player1->otherPlayer.y = b[1];
	}
	//monster1->update(tick);
	for(int i = 0; i < size; i++){
		crazies[i]->update(tick);
		crazies[i]->collideWith((Actor *)player1);
	}
}

void GameLoop::drawScene() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glMatrixMode(GL_TEXTURE);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	
	if (player1->living()) 
		partEmitter->renderParticles(0, player1->getX(), player1->getY());
	else{
		char * gameOver = (char *)malloc(sizeof(char)*9);
		strcpy(gameOver, "Game Over");
		while(true)
			displayTextScreen(gameOver);
		free(gameOver);
	}
	if(playersInGame == 2){
		secondEmitter->renderParticles(0, player1->otherPlayer.x, player1->otherPlayer.y);
		player1->draw(true);
	}else{
		player1->draw(false);
	}
	
	for(int i = 0; i < size; i++)
		crazies[i]->draw();

	SDL_Color color = {255,255,255};
	SDL_Rect location ;
	location.x = 10;
	location.y = 766;
	char text[100];
	int fps = SDL_GetTicks() - realtick;
	glMatrixMode(GL_COLOR);
	glLoadIdentity();
	glPushMatrix();
	sprintf(text, "Player 1: %09d FPS: %.2f", player1->points(), (fps > 0) ? 1000.0f / (float)fps : 0.0f );
	glPopMatrix();
	SDL_GL_RenderText(text, font, color, &location);

	glPopMatrix();
	SDL_GL_SwapBuffers();


}
void GameLoop::displayTextScreen(char * displayTop, char * displayBot) {
	handleKeyInput();
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	
	SDL_Rect location;
	location.x = 250;
	location.y = 360;
	SDL_Color color = {255,255,255};
	SDL_GL_RenderText(displayTop, font, color, &location);
	location.y = 340;
	SDL_GL_RenderText(displayBot, font, color, &location);
	SDL_Delay(100); // Render menu @ 10fps
	SDL_GL_SwapBuffers();
}
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
