#ifndef WORLD_H
#define WORLD_H


#define BOARD_SIZE 10


#define TYPE_HUNTER  1 
#define TYPE_AGENT  2


struct object{
	int type;
	int age;
	struct object * next;
	struct object * prev;
} typedef object;

struct zone{
	int objCount;
	object * head;
}typedef zone;

struct world{
	int agentX;
	int agentY;
	int age;
	zone zones[BOARD_SIZE][BOARD_SIZE];

}typedef world;



world * generateWorld();
void printWorldPop(world * w);
void initializeBasicWorld(world * w);
void advanceWorldState(world * w);
void removeObject(zone * z, object * o );
void appendObject(zone * z, object * o);



#endif
