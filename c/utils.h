#ifndef UTILS_H
#define BRAIN_H

//John Balis 2018
//for support email balisujohn@gmail.com


void mapIntToArray(int value, int * map, int length);
int mapArrayToInt(int * map, int length);
float randFloat();
int randRange(int limit);
int coinFlip();
float sigmoid(float x);
float mytanh(float x);



#endif 
