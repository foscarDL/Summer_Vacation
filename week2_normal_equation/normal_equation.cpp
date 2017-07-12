#include <iostream>
#include <fstream>
#include <armadillo>

using namespace std;
using namespace arma;

int main(void){

	mat X = zeros<mat>(96,5);
	mat XT;
	mat XTX;
	mat inv_XTX;
	mat y = zeros<mat>(96,1);
	mat theta;
	int temp;

	std::ifstream fin;
	fin.open("dataset.txt");

	for(int i = 0 ; i < 96 ; i++){
		X(i,0) = 1;

		for(int j = 1 ; j < 5 ; j++){
			fin >> temp;
			X(i,j) = temp;
		}

		fin >> temp;
		y(i,0) = temp;
	}

	fin.close();

	XT = strans(X);
	XTX = XT*X;
	inv_XTX = inv(XTX);
	theta = inv_XTX*XT*y;

	cout<< "θ0 = "<<theta(0,0)<<endl;
	cout<< "θ1 = "<<theta(1,0)<<endl;
	cout<< "θ2 = "<<theta(2,0)<<endl;
	cout<< "θ3 = "<<theta(3,0)<<endl;
	cout<< "θ4 = "<<theta(4,0)<<endl;

	return 0;
}
