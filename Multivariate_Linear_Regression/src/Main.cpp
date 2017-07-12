/* Author : Kang Hwancheol
 * Date : 2017-07-10
 */
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <numeric>

#include "Matrix.h"
#include "Linear_Regression.h"

using namespace std;

#define INPUT_DATA_FILE 	"input_data.txt"
#define TEST_DATA_FILE 		"test_data.txt"
#define LEARNING_RATE 		0.0003 			// with mean normalize
//#define LEARNING_RATE		0.0000063		// without mean normalize

int main(int argc, char* argv[]) {
	Linear_Regression model = Linear_Regression();
	model.train(INPUT_DATA_FILE);
	model.gradient_descent(LEARNING_RATE);
	model.measure_accuracy(TEST_DATA_FILE);
}



