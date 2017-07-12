#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

long double alpha = 0.00004;

void desecentCost(const double dataset[][5],const double dataset_result[][1]);

int main(void){

	double dataset[96][5];
	double dataset_result[96][1];
	double temp;

	ifstream fin;
	fin.open("dataset.txt");

	for(int i = 0 ; i < 96 ; i++){
		for(int j = 0 ; j < 6 ; j++){
			if(j == 0){
				fin >> temp;
				dataset[i][j] = 1.0;
			}
			else if(j == 5){
				fin >> temp;
				dataset_result[i][0] = temp;
			}
			else{
				fin >> temp;
				dataset[i][j] = temp;
			}
		}
	}
	fin.close();


	desecentCost(dataset,dataset_result);
	
	return 0;
}

void desecentCost(const double dataset[][5],const double dataset_result[][1]){
	long double t0 = 0.0, t1 = 0.0, t2 = 0.0, t3 = 0.0, t4 = 0.0;
	long double temp_0, temp_1, temp_2, temp_3, temp_4;
	double cur_cost, pre_cost = 0.0, h_theta_minus_y;

	while(true){
		cur_cost = 0.0;
		for(int i = 0 ; i < 96 ; i++){
			cur_cost += pow(((t0*dataset[i][0] + t1*dataset[i][1] + t2*dataset[i][2] + t3*dataset[i][3] + 
				t4*dataset[i][4]) - dataset_result[i][0]),2);
		}
		cur_cost = (1.0/2*96);

		if(pre_cost == 0)
			pre_cost = cur_cost;

		temp_0 = 0; temp_1 = 0; temp_2 = 0; temp_3 = 0; temp_4 = 0; 
		for(int i = 0 ; i < 96 ; i++){
			temp_0 += (alpha/96)*((t0*dataset[i][0] + t1*dataset[i][1] + t2*dataset[i][2] + t3*dataset[i][3] + 
				t4*dataset[i][4]) - dataset_result[i][0])*dataset[i][0];
			temp_1 += (alpha/96)*((t0*dataset[i][0] + t1*dataset[i][1] + t2*dataset[i][2] + t3*dataset[i][3] + 
				t4*dataset[i][4]) - dataset_result[i][0])*dataset[i][1];
			temp_2 += (alpha/96)*((t0*dataset[i][0] + t1*dataset[i][1] + t2*dataset[i][2] + t3*dataset[i][3] + 
				t4*dataset[i][4]) - dataset_result[i][0])*dataset[i][2];
			temp_3 += (alpha/96)*((t0*dataset[i][0] + t1*dataset[i][1] + t2*dataset[i][2] + t3*dataset[i][3] + 
				t4*dataset[i][4]) - dataset_result[i][0])*dataset[i][3];
			temp_4 += (alpha/96)*((t0*dataset[i][0] + t1*dataset[i][1] + t2*dataset[i][2] + t3*dataset[i][3] + 
				t4*dataset[i][4]) - dataset_result[i][0])*dataset[i][4];
		}

		cout<< temp_0<<" "<<temp_1<<" "<<temp_2<<" "<<temp_3<<" "<<temp_4<<endl;
		cout<<endl;
		t0 = t0 - temp_0; t1 = t1 - temp_1; t2 = t2 - temp_2; t3 = t3 - temp_3; t4 = t4 - temp_4;

		cout<< "pre_cost = "<<pre_cost<<" , cur_cost = "<<cur_cost<<endl;
		cout<< "theta0 = "<<t0<<" , theta1 = "<<t1<<" , theta2 = "<<t2<<" , theta3 = "<<t3<<" , theta4 = "<<t4<<endl;
		cout<<endl;
	}
		
}












