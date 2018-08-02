
all : xor addition

xor: xor.c test.c brain.c utils.c analysis.c 
	gcc -o xor  xor.c test.c brain.c utils.c analysis.c   -std=c11 -I. -lm
addition: smath.c brain.c utils.c 
	gcc -o addition smath.c brain.c utils.c -std=c11 -I. -lm

