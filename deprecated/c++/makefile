
control: control.o brain.o cJSON.o utils.o
	g++ -o control  cJSON.o utils.o brain.o  control.o 
control.o: control.cpp
	g++ -c -o control.o control.cpp

brain.o:  ../c/brain.c  
	gcc  -c -o brain.o ../c/brain.c  -g  -std=c11 -I. -lm
cJSON.o:  ../c/cJSON/cJSON.c  
	gcc  -c -o cJSON.o  ../c/cJSON/cJSON.c   -g  -std=c11 -I. -lm
utils.o:  ../c/utils.c  
	gcc  -c -o utils.o ../c/utils.c  -g  -std=c11 -I. -lm



