/*
 * Logistic_Regression.h
 *
 *  Created on: 2017. 7. 14.
 *      Author: Hwancheol
 */

#ifndef SRC_LOGISTIC_REGRESSION_H_
#define SRC_LOGISTIC_REGRESSION_H_

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "Matrix.h"
using namespace std;

class Logistic_Regression {
private :
	struct class_map {
			string name;
			int no;
	};
	int size_of_training_data; // m
	int size_of_features; // n
	int size_of_class;
	vector<double> theta_vec;
	vector<double> max_val_vec;
	vector<double> min_val_vec;
	vector<double> average_vec;
	vector<string> temp_class_vec;
	class_map* classes;
	double* mat_array;
	foscar::Matrix input_mat;
	foscar::Matrix test_mat;

	double calculate_hypothesis(vector<double> input, vector<double> theta);
	double calculate_cost_func(vector<double> theta, int c);
	double calculate_dif_cost_func(vector<double> theta, int index, int c);
	void input_from_txt(const char* filename);
	void calculate_max_min_val(int index, int row, double* mat_array);
	void mean_normalize(int input_spec);
	void set_Class();

public :
	Logistic_Regression();
	~Logistic_Regression();
	void gradient_descent(double learning_rate);
	int get_Size_of_training_data();
	int get_Size_of_features();
	int get_Size_of_class();
	void train(const char* filename);
	void measure_accuracy(const char* filename);
	void measure_accuracy(vector<double> data_for_measurement);
};


#endif /* SRC_LOGISTIC_REGRESSION_H_ */
