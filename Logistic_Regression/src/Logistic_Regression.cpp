/*
 * Logistic_Regression.cpp
 *
 *  Created on: 2017. 7. 14.
 *      Author: Hwancheol
 */

#include "Logistic_Regression.h"

Logistic_Regression::Logistic_Regression() :
		size_of_features(0), size_of_training_data(0), size_of_class(0),
		theta_vec(0), max_val_vec(0), min_val_vec(0), average_vec(0),
		temp_class_vec(0), classes(0), mat_array(0)
{}
Logistic_Regression::~Logistic_Regression() {
	delete[] classes;
	delete[] mat_array;
	delete[] theta_vec;
}
double Logistic_Regression::calculate_cost_func(vector<double> theta ,int c) {
	double cost_func_val = 0.f;
	int y = 0;
	for (int i = 0; i < size_of_training_data; i++) {
		vector<double> x_vec(size_of_features + 1);
		x_vec[0] = 1.f;
		for (int j = 1; j < size_of_features; j++) {
			x_vec[j] = input_mat.getValue(i+1, j+1);
			//printf("%f ", x_vec[j]);
		}
		if(c == (int)input_mat.getValue(i+1, size_of_features+1))
			y = 1;
		if(y == 1)
			cost_func_val += -log(calculate_hypothesis(x_vec, theta));
		else
			cost_func_val += -log(1 - calculate_hypothesis(x_vec, theta));
		//printf("\n");
	}
	cost_func_val /= size_of_training_data;

	return cost_func_val;
}
double Logistic_Regression::calculate_dif_cost_func(vector<double> theta, int index, int c) {
	double cost_func_val = 0.f;
	int y = 0;
	vector<double> x_vec(size_of_features + 1);
	for (int i = 0; i < size_of_training_data; i++) {
		x_vec[0] = 1.f;
		for (int j = 1; j < size_of_features; j++) {
			x_vec[j] = input_mat.getValue(i+1, j+1);
		}
		if(c == (int)input_mat.getValue(i+1, size_of_features+1)) {
			y = 1;
		}
		cost_func_val += (calculate_hypothesis(x_vec, theta) - y) * x_vec[index];
	}
	cost_func_val /= size_of_training_data;

	return cost_func_val;
}
double Logistic_Regression::calculate_hypothesis(vector<double> input,
		vector<double> theta) {
	double hypothesis = 1.f;
	double inner_product = 0.f;
	for(int i = 0; i < size_of_features; i++) {
		inner_product += theta[i] * pow(input[i], i+1);
	}
	hypothesis /= 1 + exp(-inner_product);
	//return inner_product(theta.begin(), theta.end(), input.begin(), 0);
	return hypothesis;
}
void Logistic_Regression::gradient_descent(double learning_rate) {
	int count = 0;
	for(int c = 1; c <= size_of_class; c++) {
		while (true) {
			printf("class %d training step : %d\n",c, ++count);
			double pre_cost = calculate_cost_func(theta_vec[c-1], c);
			vector<double> temp(size_of_features + 1);
			for (int i = 0; i < size_of_features; i++) {
				temp[i] = theta_vec[c-1][i]
						- learning_rate * calculate_dif_cost_func(theta_vec[c-1], i, c);
			}
			printf("\n");
			printf("theta_vec : ");
			for (int i = 0; i < size_of_features; i++) {
				printf("%f ", temp[i]);
			}
			printf("\n");
			printf("cost : %f\n", calculate_cost_func(theta_vec[c-1], c));
			if (calculate_cost_func(temp, c) >= pre_cost)
				break;
			theta_vec[c-1] = temp;
		}
	}
}
void Logistic_Regression::mean_normalize(int input_spec) {
	int data_size;
	if(input_spec == 1)
		data_size = size_of_training_data;
	else if(input_spec == 2)
		data_size = 1;
	else {
		printf("mean_normalize parameter error\n");
		return;
	}
	double* temp_mat_array = new double[(size_of_features + 1) * data_size];
	for (int i = 0; i < data_size; i++) {
		temp_mat_array[i * (size_of_features + 1) + 0] = 1.f;
		for (int j = 1; j <= size_of_features; j++) {
			if(input_spec == 1)
				temp_mat_array[i * (size_of_features + 1) + j] = input_mat.getValue(i + 1, j + 1);
			if(input_spec == 2)
				temp_mat_array[i * (size_of_features + 1) + j] = test_mat.getValue(i + 1, j + 1);
			if (j != size_of_features) {
				temp_mat_array[i * (size_of_features + 1) + j] = (temp_mat_array[i
						* (size_of_features + 1) + j] - average_vec[j])
						/ (max_val_vec[j] - min_val_vec[j]);
			}
		}
	}
	if(input_spec == 1) {
		input_mat.setValue(temp_mat_array, data_size, size_of_features + 1);
	}
	else if(input_spec == 2) {
		test_mat.setValue(temp_mat_array, data_size, size_of_features + 1);
	}
	//input_mat.show();
	delete[] temp_mat_array;
}
int Logistic_Regression::get_Size_of_training_data() {
	return size_of_training_data;
}

int Logistic_Regression::get_Size_of_features() {
	return size_of_features;
}

int Logistic_Regression::get_Size_of_class() {
	return size_of_class;
}

