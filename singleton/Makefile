all:main
main:main.o a.o
	g++ -o main main.o a.o
main.o:main.cpp a.h
	g++ -c main.cpp
a.o:a.cpp a.h
	g++ -c a.cpp