#ifndef WORLD_H
#define WORLD_H


#define boardSize 10


struct object{
	int type;
} typedef object;

struct zone{
	int objCount;
	object * objects;
}typedef zone;

struct world{
	zone zones[boardSize][boardSize];

}typedef world;



world * generateWorld();
void printWorldPop(world * w);
void initializeBasicWorld(world * w);


#endif
