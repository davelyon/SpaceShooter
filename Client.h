#ifndef TheClientCaller
#define TheClientCaller

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Enemy.h"
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
#include "Parser/Parser.h"
class Client{
	private:
		UDPsocket sd;
		UDPpacket *p;
		IPaddress srvadd;
		Parser *myParser;
		
	public:
		Client();
		~Client();
		void GetEnemyList(Enemy **ListOfEnemies);


};
#endif
