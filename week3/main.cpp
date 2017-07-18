#include "logistic_regression.h"

int main (int argc, char* argv[]){

	logistic_regression trainning = logistic_regression();
	trainning.load_data_file();
	trainning.calc_min_J();

	return 0;
}