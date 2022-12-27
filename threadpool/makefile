all:main
main:main.o threadpool.o
	gcc -o main main.o threadpool.o
mian.o:main.c threadpool.h
	gcc -c main.cpp -l pthread
threadpool.o:threadpool.c threadpool.h
	gcc -c threadpool.c -l pthread