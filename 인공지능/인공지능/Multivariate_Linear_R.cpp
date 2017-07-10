#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

int m=96;
int n=5;
double hypothesis;
double cost;
vector<double> theta(n);
vector<double> x(n);

void main(){

	ifstream fin;
	int input_val;
	fin.open("data.txt");
	
	vector<int> X(n);	
	int Y;


	for(int i=0; i<m; i++){
		fin >> input_val;
		fin >> input_val;
		X1.push_back(input_val);
		fin >> input_val;
		X2.push_back(input_val);
		fin >> input_val;
		X3.push_back(input_val);
		fin >> input_val;
		X4.push_back(input_val);
		fin >> input_val;
		Y.push_back(input_val);
	}

}

double costFunction(int x1, int x2, int x3, int x4){
	hypothesis = theta[0] 
	+ theta[1] * x[1] 
	+ theta[2] * x[2]
	+ theta[3] * x[3]
	+ theta[4] * x[4];
	
	for(int a = 0; a<n; a++){

		}

	cost=-(1/m)*
}

