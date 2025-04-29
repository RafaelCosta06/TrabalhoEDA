all: prog

funcoes.o: funcoes.h funcoes.c   
	gcc -c funcoes.c

ecra.o: ecra.h ecra.c
	gcc -c ecra.c

prog: main.c funcoes.o ecra.o 	
	gcc main.c funcoes.o ecra.o -o prog

run: 
	./prog 

clean: 
	rm *.o prog
