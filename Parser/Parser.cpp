#include "Parser.h"

using namespace std;

Parser::Parser(){}
Parser::~Parser(){
}
int* Parser::CreateMonsterObject(string monsterCreationParams){
	string uID, x, y, img, points;
	int* returnable = new int[5];
	SpaceParser(&monsterCreationParams, &uID);
	returnable[0] = atoi(uID.c_str());
	SpaceParser(&monsterCreationParams, &x);
	returnable[1] = atoi(x.c_str());
	SpaceParser(&monsterCreationParams, &y);
	returnable[2] = atoi(y.c_str());
	SpaceParser(&monsterCreationParams, &img);
	returnable[3] = atoi(img.c_str());
	SpaceParser(&monsterCreationParams, &points);
	returnable[4] = atoi(points.c_str());
	return returnable;
}
float* Parser::Position(string XYPositions){
	string xPos, yPos, junk;
	float* returnable = new float[2];
	SpaceParser(&XYPositions, &junk);
	SpaceParser(&XYPositions, &xPos);
	returnable[0] = atof(xPos.c_str());
	SpaceParser(&XYPositions, &yPos);
	returnable[1] = atof(yPos.c_str());
	return returnable;
}
float* Parser::OtherPlayer(string XYPositions){
	string xPos, yPos;
	float* returnable = new float[2];
	SpaceParser(&XYPositions, &xPos);
	returnable[0] = atof(xPos.c_str());
	SpaceParser(&XYPositions, &yPos);
	returnable[1] = atof(yPos.c_str());
	return returnable;
}
void Parser::SpaceParser(string *params, string *varToSet){
	string newParams = *params;
	string newVarToSet;
	int found = newParams.find(" ");
	newVarToSet.assign(newParams, 0, found);
	newParams.erase(0, found+1);
	*params = newParams;
	*varToSet = newVarToSet;
}

