
myexe: main.o a.o b.o
	gcc main.o a.o b.o -o myexe

main.o: main.c
	gcc -c main.c
	
a.o: a.c a.h
	gcc -c a.c 

b.o: b.c b.h
	gcc -c b.c
	
clean:
	rm *.o 
	rm myexe








