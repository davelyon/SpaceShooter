#include <iostream>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int main () {
  ofstream myfile ("level1.txt");
  if (myfile.is_open())
  {
  for (int i = 0; i < 50; i++){
  	char * output = new char[1000];
	float x;
	if((rand()%2))
		x = (rand()%210)/100.0f*-1.0;
	else
		x = (rand()%150)/100.0f;
	float y = 1+i*(rand()%150)/100.0f;
	sprintf(output,"%d %f %f 1 75", i, x, y);
    myfile << output <<endl;
  }
  	myfile.close();
  }
  else cout << "Unable to open file";
  return 0;
}
