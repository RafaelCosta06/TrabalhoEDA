all: prog

grafos.o: grafos.h grafos.c   
	gcc -c grafos.c


prog: main.c grafos.o 	
	gcc main.c grafos.o -o prog

run: 
	./prog 

clean: 
	rm *.o prog