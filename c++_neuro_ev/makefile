
all : test

# add build objects to .gitignore

test: xor.c test.c utils.c analysis.c smath.c learning.c  ./brains/brain.c ./cJSON/cJSON.c
	g++ -o test  smath.c learning.c xor.c test.c ./brains/brain.c utils.c analysis.c ./cJSON/cJSON.c  -g  -std=c++11 -I. -lm

