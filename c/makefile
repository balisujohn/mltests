
all : test

test: xor.c test.c brain.c utils.c analysis.c smath.c learning.c  
	gcc -o test  smath.c learning.c xor.c test.c brain.c utils.c analysis.c  -g  -std=c11 -I. -lm

