shell: main.o
	gcc main.o -o shell
main.o: main.c
	gcc -c main.c -o main.o
clean:
	rm *.o shell