#生成main
main:main.o add.o
	gcc main.o add.o -o main
#生成main.o&add.o
main.o:main.c
	gcc -c main.c

add.o:add.c add.h
	gcc -c add.c

clean:
	rm -rf *.o main

