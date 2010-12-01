#include "Parser.h"

using namespace std;

Parser::Parser(){}
Parser::~Parser(){
}
int* Parser::CreateMonsterObject(string monsterCreationParams){
	string uID, x, y, img, points;
	int* returnable = new int[5];
	MonsterParser(&monsterCreationParams, &uID);
	returnable[0] = atoi(uID.c_str());
	MonsterParser(&monsterCreationParams, &x);
	returnable[1] = atoi(x.c_str());
	MonsterParser(&monsterCreationParams, &y);
	returnable[2] = atoi(y.c_str());
	MonsterParser(&monsterCreationParams, &img);
	returnable[3] = atoi(img.c_str());
	MonsterParser(&monsterCreationParams, &points);
	returnable[4] = atoi(points.c_str());
	//cout << "parser: " << uID << x << y << img << points << endl;
	return returnable;
}
void Parser::MonsterParser(string *params, string *varToSet){
	string newParams = *params;
	string newVarToSet;
	int found = newParams.find(" ");
	newVarToSet.assign(newParams, 0, found);
	newParams.erase(0, found+1);
	*params = newParams;
	*varToSet = newVarToSet;
}

