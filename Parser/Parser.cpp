#include <iostream>
#include <fstream>
#include <cstdlib>
#include "../Monster.h"
#include <string>
#include "Parser.h"

void WhichObjectToCreate(string line){
	string temp = line;
	temp.erase(temp.find(" "));
	line.erase(0, line.find(" " )+1);
	if(!temp.compare("monster"))
		CreateMonsterObject(line);
	else{
		cout << "THIS TYPE OF OBJECT ISN'T CREATED: "<< temp <<endl;
	}
}
void CreateMonsterObject(string monsterCreationParams){
	string x, y, img, points;
	MonsterParser(&monsterCreationParams, &x);
	MonsterParser(&monsterCreationParams, &y);
	MonsterParser(&monsterCreationParams, &img);
	MonsterParser(&monsterCreationParams, &points);
//	Monster balla = new Monster(atoi(x.c_str()), atoi(y.c_str()), atoi(img.c_str()), atoi(points.c_str()));
}
void MonsterParser(string *params, string *varToSet){
	string newParams = *params;
	string newVarToSet;
	int found = newParams.find(" ");
	newVarToSet.assign(newParams, 0, found);
	newParams.erase(0, found+1);
	*params = newParams;
	*varToSet = newVarToSet;
}
void parseFile(string filename){
	fstream file;
	file.open(filename.c_str());
	if(file.is_open()){
		string objectToCreate;
		while(getline(file, objectToCreate))
			WhichObjectToCreate(objectToCreate);
	}else
		cout << "file open failed. did you send me the right file?\n";
}
