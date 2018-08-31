#ifndef LEARNING_H
#define LEARNING_H

//John Balis 2018
//for support email balisujohn@gmail.com



void learn( float (*f)(brain *), int inputCount, int outputCount);
void multiSucc( float (*f)(brain *), int inputCount, int outputCount, int childCount);
void populationLearn( float (*f)(brain *), int inputCount, int outputCount, int populationCount, int generations);



#endif
