#define SERVER_COMPILE_FLAG true
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"

#ifdef MAC_OSX_BUILD_MODE
#include "SDL_net.h"
#else
#include "SDL/SDL_net.h"
#endif	


#include "../Parser/Parser.h"
#include "../Enemy.h"

#include <SDL/SDL_main.h>


void waitForUpdates();
void createMonsterArray(int num, Enemy **cM, string file);
void sendLevel (UDPpacket *p, UDPsocket sd, Enemy **cM, int aL);
int lineCount(string file);
