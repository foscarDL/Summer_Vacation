/* Author : Kang Hwancheol
 * Date : 2017-07-10
 */
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include "Matrix.h"
#include "Vector.h"
#include "Transform.h"
#include "Operator.h"

using namespace std;

class Linear_Regression {
private :
	int size_of_training_data; // m
	int size_of_features; // n
	double hypothesis;
	foscar::Vector theta_vec;
	foscar::Vector input_vec;
	foscar::Matrix input_mat;
	double cost_func;

	Linear_Regression();
	void input_from_txt(const char* filename);

public :
	Linear_Regression(int n);
	void gradient_descent(double learning_rate);
	void mean_normalize();
	void normal_equation();
	int get_Size_of_training_data();
	int get_Size_of_features();
	void train(const char* filename);
	void
};

int main(int argc, char* argv[]) {

}

Linear_Regression::Linear_Regression(int n) {

}
void Linear_Regression::gradient_descent(double learning_rate) {

}
void Linear_Regression::mean_normalize() {

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
