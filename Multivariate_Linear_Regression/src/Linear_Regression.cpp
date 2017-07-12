#include "Linear_Regression.h"

Linear_Regression::Linear_Regression() :
		size_of_features(0), size_of_training_data(0), theta_vec(0), max_val_vec(
				0), min_val_vec(0), average_vec(0) {
}
double Linear_Regression::calculate_cost_func(vector<double> theta) {
	double cost_func_val = 0.f;
	for (int i = 0; i < size_of_training_data; i++) {
		vector<double> x_vec(size_of_features + 1);
		x_vec[0] = 1.f;
		for (int j = 1; j < size_of_features; j++) {
			x_vec[j] = input_mat.getValue(i+1, j+1);
			//printf("%f ", x_vec[j]);
		}
		//printf("\n");
		cost_func_val += pow(
				(calculate_hypothesis(x_vec, theta)
						- input_mat.getValue(i+1, size_of_features+1)), 2.f);
	}
	cost_func_val /= 2 * size_of_training_data;

	return cost_func_val;
}
double Linear_Regression::calculate_dif_cost_func(vector<double> theta,
		int index) {
	double cost_func_val = 0.f;
	vector<double> x_vec(size_of_features + 1);
	for (int i = 0; i < size_of_training_data; i++) {

		x_vec[0] = 1.f;
		for (int j = 1; j < size_of_features; j++) {
			x_vec[j] = input_mat.getValue(i+1, j+1);
		}
		cost_func_val += (calculate_hypothesis(x_vec, theta)
				- input_mat.getValue(i+1, size_of_features+1)) * x_vec[index];
	}
	return cost_func_val;
}
double Linear_Regression::calculate_hypothesis(vector<double> input,
		vector<double> theta) {
	double hypothesis = 0.f;
	for(int i = 0; i < size_of_features; i++) {
		hypothesis += theta[i] * input[i];
	}
	//return inner_product(theta.begin(), theta.end(), input.begin(), 0);
	return hypothesis;
}
void Linear_Regression::gradient_descent(double learning_rate) {
	int count = 0;
	while (true) {
		printf("training step : %d\n", ++count);
		double pre_cost = calculate_cost_func(theta_vec);
		vector<double> temp(size_of_features+1);
		for (int i = 0; i < size_of_features; i++) {
			temp[i] = theta_vec[i]
					- learning_rate	* calculate_dif_cost_func(theta_vec, i);
		}
		printf("\n");
		printf("theta_vec : ");
		for (int i = 0; i < size_of_features; i++) {
			printf("%f ", temp[i]);
		}
		printf("\n");
		printf("cost : %f\n", calculate_cost_func(theta_vec));
		if (calculate_cost_func(temp) > pre_cost)
			break;
		theta_vec = temp;
	}
}
void Linear_Regression::mean_normalize(int input_spec) {
	int data_size;
	if(input_spec == 1)
		data_size = size_of_training_data;
	else if(input_spec == 2)
		data_size = 1;
	else {
		printf("mean_normalize parameter error\n");
		return;
	}
	double* mat_array = new double[(size_of_features + 1) * data_size];
	for (int i = 0; i < data_size; i++) {
		mat_array[i * (size_of_features + 1) + 0] = 1.f;
		for (int j = 1; j <= size_of_features; j++) {
			if(input_spec == 1)
				mat_array[i * (size_of_features + 1) + j] = input_mat.getValue(i + 1, j + 1);
			if(input_spec == 2)
				mat_array[i * (size_of_features + 1) + j] = test_mat.getValue(i + 1, j + 1);
			if (j != size_of_features) {
				mat_array[i * (size_of_features + 1) + j] = (mat_array[i
						* (size_of_features + 1) + j] - average_vec[j])
						/ (max_val_vec[j] - min_val_vec[j]);
			}
		}
	}
	if(input_spec == 1) {
		input_mat.setValue(mat_array, data_size, size_of_features + 1);
	}
	else if(input_spec == 2) {
		test_mat.setValue(mat_array, data_size, size_of_features + 1);
	}

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
	mean_normalize(1);
}
void Linear_Regression::measure_accuracy(const char* filename) {
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
		for (int j = 1; j <= size_of_features; j++) {
			input >> temp;
//			printf("%s ", temp);
			temp_mat[j] = atof(temp);
		}
		test_mat.setValue(temp_mat, 1, size_of_features + 1);
		delete[] temp_mat;
		//test_mat.show();
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
void Linear_Regression::measure_accuracy(vector<double> data_for_measurement) {
	vector<double> x_vec(size_of_features + 1);
	for (int i = 0; i < size_of_features; i++) {
		//printf("x_vec[%d] : %f\n", i,data_for_measurement[i]);
		x_vec[i] = data_for_measurement[i];
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
	theta_vec = vector<double>(size_of_features + 1);
	min_val_vec = vector<double>(size_of_features + 1);
	max_val_vec = vector<double>(size_of_features + 1);
	average_vec = vector<double>(size_of_features + 1);
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
	for (int i = 1; i < size_of_features; i++)
		average_vec[i] = 0.f;
	for (int i = 1; i < size_of_features; i++) {
		for (int j = 0; j < size_of_training_data; j++)
			average_vec[i] += input_mat.getValue(j+1, i+1);
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

