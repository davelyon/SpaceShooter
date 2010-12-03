#include "Server.h"
using namespace std;
void waitForUpdates();
void createMonsterArray(int numOfLines, Enemy **currentMonsters, string filename);
void sendLevel(UDPpacket *p, UDPsocket sd, Enemy **currentMonsters, int arrayLength);
int lineCount(string fileName);
int main(int argc, char *argv[])
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
		createMonsterArray(numOfLines, currentMonsters, "level1.txt");
	}
	int count = 0;
	while (true)
	{
		if (SDLNet_UDP_Recv(mySocketDesc, p1)){
			char * incoming = (char *) p1->data;
			cout <<(char *) p1->data << endl;
			if(strcmp(incoming, "size") == 0){
				cout << "sending size" << endl;
				char * temp = new char[25];
				sprintf(temp, "%d", numOfLines);
				strcpy((char *)p1->data, temp);
				p1->len = strlen((char *)p1->data)+1;
				SDLNet_UDP_Send(mySocketDesc, -1, p1);
				delete [] temp;
			}else if (strcmp(incoming, "ready") == 0){
				cout << "sending level" << endl;
				sendLevel(p1, mySocketDesc, currentMonsters, numOfLines);
				count = 0;
			}
		}
	}		
	/* Clean and exit */
	SDLNet_FreePacket(p);
	SDLNet_Quit();
	return EXIT_SUCCESS;
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
	sleep(2);
	int count = 0;
	char * temp = new char[25];
	while (count < arrayLength){
		currentMonsters[count++]->toString(temp);
		p->data =(Uint8 *) temp;
		cout << endl;
		p->len = strlen(temp)+1;
		printf("sendLevel: %s\n", temp);
		SDLNet_UDP_Send(sd, -1, p);
	}
	strcpy((char *)p->data, "quit");
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
	return count-1;
}
