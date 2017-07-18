#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

class logistic_regression{
private:
	double theta[3][5];
	int	   y_result[150][3];
	double dataset[150][5];
	double rate;
	

public:
	logistic_regression();
	void load_data_file();
	double thetaTx(int thetaNum, int i);
	double h_theta_x(int thetaNum, int i);
	double par_dif_J(int thetaNum, int j);
	void gradient_descent(int thetaNum);
	void calc_min_J();
};