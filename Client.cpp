#include "Client.h"

Client::Client(){
	/* Check for parameters */
	/* Initialize SDL_net */
	packetSize = 64;
	gameStarted = false;
	myParser = new Parser();
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	
	/* Open a socket on random port */
	if (!(sd = SDLNet_UDP_Open(0)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, "198.110.193.214",18844))
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "127.0.0.1", 12345, SDLNet_GetError());
		exit(EXIT_FAILURE);
 	}
	/* Allocate memory for the packet */
	if (!(p = SDLNet_AllocPacket(packetSize)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	p->address.host = srvadd.host;
	p->address.port = srvadd.port;
	noServer = false;
}
Client::~Client(){
	SDLNet_FreePacket(p);
	SDLNet_Quit();
}
void Client::TellPlayerAmount(int players){
	if(players == 1)
		strcpy((char *)p->data, "one");
	if(players == 2)
		strcpy((char *)p->data, "two");
	p->len = 4;
	SDLNet_UDP_Send(sd, -1, p);
}
float* Client::Position(float x, float y){
	sprintf((char *)p->data, "position %f %f", x, y);
	p->len = strlen((char *)p->data);
	SDLNet_UDP_Send(sd, -1, p);
	SDLNet_ResizePacket(p, packetSize);
	while(true){
		if(gameStarted)
			SDL_Delay(20);
		if(SDLNet_UDP_Recv(sd, p)){
			if(strcmp((char*) p->data, "Not Ready") != 0){
				gameStarted = true;
				float * a;
				a = myParser->OtherPlayer((char *) p->data);
				return a;
			}else if(!gameStarted){
				//cout << "Server said waiting for 2nd player" << endl;
				SDL_Delay(200);
				sprintf((char *)p->data, "position %f %f", x, y);
				p->len = strlen((char *)p->data);
				SDLNet_UDP_Send(sd, -1, p);
				SDLNet_ResizePacket(p, packetSize);
			}
		}
		if(gameStarted)
			break;
	}
}
int Client::GetArraySize(){
	int quit = 0;
	int arraySize = -1;
	while(!quit)
	{
		strcpy((char *)p->data, "size");
		p->len = 5;
		SDLNet_UDP_Send(sd, -1, p);
		int attempt = false;
		SDLNet_ResizePacket(p, packetSize);
 		while(true){
			if(SDLNet_UDP_Recv(sd, p)){

				arraySize = atoi((char *)p->data);
				quit = 1;
				break;
			}
			if(!attempt){
				sleep(4);
				attempt = true;
			}else{
				noServer = true;
				quit=1;
				break;
			}
		}
	}
	
	return arraySize;
}

void Client::GetEnemyList(Enemy **enemyList){
	//int quit = 0;
	int count = 0;
	int* params;
	strcpy((char *)p->data, "ready");
	p->len = 6;
	SDLNet_UDP_Send(sd, -1, p);
	SDLNet_ResizePacket(p, packetSize);
	while(true){
		if(SDLNet_UDP_Recv(sd, p)){

			if(!strcmp((char *)p->data, "quit"))
				break;
			//parse the char* //update the monster. move on
			params = myParser->CreateMonsterObject((char *)p->data);
			enemyList[count++]->update(params[0], params[1], params[2], params[3], params[4]);
			//cout << "updated enemy: " << count-1 << endl;
		}
	}
		//cout << "leaving" << endl;
}
int Client::LineCount(string fileName){
	ifstream openForLines;
	openForLines.open(fileName.c_str());
	int count = 0;
	while(!openForLines.eof()){
		getline(openForLines, fileName);
		count++;
	}
	openForLines.close();
	return count-1;
}
void Client::NoServerCall(int numOfLines, Enemy **currentMonsters, string filename){
	/* read the line. parse the line. create the monster. quit at eof*/
	ifstream openForParse;
	int count = 0;
	openForParse.open(filename.c_str());
	int* constructParams;
	while(count < numOfLines && !openForParse.eof()){
	//read the line
		string needsParsing;
		getline(openForParse, needsParsing);
	//parse the file.
		constructParams = myParser->CreateMonsterObject(needsParsing);
	//create the monster
		currentMonsters[count++]->update(constructParams[0], (float)constructParams[1], (float)constructParams[2], constructParams[3], constructParams[4]);
	}

	openForParse.close();
}
