FLAGS= -Wall   -ansi -pedantic   #warnings

all: assembler

assembler: utils.o castingToBinnary.o linkedList.o preAssembler.o directiveSentence.o teachingSentence.o firstRun.o secondRun.o main.o encodeLabels.o
	gcc $(FLAGS)  -o assembler utils.o castingToBinnary.o linkedList.o preAssembler.o directiveSentence.o teachingSentence.o firstRun.o secondRun.o main.o encodeLabels.o -lm

main.o: main.c linkedList.h assembler.h 
	gcc $(FLAGS) -c  main.c -lm  

utils.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c

castingToBinnary.o: castingToBinnary.c castingToBinnary.h
	gcc $(FLAGS)  -c castingToBinnary.c

linkedList.o: linkedList.c linkedList.h
	gcc $(FLAGS) -c linkedList.c

preAssembler.o: preAssembler.c assembler.h linkedList.h 
	gcc $(FLAGS) -c preAssembler.c

directiveSentence.o: directiveSentence.c linkedList.h utils.h castingToBinnary.h assembler.h
	gcc $(FLAGS) -c directiveSentence.c

teachingSentence.o: teachingSentence.c utils.h castingToBinnary.h assembler.h 
	gcc $(FLAGS) -c teachingSentence.c

firstRun.o: firstRun.c assembler.h linkedList.h utils.h 
	gcc $(FLAGS) -c firstRun.c

secondRun.o: secondRun.c assembler.h linkedList.h utils.h  castingToBinnary.h
	gcc $(FLAGS) -c secondRun.c

encodeLabels.o: encodeLabels.c assembler.h linkedList.h utils.h  castingToBinnary.h
	gcc $(FLAGS) -c encodeLabels.c



