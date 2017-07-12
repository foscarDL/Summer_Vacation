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

	double calculate_hypothesis(vector<double> input, vector<double> theta);
	double calculate_cost_func(vector<double> theta);
	double calculate_dif_cost_func(vector<double> theta, int index);
	void input_from_txt(const char* filename);
	void calculate_max_min_val(int index, int row, double* mat_array);
public:
	Linear_Regression();
	void gradient_descent(double learning_rate);
	void mean_normalize();
	void normal_equation();
	int get_Size_of_training_data();
	int get_Size_of_features();
	void train(const char* filename);
	void measure_accuracy(const char* filename);
	void measure_accuracy(vector<double> data_for_measurement);
};

int main(int argc, char* argv[]) {
	Linear_Regression model = Linear_Regression();
	model.train("input_data.txt");
	model.mean_normalize();
	model.gradient_descent(0.3);
	model.measure_accuracy("test_data.txt");
}

Linear_Regression::Linear_Regression() :
		size_of_features(0), size_of_training_data(0), theta_vec(0), max_val_vec(
				0), min_val_vec(0), average_vec(0) {
}
double Linear_Regression::calculate_cost_func(vector<double> theta) {
	double cost_func_val = 0.f;
	for (int i = 0; i < size_of_training_data; i++) {
		vector<double> x_vec(size_of_features);
		x_vec[0] = 1.f;
		for (int j = 1; j < size_of_features; j++) {
			x_vec[j] = input_mat.getValue(i, j);
			//printf("%f ", x_vec[j]);
		}
		//printf("\n");
		cost_func_val += pow(
				(calculate_hypothesis(x_vec, theta)
						- input_mat.getValue(i, size_of_features)), 2.f);
	}
	cost_func_val /= 2 * size_of_training_data;
	printf("cost_func_val : %f\n", cost_func_val);
	return cost_func_val;
}
double Linear_Regression::calculate_dif_cost_func(vector<double> theta,
		int index) {
	double cost_func_val = 0.f;
	for (int i = 0; i < size_of_training_data; i++) {
		vector<double> x_vec(size_of_features);
		x_vec.push_back(1.f);
		for (int j = 1; j < size_of_features; j++) {
			x_vec.push_back(input_mat.getValue(i, j));
		}
		cost_func_val += (calculate_hypothesis(x_vec, theta)
				- input_mat.getValue(i, size_of_features)) * x_vec[index];
	}
	cost_func_val /= size_of_training_data;
	return cost_func_val;
}
double Linear_Regression::calculate_hypothesis(vector<double> input,
		vector<double> theta) {
	return inner_product(theta.begin(), theta.end(), input.begin(), 0);
}
void Linear_Regression::gradient_descent(double learning_rate) {
	while (true) {
		input_mat.show();
		double pre_cost = calculate_cost_func(theta_vec);
		vector<double> temp(size_of_features);
		printf("pre theta_vec : ");
		for (int i = 0; i < size_of_features; i++) {
			printf("%f ", theta_vec[i]);
			temp[i] = theta_vec[i]
					- learning_rate * (1 / size_of_training_data)
							* calculate_dif_cost_func(theta_vec, i);
		}
		printf("\n");
		printf("cur theta_vec : ");
		for (int i = 0; i < size_of_features; i++) {
			printf("%f ", temp[i]);
		}
		printf("\n");
		theta_vec = temp;
		if (calculate_cost_func(theta_vec) >= pre_cost)
			break;
	}
}
void Linear_Regression::mean_normalize() {
	double* mat_array = new double[(size_of_features + 1)
			* size_of_training_data];
	for (int i = 0; i < size_of_training_data; i++) {
		mat_array[i * (size_of_features + 1) + 0] = 1.f;
		for (int j = 1; j <= size_of_features; j++) {
			mat_array[i * (size_of_features + 1) + j] = input_mat.getValue(
					i + 1, j + 1);
			if (j != size_of_features) {
				mat_array[i * (size_of_features + 1) + j] = (mat_array[i
						* (size_of_features + 1) + j] - average_vec[j])
						/ (max_val_vec[j] - min_val_vec[j]);
			}
		}
	}
	input_mat.setValue(mat_array, size_of_training_data, size_of_features + 1);
	//input_mat.show();
	delete[] mat_array;
}
void Linear_Regression::normal_equation() {

}
int Linear_Regression::get_Size_of_training_data() {
	return size_of_training_data;
}

