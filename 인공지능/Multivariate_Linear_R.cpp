#include <fstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

const int m=30;
const int n=5;

Matrix<double, m, n> X;
Matrix<double, m, 1> Y;

Matrix<double, 1, n> input;

double theta[5];

double alpha = 0.00003;

void gradientDecent();
double costFunction(double theta[5]);
double* difFunction(double theta[5]);
double hypothesisFunction(Matrix<double,1,n> x, double theta[5]);



int main(){

	ifstream fin;
	int input_val;
	fin.open("data.txt");

	for(int i=0; i<m; i++){
		for(int j=0; j<n+1; j++){
			if(j==0){
				fin >> input_val;
				X(i,j)=1;
			}else if(j==n){
				fin >>input_val;
				Y(i,0) = input_val;
			}else{
				fin >> input_val;
				X(i,j)=input_val;
			}

		}
	}

	gradientDecent();
	

	system("pause");
	fin.close();
	return 0;
}

void gradientDecent(){
	double temptheta[5]={0.0};
	double precost;
	double curcost;

	for(int a=0; a<2000;a++) {
		precost = costFunction(theta);
		temptheta[0] = theta[0] - (alpha * difFunction(theta)[0]);
		temptheta[1] = theta[1] - (alpha * difFunction(theta)[1]);
		temptheta[2] = theta[2] - (alpha * difFunction(theta)[2]);
		temptheta[3] = theta[3] - (alpha * difFunction(theta)[3]);
		temptheta[4] = theta[4] - (alpha * difFunction(theta)[4]);
		for(int i=0; i<n; i++){
			theta[i]= temptheta[i];
		}
		if(a % 20 == 0) {
			cout << theta[0] << endl;
		}
	
	}
	

}

double costFunction(double theta[5]){
	double sum = 0;
	for(int i=0 ; i < m ; i++){
		sum += pow(hypothesisFunction(X.row(i),theta) - Y[i], 2);
	}
	cout<<sum/m/2<<endl;
	return  sum/m/2 ;
}

double* difFunction(double theta[5]){
	double sum0 = 0;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;
	double sum4 = 0;
	double diff[5]={0.0};
	for( int i = 0; i< m ; i++){
		sum0 += (hypothesisFunction(X.row(i), theta)-Y[i]) * X.row(i)[0];
		sum1 += (hypothesisFunction(X.row(i), theta)-Y[i]) * X.row(i)[1];
		sum2 += (hypothesisFunction(X.row(i), theta)-Y[i]) * X.row(i)[2];
		sum3 += (hypothesisFunction(X.row(i), theta)-Y[i]) * X.row(i)[3];
		sum4 += (hypothesisFunction(X.row(i), theta)-Y[i]) * X.row(i)[4];
	}
	diff[0]= sum0/m;
	diff[1]= sum1/m;
	diff[2]= sum2/m;
	diff[3]= sum3/m;
	diff[4]= sum4/m;

	return diff;
}


double hypothesisFunction(Matrix<double,1,n> x, double theta[5]){
	double hypothesis;
	hypothesis = theta[0] * x[0] + theta[1] * x[1] + theta[2] * x[2] + theta[3] * x[3] + theta[4] * x[4];
	return hypothesis;
}



