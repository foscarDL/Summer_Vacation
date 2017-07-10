mlr : Main.o Matrix.o
	g++ -lm -o mlr Main.o Matrix.o

Main.o : Main.cpp Matrix.h
	g++ -c Main.cpp

Matrix.o : Matrix.cpp Matrix.h
	g++ -c Matrix.cpp
