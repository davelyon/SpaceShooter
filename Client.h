#ifndef TheClientCaller
#define TheClientCaller

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Enemy.h"
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
		
	public:
		Client();
		Client(int a);
		~Client();
		void NoServerCall(int numOfLines, Enemy **currentMonsters, string filename);
		void GetEnemyList(Enemy** enemyList);
		int GetArraySize();
		void TellPlayerAmount(int players);


};
#endif
