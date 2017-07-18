#include "logistic_regression.h"

logistic_regression::logistic_regression(){
	for(int i = 0 ; i < 150 ; i++)
		for(int j = 0 ; j < 3 ; j++)
			y_result[i][j] = 0;

	for(int i = 0 ; i< 3; i++)
		for(int j = 0 ; j < 5 ; j++)
			theta[i][j] = 0;

	rate = 0.03;
}

void logistic_regression::load_data_file(){
	char temp[100];
	ifstream fin;
	fin.open("data_set.txt");

	for(int i = 0 ; i < 150 ; i++){
		dataset[i][0] = 1;

		for(int j = 1 ; j < 5 ; j++){

			fin >> temp;
			dataset[i][j] = atof(temp);
		}

		fin >> temp;
		if((string)temp == "Iris-setosa")
			y_result[i][0] = 1;
		else if((string)temp == "Iris-versicolor")
			y_result[i][1] = 1;
		else
			y_result[i][2] = 1;
	}
	fin.close();
}

double logistic_regression::thetaTx(int thetaNum, int i){

	double z = theta[thetaNum][0]*dataset[i][0] + theta[thetaNum][1]*dataset[i][1] + 
		theta[thetaNum][2]*dataset[i][2] + theta[thetaNum][3]*dataset[i][3] + theta[thetaNum][4]*dataset[i][4];

	return z;
}

double logistic_regression::h_theta_x(int thetaNum, int i){
	double h = 1.0 / (1.0 + exp(-thetaTx(thetaNum, i)));

	return h;
}

double logistic_regression::par_dif_J(int thetaNum, int j){
	double result = 0;

	for(int i = 0 ; i < 150 ; i++){
		result += ( h_theta_x(thetaNum, i) - y_result[i][thetaNum] ) * dataset[i][j];
	}

	return result/150.0;
}

void logistic_regression::gradient_descent(int thetaNum){
	double t0,t1,t2,t3,t4;

	t0 = theta[thetaNum][0] - rate * par_dif_J(thetaNum, 0);
	t1 = theta[thetaNum][1] - rate * par_dif_J(thetaNum, 1);
	t2 = theta[thetaNum][2] - rate * par_dif_J(thetaNum, 2);
	t3 = theta[thetaNum][3] - rate * par_dif_J(thetaNum, 3);
	t4 = theta[thetaNum][4] - rate * par_dif_J(thetaNum, 4);

	theta[thetaNum][0] = t0;
	theta[thetaNum][1] = t1;
	theta[thetaNum][2] = t2;
	theta[thetaNum][3] = t3;
	theta[thetaNum][4] = t4;
}

void logistic_regression::calc_min_J(){
	while(true){
		gradient_descent(0);
		gradient_descent(1);
		gradient_descent(2);

		cout<<"=====theta======"<<endl;
		for(int i = 0 ; i < 3 ; i++){
			for(int j = 0 ; j < 5 ; j++){
				cout<<theta[i][j]<<" ";
			}
			cout<<endl;
			cout<<endl;
		}


	}
}













