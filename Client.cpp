#include "Client.h"

Client::Client(){
	/* Check for parameters */
	/* Initialize SDL_net */
	myParser = new Parser();
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	
	/* Open a socket on random port */
	if (!(sd = SDLNet_UDP_Open(14359)))
	{
	cout << "15098" << endl;
		if (!(sd = SDLNet_UDP_Open(15098)))
		{
			fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
			exit(EXIT_FAILURE);
		}
	}
 
	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, "127.0.0.1",18844))
	{
		fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", "127.0.0.1", 12345, SDLNet_GetError());
		exit(EXIT_FAILURE);
 	}
	/* Allocate memory for the packet */
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	p->address.host = srvadd.host;
	p->address.port = srvadd.port;
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
		cout << (char *)p->data << endl;
	p->len = 4;
	SDLNet_UDP_Send(sd, -1, p);
}
int Client::GetArraySize(){
	int quit = 0;
	int arraySize = -1;
	while(!quit)
	{
		char * temp = new char[5];
		strcpy(temp, "size");
		p->data = (Uint8 *)temp;
		p->address.host = srvadd.host;
		p->address.port = srvadd.port;
		p->len = 5;
		SDLNet_UDP_Send(sd, -1, p);
 		while(true){
			if(SDLNet_UDP_Recv(sd, p)){
				arraySize = atoi((char *)p->data);
				quit = 1;
				break;
			}
		}
		delete[] temp;
	}
	return arraySize;
}

void Client::GetEnemyList(Enemy **enemyList){
	int quit = 0;
	int count = 0;
	int* params;
	char * temp = new char[6];
	strcpy(temp, "ready");
	p->data = (Uint8 *)temp;
	p->address.host = srvadd.host;
	p->address.port = srvadd.port;
	p->len = 6;
	SDLNet_UDP_Send(sd, -1, p);
	while(true){
		if(SDLNet_UDP_Recv(sd, p)){
			if(!strcmp((char *)p->data, "quit"))
				break;
			//parse the char* //update the monster. move on
			char * r = (char *)p->data;
			string b = r;
			params = myParser->CreateMonsterObject(b);
			enemyList[count++]->update(params[0], params[1], params[2], params[3], params[4]);
		}
	}
}
Client::Client(int a){
	myParser = new Parser();
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
