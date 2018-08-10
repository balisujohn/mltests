#ifndef LEARNING_H
#define LEARNING_H

void learn( int (*f)(brain *), int inputCount, int outputCount);
void multiSucc( int (*f)(brain *), int inputCount, int outputCount);
void populationLearn( int (*f)(brain *), int inputCount, int outputCount, int populationCount, int generations);



#endif
