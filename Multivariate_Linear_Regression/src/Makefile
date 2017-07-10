mlr : Main.o Vector.o Matrix.o Transform.o Operator.o
	g++ -lm -o mlr Main.o Vector.o Matrix.o Transform.o Operator.o

Main.o : Main.cpp Vector.h Matrix.h Transform.h Operator.h
	g++ -c Main.cpp
	
Vector.o : Vector.cpp Vector.h
	g++ -c Vector.cpp
	
Matrix.o : Matrix.cpp Matrix.h Vector.h
	g++ -c Matrix.cpp

Operator.o : Operator.cpp Operator.h Matrix.h Vector.h

Transform.o : Transform.cpp Transform.h Matrix.h Vector.h Operator.h
