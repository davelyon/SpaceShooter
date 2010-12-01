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

void Client::GetEnemyList(Enemy **ListOfEnemies){
	int quit = 0;
	while (!quit)
	{
		p->data = (Uint8 *)"Ready";
		
		p->address.host = srvadd.host;	/* Set the destination host */
		p->address.port = srvadd.port;	/* And destination port */
 
		p->len = strlen((char *)p->data) + 1;
		SDLNet_UDP_Send(sd, -1, p); /* This sets the p->channel */
		bool firstRead = true;
		int count = 0;
		int* params;
 		while(true){
			if(SDLNet_UDP_Recv(sd, p)){
				if(!strcmp((char *)p->data, "quit"))
					break;
				if(firstRead){
					Enemy *temp[atoi((char *)p->data)];
					for(int i = 0; i < atoi((char *)p->data); i++)
						temp[i] = new Enemy();
					ListOfEnemies = temp;
				}else{
					//parse the char* //update the monster. move on
					params = myParser->CreateMonsterObject((char *)p->data);
					ListOfEnemies[count++]->update(params[0], params[1], params[2], params[3], params[4]);
				}
					/* this needs to be changed to parsing out a enemy you need to create a parser object here.*/
				printf("%s", (char *)p->data);
				sleep(10);
			}
		}
		/* Quit if packet contains "quit" */
		if (!strcmp((char *)p->data, "quit"))
			quit = 1;
	}
 	printf("bye!");
}
