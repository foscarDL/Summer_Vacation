mlr : Main.o Matrix.o Linear_Regression.o
	g++ -lm -o mlr Main.o Matrix.o Linear_Regression.o

Main.o : Main.cpp Matrix.h Linear_Regression.h
	g++ -c Main.cpp

Matrix.o : Matrix.cpp Matrix.h
	g++ -c Matrix.cpp

Linear_Regression.o : Linear_Regression.cpp Linear_Regression.h Matrix.h
	g++ -c Linear_Regression.cpp 	