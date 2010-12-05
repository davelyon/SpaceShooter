#ifndef parserOut
#define parserOut
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
using namespace std;
class Parser{
	public:
		Parser();
		~Parser();
		void SpaceParser(string *params, string *varToSet);
		int* CreateMonsterObject(string monsterCreationParams);
		float* Position(string XYPositions);
		float* OtherPlayer(string XYPositions);
};
#endif

