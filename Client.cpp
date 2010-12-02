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
	if (!(sd = SDLNet_UDP_Open(12234)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Resolve server name  */
	if (SDLNet_ResolveHost(&srvadd, "127.0.0.1",12345))
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
}
Client::~Client(){
	SDLNet_FreePacket(p);
	SDLNet_Quit();
}

Enemy** Client::GetEnemyList(){
	int quit = 0;
	int arraySize = 0;
		int count = 0;
		int* params;
	while (!quit)
	{
		strcpy((char *)p->data, "ready");	
		p->address.host = srvadd.host;
		p->address.port = srvadd.port;
 
		p->len = strlen((char *)p->data) + 1;
		SDLNet_UDP_Send(sd, -1, p);
 		while(true){
			if(SDLNet_UDP_Recv(sd, p)){
				arraySize = atoi((char *)p->data);
				quit = 1;
				break;
			}
		}
		cout <<"I'm out"<<endl;
	}
		cout <<"true!" <<endl;
	static Enemy *enemyList[100];
	for (int i = 0; i < 100; i++)
		enemyList[i] = new Enemy();
	strcpy((char *)p->data, "ready");	
	p->len = strlen((char *)p->data) + 1;
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
	char * asdf = new char[25];
	enemyList[20]->toString(asdf);
	printf("asdf, %s\n\n\n", asdf);
	return enemyList;
}
