#ifndef TheClientCaller
#define TheClientCaller

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "Enemy.h"
#include "SDL/SDL.h"
#include "SDL/SDL_net.h"
class Client{
	private:
		UDPsocket sd;
		UDPpacket *p;
		IPaddress srvadd;
		
	public:
		Client();
		~Client();
		void GetEnemyList(Enemy **ListOfEnemies);


};
#endif
