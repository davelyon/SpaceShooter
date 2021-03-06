#include "Server.h"
using namespace std;
void createMonsterArray(int numOfLines, Enemy **currentMonsters, string filename);
void sendLevel(UDPpacket *p, UDPsocket sd, Enemy **currentMonsters, int arrayLength);
void addScore(UDPpacket *p, UDPsocket sd);
int lineCount(string fileName);
int numOfLines = 0;
int packetSize = 64;
struct CurrentPlayer{
	int port;
	unsigned int host;
	int score;
	float x_Position;
	float y_Position;
	bool ready;
	unsigned int check;
};
void waitForUpdates(CurrentPlayer PlayerOne, CurrentPlayer PlayerTwo, Enemy **currentMonsters, UDPpacket *p, UDPsocket mySocketDesc);
int main(int argc, char *argv[])
{
	UDPsocket mySocketDesc;       /* Socket descriptor */
	UDPpacket *p;       /* Pointer to packet memory */
	int quit;
 
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Open a socket */
	if (!(mySocketDesc = SDLNet_UDP_Open(18844)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if (!(p = SDLNet_AllocPacket(packetSize)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Main loop */
	numOfLines = lineCount("level1.txt");
	Enemy *currentMonsters[numOfLines];
	if(numOfLines > 0){
		for(int i = 0; i < numOfLines; i++)
			currentMonsters[i] = new Enemy();
		createMonsterArray(numOfLines, currentMonsters, "level1.txt");
	}
	int count = 0;
	bool firstPlayerSignedIn = false;
	CurrentPlayer PlayerOne;
		PlayerOne.port = 0;
		PlayerOne.host = 0;
		PlayerOne.score = 0;
		PlayerOne.x_Position = 0;
		PlayerOne.y_Position = 0;
		PlayerOne.ready = false;
		PlayerOne.check = 0;
	CurrentPlayer PlayerTwo; 
		PlayerTwo.port = 0;
		PlayerTwo.host = 0;
		PlayerTwo.score = 0;
		PlayerTwo.x_Position = 0;
		PlayerTwo.y_Position = 0;
		PlayerTwo.ready = false;
		PlayerTwo.check = 0;
	while (true) {
		if (SDLNet_UDP_Recv(mySocketDesc, p)){
			unsigned int sPHost = SDLNet_Read32(&(p->address.host));
			int sPPort = SDLNet_Read16(&(p->address.port));
			unsigned int somePlayer = sPHost*sPPort;
			char * incoming = (char *) p->data;
			if(strcmp(incoming, "size") == 0){
				cout << "sending size" << endl;
				char * temp = (char *)malloc(sizeof(char) * 25);;
				sprintf(temp, "%d", numOfLines);
				strcpy((char *)p->data, temp);
				p->len = strlen((char *)p->data)+1;
				SDLNet_UDP_Send(mySocketDesc, -1, p);
				free(temp);
			}else if (strcmp(incoming, "ready") == 0){
				cout << "sending level" << endl;
				sendLevel(p, mySocketDesc, currentMonsters, numOfLines);
				count = 0;
				if(somePlayer == PlayerOne.check)
					PlayerOne.ready = true;
				else if(somePlayer == PlayerTwo.check)
					PlayerTwo.ready = true;
				if(PlayerOne.ready && PlayerTwo.ready){
					cout << "entering loop" << endl;
					waitForUpdates(PlayerOne, PlayerTwo, currentMonsters, p, mySocketDesc);
					PlayerOne.port = PlayerTwo.port = 0;
					PlayerOne.ready = PlayerTwo.ready = false;
				}
			}else if (strcmp(incoming, "highScore") == 0){
				addScore(p, mySocketDesc);
			}else if (strcmp(incoming, "two") == 0){
				if(PlayerOne.port == 0){
					PlayerOne.port = SDLNet_Read16(&(p->address.port));
					PlayerOne.host = SDLNet_Read32(&(p->address.host));
					PlayerOne.check = PlayerOne.host * PlayerOne.port;
				}
				if(SDLNet_Read16(&(p->address.port)) != PlayerOne.port && PlayerOne.port != PlayerTwo.port){
					PlayerTwo.port = SDLNet_Read16(&(p->address.port));
					PlayerTwo.host = SDLNet_Read32(&(p->address.host));
					PlayerTwo.check = PlayerTwo.host * PlayerTwo.port;
				}
			}else if(strncmp(incoming, "position", 8) == 0){
				strcpy((char *)p->data, "Not Ready");
				p->len = strlen((char *)p->data)+1;
				SDLNet_UDP_Send(mySocketDesc, -1, p);
			}
			SDLNet_ResizePacket(p, packetSize);
		}
		SDL_Delay(100);
	}
	/* Clean and exit */
	SDLNet_FreePacket(p);
	SDLNet_Quit();
	return EXIT_SUCCESS;
}
void addScore(UDPpacket *p, UDPsocket sd){
	while(!SDLNet_UDP_Recv(sd, p)){}
	char * temp = (char *)malloc(sizeof(char) * 25);;
	strcpy(temp, (char *)p->data);
	ofstream hsFile;
	hsFile.open("HighScores.txt");
	hsFile << temp << endl;
	hsFile.close();
}
void createMonsterArray(int numOfLines, Enemy **currentMonsters, string filename){
	Parser *myParser = new Parser();
	/* read the line. parse the line. create the monster. quit at eof*/
	ifstream openForParse;
	int count = 0;
	openForParse.open(filename.c_str());
	string needsParsing;
	int* constructParams;
	while(count < numOfLines && !openForParse.eof()){
	//read the line
		getline(openForParse, needsParsing);
	//parse the file.
		constructParams = myParser->CreateMonsterObject(needsParsing);
	//create the monster
		currentMonsters[count++]->update(constructParams[0], (float)constructParams[1], (float)constructParams[2], constructParams[3], constructParams[4]);
	}
	openForParse.close();
}
void sendLevel(UDPpacket *p, UDPsocket sd, Enemy **currentMonsters, int arrayLength){
	unsigned int sPHost = SDLNet_Read32(&(p->address.host));
	int sPPort = SDLNet_Read16(&(p->address.port));
	int count = 0;
	string apple;
	SDLNet_ResizePacket(p, packetSize);
	while (count < arrayLength){
		apple = currentMonsters[count++]->toString();
		strcpy((char *)p->data, apple.c_str());
		p->len = apple.length()+1;
		SDLNet_UDP_Send(sd, -1, p);
		SDLNet_ResizePacket(p, packetSize);
	}	
	SDLNet_ResizePacket(p, packetSize);
	strcpy((char *)p->data, "quit");
	p->len = 5;
	SDLNet_UDP_Send(sd, -1, p);
}
			/* takes a position call. on any call we ALWAYS send updates 
			 * to store updates. Create a new monster array,
			 * only update on the new array never on the old. Position should only set
			 * player position. Destroyed will check if something was destroyed or if it can be
			 * and return a score. a score of 0 is already dead stop fucking with me
			 * anything else is it got the points
			 */
void waitForUpdates(CurrentPlayer PlayerOne, CurrentPlayer PlayerTwo, Enemy **currentMonsters, UDPpacket *p, UDPsocket mySocketDesc){
	unsigned int p1Check, p2Check;
	p1Check = PlayerOne.host * PlayerOne.port;
	p2Check = PlayerTwo.host * PlayerTwo.port;
	Parser *myParser = new Parser();
	while (true) {
		if (SDLNet_UDP_Recv(mySocketDesc, p)){
			unsigned int somePlayer = SDLNet_Read32(&(p->address.host))*SDLNet_Read16(&(p->address.port));
			if(somePlayer != p1Check && somePlayer != p2Check){
				char * incoming = (char *) p->data;
				if(strcmp(incoming, "size") == 0){
					char * temp = (char *)malloc(sizeof(char) * 25);
					sprintf(temp, "%d", numOfLines);
					strcpy((char *)p->data, temp);
					p->len = strlen((char *)p->data)+1;
					SDLNet_UDP_Send(mySocketDesc, -1, p);
					free(temp);
				}else if (strcmp(incoming, "ready") == 0){
					cout << "sending level" << endl;
					sendLevel(p, mySocketDesc, currentMonsters, numOfLines);
				}else if (strcmp(incoming, "highScore") == 0){
					addScore(p, mySocketDesc);
				}
			}else{
				char * incoming = (char *) p->data;
				if(strncmp(incoming, "position", 8) == 0){
					float * a;			
					a = myParser->Position(incoming);
					char * temp = (char *)malloc(sizeof(char) * 15);;
					if(p1Check == somePlayer){
						PlayerOne.x_Position = a[0];
						PlayerOne.y_Position = a[1];
						sprintf(temp,"%f %f", PlayerTwo.x_Position, PlayerTwo.y_Position);
					}else{
						PlayerTwo.x_Position = a[0];
						PlayerTwo.y_Position = a[1];
						sprintf(temp,"%f %f", PlayerOne.x_Position, PlayerOne.y_Position);
					}
					//if running out of space look at this
					strcpy((char *)p->data, temp);
					p->len = strlen((char *)p->data)+1;
					SDLNet_UDP_Send(mySocketDesc, -1, p);
					free(temp);
				}
			}

			SDLNet_FreePacket(p);
			if(!(p = SDLNet_AllocPacket(packetSize)))
			{
				fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
				exit(EXIT_FAILURE);
			}
		}
	}
	cout << "finished" <<endl;
}
int lineCount(string fileName){
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
