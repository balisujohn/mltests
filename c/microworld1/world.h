#ifndef WORLD_H
#define WORLD_H


#define BOARD_SIZE 7



#define TYPE_ANY 0
#define TYPE_HUNTER  1 
#define TYPE_AGENT  2

#define ACTION_MOVE_RIGHT 0
#define ACTION_MOVE_LEFT 1
#define ACTION_MOVE_FORWARD 2
#define ACTION_MOVE_BACK 3
#define ACTION_TURN_RIGHT 4
#define ACTION_TURN_LEFT 5


#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

#include"../brains/brain.h"

 
//John Balis 2018
//for support email balisujohn@gmail.com



struct agentInfo{
int direction;
int health;
} typedef agentInfo;


struct object{
	int type;
	int actuation;
	int age;
	void * objectInfo;
	struct object * next;
	struct object * prev;
} typedef object;

struct zone{
	int objCount;
	object * head;
}typedef zone;

struct movementQueueNode{
	zone  * curr;
	zone * dest;
	object * o;	
	struct movementQueueNode * next;
} typedef movementQueueNode;


struct world{
	int agentX;
	int agentY;
	int age;
	int dead;
	movementQueueNode movementQueueHead;
	zone zones[BOARD_SIZE][BOARD_SIZE];

}typedef world;



world * generateWorld();
void printWorldPop(world * w);
void printWorldInfo(world * w);
void initializeBasicWorld(world * w);
void freeWorld(world * w);
void advanceWorldState(world * w, brain * b);
void removeObject(zone * z, object * o );
void appendObject(zone * z, object * o);
movementQueueNode * popMovement(world * w);
void pushMovement(world * w, zone * curr, zone * dest, object * o);
float randFloat(); // what is this
int randRange(int limit);

#endif