void Logistic_Regression::train(const char* filename) {
	input_from_txt(filename);
	mean_normalize(1);
}
void Logistic_Regression::measure_accuracy(const char* filename) {
	ifstream input;
	char temp[1024];
	input.open(filename, ios::in);
	if (input.fail()) {
			printf("file not exists\n");
	}
	int num_of_test_data;
	input >> temp;
	num_of_test_data = atoi(temp);

	for (int i = 0; i < num_of_test_data; i++) {
		test_mat = foscar::Matrix(size_of_features + 1, num_of_test_data);
		double* temp_mat = new double[size_of_features + 1];
		temp_mat[0] = 1.f;
		for (int j = 1; j < size_of_features; j++) {
			input >> temp;
//			printf("%s ", temp);
			temp_mat[j] = atof(temp);
		}
		input >> temp;
		for(int i = 0; i < size_of_class; i++) {
			if(!strcmp(classes[i].name.c_str(), temp)) {
				temp_mat[size_of_features] = classes[i].no;
				break;
			}
		}
 		test_mat.setValue(temp_mat, 1, size_of_features + 1);
		delete[] temp_mat;
		mean_normalize(2);
		vector<double> input_line_vector(size_of_features + 2);
		//test_mat.show();
		for(int j = 1; j <= size_of_features; j++) {
			input_line_vector[j] = test_mat.getValue(1, j+1);
		}
		measure_accuracy(input_line_vector);
		input_line_vector.clear();
	}
	input.close();
}
void Logistic_Regression::measure_accuracy(vector<double> data_for_measurement) {
	vector<double> x_vec(size_of_features + 1);
	for (int i = 0; i < size_of_features; i++) {
		x_vec[i] = data_for_measurement[i];
	}
	double actual_data = data_for_measurement[size_of_features];
	double hypothesis = 0;
	int predict;
	for(int c = 1; c <= size_of_class; c++) {
		double temp = calculate_hypothesis(x_vec, theta_vec[c-1]);
		printf("hypothesis : %f\n", temp);
		if(temp > hypothesis) {
			predict = c;
		}
		hypothesis = temp;
	}
	int actual_index = (int) actual_data - 1;
	printf("predict : %s, actual_data : %s\n", classes[predict-1].name.c_str(), classes[actual_index].name.c_str());
}
void Logistic_Regression::input_from_txt(const char* filename) {
	ifstream input;
	char temp[1024];
	input.open(filename, ios::in);
	if (input.fail()) {
		printf("file not exists\n");
	}
	input >> temp;
	size_of_features = atoi(temp) + 1;
	min_val_vec = vector<double>(size_of_features + 1);
	max_val_vec = vector<double>(size_of_features + 1);
	average_vec = vector<double>(size_of_features + 1);
	bool init_flag = true;

	input >> temp;
	size_of_class = atoi(temp);
	classes = new class_map[size_of_class + 1];
	theta_vec = new vector<double>[3];
	for(int i = 0; i< size_of_class; i++)
		theta_vec[i] = vector<double>(size_of_features + 1);

	input >> temp;
	size_of_training_data = atoi(temp);
	temp_class_vec = vector<string>(size_of_training_data + 1);
	input_mat = foscar::Matrix(size_of_features + 1, size_of_training_data);
	mat_array = new double[(size_of_features + 1) * size_of_training_data];
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
		for (int j = 2; j < size_of_features; j++) {
			if (!input.eof()) {
				input >> temp;
			}
			mat_array[i * (size_of_features + 1) + j] = atof(temp);
			calculate_max_min_val(j, i, mat_array);
		}
		input >> temp;
		temp_class_vec[i] = string(temp);
	}
	set_Class();
	input_mat.setValue(mat_array, size_of_training_data, size_of_features + 1);
	average_vec[0] = 1.f;
	for (int i = 1; i < size_of_features; i++)
		average_vec[i] = 0.f;
	for (int i = 1; i < size_of_features; i++) {
		for (int j = 0; j < size_of_training_data; j++)
			average_vec[i] += input_mat.getValue(j+1, i+1);
		average_vec[i] /= size_of_training_data;
	}
	input.close();
}

void Logistic_Regression::calculate_max_min_val(int index, int row,
		double* mat_array) {
	if (min_val_vec[index] > mat_array[row * (size_of_features + 1) + index])
		min_val_vec[index] = mat_array[row * (size_of_features + 1) + index];
	if (max_val_vec[index] < mat_array[row * (size_of_features + 1) + index])
		max_val_vec[index] = mat_array[row * (size_of_features + 1) + index];
}

void Logistic_Regression::set_Class() {
	vector<string>::iterator new_end;
	vector<string> unique_vec(size_of_training_data);
	unique_vec.assign(temp_class_vec.begin(), temp_class_vec.end());
	new_end = unique(unique_vec.begin(), unique_vec.end());
	unique_vec.erase(new_end, unique_vec.end());
	for(int i = 0; i < size_of_class; i++) {
		classes[i].name = unique_vec[i];
		classes[i].no = i+1;
	}
	for(int i = 0; i < size_of_training_data; i++) {
		for(int j = 0; j < size_of_class; j++) {
			if(!strcmp(classes[j].name.c_str(), temp_class_vec[i].c_str())){
				mat_array[i * (size_of_features + 1) + size_of_features] = classes[j].no;
			}
		}
	}
}