int Linear_Regression::get_Size_of_features() {
	return size_of_features;
}
void Linear_Regression::train(const char* filename) {
	input_from_txt(filename);
}
void Linear_Regression::measure_accuracy(const char* filename) {
	ifstream input;
	char *temp;
	int num_of_test_data;
	input.open(filename);
	input >> temp;
	num_of_test_data = atoi(temp);

	for (int i = 0; i < num_of_test_data; i++) {
		vector<double> input_line_vector(size_of_features + 1);
		input_line_vector[0] = 1.f;
		for (int j = 1; j <= size_of_features; j++) {
			input >> temp;
			input_line_vector[j] = atof(temp);
		}
		measure_accuracy(input_line_vector);
		input_line_vector.clear();
	}
	input.close();
}
void Linear_Regression::measure_accuracy(vector<double> data_for_measurement) {
	vector<double> x_vec(size_of_features);
	for (int i = 0; i < size_of_features; i++) {
//		printf("x_vec[%d] : %f\n", i,data_for_measurement[i]);
		x_vec.push_back(data_for_measurement[i]);
	}
	double actual_data = data_for_measurement[size_of_features];
	double hypothesis = calculate_hypothesis(x_vec, theta_vec);
	double error = fabs((hypothesis - actual_data) / actual_data) * 100;
	printf("hypothesis : %f, actual_data : %f\nerror : %f\n", hypothesis,
			actual_data, error);
}
void Linear_Regression::input_from_txt(const char* filename) {
	ifstream input;
	char temp[1024];
	input.open(filename, ios::in);
	if (input.fail()) {
		printf("file not exists\n");
	}
	input >> temp;
	size_of_features = atoi(temp) + 1;
	theta_vec = vector<double>(size_of_features);
	min_val_vec = vector<double>(size_of_features);
	max_val_vec = vector<double>(size_of_features);
	average_vec = vector<double>(size_of_features);
	bool init_flag = true;

	input >> temp;
	size_of_training_data = atoi(temp);
	input_mat = foscar::Matrix(size_of_features + 1, size_of_training_data);
	double* mat_array = new double[(size_of_features + 1)
			* size_of_training_data];
	for (int i = 0; i < size_of_training_data; i++) {
		input >> temp;
		mat_array[i * (size_of_features + 1) + 0] = 1.f;
		min_val_vec[0] = 1.f;
		max_val_vec[0] = 1.f;
		mat_array[i * (size_of_features + 1) + 1] = atof(temp);
		if (init_flag) {
			min_val_vec[1] = mat_array[i * (size_of_features + 1) + 1];
			max_val_vec[1] = mat_array[i * (size_of_features + 1) + 1];
			init_flag = false;
		}
		calculate_max_min_val(1, i, mat_array);
		for (int j = 2; j <= size_of_features; j++) {
			if (!input.eof()) {
				input >> temp;
			}
			mat_array[i * (size_of_features + 1) + j] = atof(temp);
			if (j != size_of_features)
				calculate_max_min_val(j, i, mat_array);
		}
	}
	input_mat.setValue(mat_array, size_of_training_data, size_of_features + 1);
	average_vec[0] = 1.f;
	for (int i = 1; i < size_of_training_data; i++)
		average_vec.push_back(0.f);
	for (int i = 1; i < size_of_features; i++) {
		for (int j = 0; j < size_of_training_data; j++)
			average_vec[i] += input_mat.getValue(j, i);
		average_vec[i] /= size_of_training_data;
	}
	input.close();
//	input_mat.show();
	delete[] mat_array;
}
void Linear_Regression::calculate_max_min_val(int index, int row,
		double* mat_array) {
	if (min_val_vec[index] > mat_array[row * (size_of_features + 1) + index])
		min_val_vec[index] = mat_array[row * (size_of_features + 1) + index];
	if (max_val_vec[index] < mat_array[row * (size_of_features + 1) + index])
		max_val_vec[index] = mat_array[row * (size_of_features + 1) + index];
}
