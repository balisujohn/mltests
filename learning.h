#ifndef LEARNING_H
#define LEARNING_H

//John Balis 2018
//for support email balisujohn@gmail.com



brain * learn( float (*f)(brain *), int inputCount, int outputCount);
brain *  multiSucc( float (*f)(brain *), int inputCount, int outputCount, int childCount);
brain * populationLearn( float (*f)(brain *), int inputCount, int outputCount, int populationCount, int generations);



#endif
