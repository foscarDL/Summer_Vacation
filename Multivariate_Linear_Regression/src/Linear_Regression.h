/* Author : Kang Hwancheol
 * Date : 2017-07-13
 */
 
 #ifndef LINEAR_REGRESSION_H
 #define LINEAR_REGRESSION_H
 
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
#include <numeric>

#include "Matrix.h"

using namespace std;

class Linear_Regression {
private:
	int size_of_training_data; // m
	int size_of_features; // n

	vector<double> theta_vec;
	vector<double> max_val_vec;
	vector<double> min_val_vec;
	vector<double> average_vec;
	foscar::Matrix input_mat;
	foscar::Matrix test_mat;

	double calculate_hypothesis(vector<double> input, vector<double> theta);
	double calculate_cost_func(vector<double> theta);
	double calculate_dif_cost_func(vector<double> theta, int index);
	void input_from_txt(const char* filename);
	void calculate_max_min_val(int index, int row, double* mat_array);
	void mean_normalize(int input_spec);
public:
	Linear_Regression();
	void gradient_descent(double learning_rate);
	void normal_equation();
	int get_Size_of_training_data();
	int get_Size_of_features();
	void train(const char* filename);
	void measure_accuracy(const char* filename);
	void measure_accuracy(vector<double> data_for_measurement);
};
#endif

