lr : Main.o Matrix.o Logistic_Regression.o
	g++ -lm -o lr Main.o Matrix.o Logistic_Regression.o

Main.o : Main.cpp Matrix.h Logistic_Regression.h
	g++ -c Main.cpp

Matrix.o : Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

Logistic_Regression.o : Logistic_Regression.cpp Logistic_Regression.h Matrix.h
	g++ -c Logistic_Regression.cpp 	