output: main.o lib.a
	gcc main.o lib.a -o output

main.o: main.c
	gcc -c main.c

lib.a: SkipList.o SkipList.h
	ar -rsc lib.a SkipList.o
	
SkipList.o:
	gcc -c SkipList.c

clean:
	rm *.o *.a *.exe