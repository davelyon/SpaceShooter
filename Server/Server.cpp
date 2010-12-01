#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "../Parser/Parser.h"
#include "../Enemy.h"

using namespace std;
void waitForUpdates();
void createMonsterArray(Enemy **currentMonsters, string filename);
void sendLevel(UDPpacket *p, UDPsocket sd, Enemy **currentMonsters, int arrayLength);
int lineCount(string fileName);
int main(int argc, char **argv)
{
	UDPsocket mySocketDesc;       /* Socket descriptor */
	UDPpacket *p1, *p2, *p;       /* Pointer to packet memory */
	IPaddress p1IpAddress, p2IpAddress;
	int quit;
 
	/* Initialize SDL_net */
	if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Open a socket */
	if (!(mySocketDesc = SDLNet_UDP_Open(12345)))
	{
		fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Make space for the packet */
	if (!(p1 = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(p2 = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
	if (!(p = SDLNet_AllocPacket(512)))
	{
		fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Main loop */
	int numOfLines = lineCount("level1.txt");
	Enemy *currentMonsters[numOfLines];
	if(numOfLines > 0){
		for(int i = 0; i < numOfLines; i++)
			currentMonsters[i] = new Enemy();
		/* IF WE ARE SEG FAULTING LOOK AT THE LINE BELOW */
		createMonsterArray(currentMonsters, "level1.txt");
	}
	int count = 0;
	while (count != 2)
	{
		if(count == 0){
			if (SDLNet_UDP_Recv(mySocketDesc, p1)){
				cout << "sending level" << endl;
				sendLevel(p1, mySocketDesc, currentMonsters, numOfLines);
				count++;
			}
		}else if (count == 1){
			if (SDLNet_UDP_Recv(mySocketDesc, p2)){
				cout << "sending level" << endl;
				sendLevel(p2, mySocketDesc, currentMonsters, numOfLines);
				count++;
			}
		}else
			cout << "ok" <<endl;
		/* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
	}
 
	/* Clean and exit */
	SDLNet_FreePacket(p);
	SDLNet_Quit();
	return EXIT_SUCCESS;
}
void createMonsterArray(Enemy **currentMonsters, string filename){
	Parser *myParser = new Parser();
	/* read the line. parse the line. create the monster. quit at eof*/
	ifstream openForParse;
	int count = 0;
	openForParse.open(filename.c_str());
	string needsParsing;
	int* constructParams;
	while(!openForParse.eof()){
	//read the line
		getline(openForParse, needsParsing);
	//parse the file.
		constructParams = myParser->CreateMonsterObject(needsParsing);
	//create the monster
		currentMonsters[count++]->update(constructParams[0], constructParams[1], constructParams[2], constructParams[3], constructParams[4]);
	}
	openForParse.close();
}
void sendLevel(UDPpacket *p, UDPsocket sd, Enemy **currentMonsters, int arrayLength){
	sleep(5);int count = 0;
	while (count < arrayLength+1){
		char * temp = currentMonsters[count++]->toString();
		p->data =(Uint8 *) temp;
		p->len = strlen(temp)+1;
		SDLNet_UDP_Send(sd, -1, p);
		cout << "waiting for reply" << endl;
		/*while(true){
			if(SDLNet_UDP_Recv(sd, p)){
				cout << "GOT IT!" << endl;
				break;
			}
		}*/
		count++;
	}
	p->data = (Uint8 *)"quit";
	p->len = 5;
	SDLNet_UDP_Send(sd, -1, p);
}
void waitForUpdates(){
	

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
	return count;
}	
