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

int main(int argc, char* argv[]) {
	Linear_Regression model = Linear_Regression();
	model.train("input_data.txt");
	model.gradient_descent(0.0003); // with mean normalize
	//model.gradient_descent(0.0000063); // with no mean normalize
	model.measure_accuracy("test_data.txt");
}



