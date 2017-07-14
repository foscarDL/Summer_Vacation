/*
 * Main.cpp
 *
 *  Created on: 2017. 7. 14.
 *      Author: Hwancheol
 */

#include "Matrix.h"
#include "Logistic_Regression.h"

#define INPUT_DATA_FILE 	"input_data.txt"
#define TEST_DATA_FILE 		"test_data.txt"
#define LEARNING_RATE 		0.0003

int main(int argc, char* argv[]) {
	Logistic_Regression model = Logistic_Regression();
	model.train(INPUT_DATA_FILE);
	model.gradient_descent(LEARNING_RATE);
	model.measure_accuracy(TEST_DATA_FILE);
}



