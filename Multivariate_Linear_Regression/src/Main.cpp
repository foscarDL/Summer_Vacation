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
private :
	int size_of_training_data; // m
	int size_of_features; // n

	vector<double> theta_vec;
	vector<double> input_vec;
	vector<double> max_val_vec;
	vector<double> min_val_vec;
	vector<double> average_vec;
	foscar::Matrix input_mat;

	double calculate_hypothesis(vector<double> input, vector<double> theta);
	double calculate_cost_func(vector<double> theta);
	double calculate_dif_cost_func(vector<double> theta, int index);
	void input_from_txt(const char* filename);
	void calculate_max_min_val(int index, int row, double* mat_array);
public :
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

}

Linear_Regression::Linear_Regression() : size_of_features(0), size_of_training_data(0) {}

double Linear_Regression::calculate_cost_func(vector<double> theta) {
	double cost_func_val = 0.f;
	for(int i = 0; i < size_of_training_data; i++) {
		vector<double> x_vec(size_of_features);
		x_vec[0] = 1.f;
		for(int j = 1; j < size_of_features; j++) {
			x_vec[j] = input_mat.getValue(i, j);
		}
		cost_func_val += pow((calculate_hypothesis(x_vec, theta) - input_mat.getValue(i, size_of_features)), 2.f);
	}
	cost_func_val /= 2 * size_of_training_data;
	return cost_func_val;
}
double Linear_Regression::calculate_dif_cost_func(vector<double> theta, int index) {
	double cost_func_val = 0.f;
		for(int i = 0; i < size_of_training_data; i++) {
			vector<double> x_vec(size_of_features);
			x_vec[0] = 1.f;
			for(int j = 1; j < size_of_features; j++) {
				x_vec[j] = input_mat.getValue(i, j);
			}
			cost_func_val += (calculate_hypothesis(x_vec, theta) - input_mat.getValue(i, size_of_features)) * x_vec[index];
		}
		cost_func_val /= size_of_training_data;
		return cost_func_val;
}
double Linear_Regression::calculate_hypothesis(vector<double> input, vector<double> theta) {
	return inner_product(theta.begin(), theta.end(), input.begin(), 0);
}
void Linear_Regression::gradient_descent(double learning_rate) {
	while(true) {
		double pre_cost = calculate_cost_func(theta_vec);
		vector<double> temp(size_of_features);
		for(int i = 0; i < size_of_features; i++) {
			temp[i] = theta_vec[i] - learning_rate * (1 / size_of_training_data) * calculate_dif_cost_func(theta_vec, i);
		}
		theta_vec = temp;
		if(calculate_cost_func(theta_vec) < pre_cost)
			break;
	}
}
void Linear_Regression::mean_normalize() {
	for(int i = 1; i < size_of_features; i++)
		input_vec[i] = (input_vec[i] - average_vec[i]) / (max_val_vec[i] - min_val_vec[i]);
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

}
void Linear_Regression::measure_accuracy(vector<double> data_for_measurement) {

}
void Linear_Regression::input_from_txt(const char* filename) {
	ifstream input;
	char *temp;

	input.open(filename);

	input.getline(temp, 10);
	size_of_features = atoi(temp) + 1;
	input_vec = vector<double>(size_of_features);
	theta_vec = vector<double>(size_of_features);
	min_val_vec = vector<double>(size_of_features);
	max_val_vec = vector<double>(size_of_features);
	bool init_flag = true;
	temp = "";
	input.getline(temp, 10);
	size_of_training_data = atoi(temp);
	input_mat = foscar::Matrix(size_of_features+1, size_of_training_data);
	double* mat_array = new double[(size_of_features+1) * size_of_training_data];
	for (int i = 0; i < size_of_training_data; i++) {
		temp = "";
		char* ptr;
		input.getline(temp, 1024);
		ptr = strtok(temp, " ");
		mat_array[i*size_of_features + 0] = 1.f;
		min_val_vec[0] = 1.f;
		max_val_vec[0] = 1.f;
		mat_array[i*size_of_features + 1] = atof(ptr);
		if(init_flag) {
			min_val_vec[1] = mat_array[i*size_of_features + 1];
			max_val_vec[1] = mat_array[i*size_of_features + 1];
			init_flag = false;
		}
		calculate_max_min_val(1, i, mat_array);
		for (int j = 2; j <= size_of_features; j++) {
			ptr = strtok(NULL, " ");
			mat_array[i*size_of_features + j] = atof(ptr);
			if(j != size_of_features)
				calculate_max_min_val(j, i, mat_array);
		}
	}
	input_mat.setValue(mat_array, size_of_features, size_of_training_data);
	average_vec[0] = 1.f;
	for(int i = 1; i < size_of_features; i++) {
		for(int j = 0; j < size_of_training_data; j++)
			average_vec[i] += input_mat.getValue(i, j);
		average_vec[i] /= size_of_training_data;
	}
	input.close();
}
void Linear_Regression::calculate_max_min_val(int index, int row, double* mat_array) {
	if(min_val_vec[index] > mat_array[row*size_of_features + index])
			min_val_vec[index] = mat_array[row*size_of_features + index];
	if(max_val_vec[index] < mat_array[row*size_of_features + index])
			max_val_vec[index] = mat_array[row*size_of_features + index];
}
