#ifndef TheClientCaller
#define TheClientCaller

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Enemy.h"
#include "Player.h"
#include "SDL/SDL.h"

#ifdef MAC_OSX_BUILD_MODE
#include "SDL_net.h"
#else
#include "SDL/SDL_net.h"
#endif	


#include "Parser/Parser.h"
class Client{
	private:
		UDPsocket sd;
		UDPpacket *p;
		IPaddress srvadd;
		Parser *myParser;
		int packetSize;
		
	public:
		Client();
		~Client();
		void NoServerCall(int numOfLines, Enemy **currentMonsters, string filename);
		void GetEnemyList(Enemy** enemyList);
		int LineCount(string fileName);
		int GetArraySize();
		bool gameStarted;
		void TellPlayerAmount(int players);
		float* Position(float x, float y);
		bool noServer;


};
#endif
