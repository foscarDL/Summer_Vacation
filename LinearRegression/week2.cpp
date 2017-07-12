#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#define CASE 30
#define FEATURE 5

class LinearRegression
{
public:
  std::vector<double> x;
  std::vector<double> y;
  std::vector<double> theta;
  double x_[CASE][FEATURE];

  LinearRegression();
  double hyphothesis(int n);
  double cost_function();
  double d_cost_function(int n);
  void gradient_descent();
  void new_theta();
  void fillMat(std::ifstream& in);
  const double learning_rate = 0.078;

  double test();
};

LinearRegression::LinearRegression() : x(CASE), y(CASE), theta(FEATURE)
{

}

double LinearRegression::hyphothesis(int n)
{
  double h_x = 0.0;
  for(int i=0; i<FEATURE; ++i)
    h_x += (theta[i]*x_[n][i]);
  //std::cout << "h_x : " << h_x << std::endl;
  return h_x;
}

double LinearRegression::cost_function()
{
  double sum=0.0;
  double cost;
  for(int i=0; i<CASE; ++i)
      sum += pow(hyphothesis(i)-y[i],2);
  cost = (1/(2*(double)CASE))*sum;
  //std::cout << "cost : " << cost << std::endl;
  return cost;
}

double LinearRegression::d_cost_function(int n)
{
  double sum = 0;
  double d_cost;
  for(int i=0; i<FEATURE; ++i)
    sum += (hyphothesis(i)-y[i])*x_[i][n];
  d_cost = (1/(double)CASE)*sum;
//  std::cout << "d_cost : " << d_cost << std::endl;
  return d_cost;
}

void LinearRegression::gradient_descent()
{
  double p_cost;
  for(int i=0; i<2000; ++i)
  {
    p_cost = cost_function();
    new_theta();
    if(cost_function() > p_cost)
      break;
    if(i%100==0)
    {
      //std::cout << "p_cost : " << p_cost << std::endl;
      std::cout <<"theta : ";
      for(int j=0; j<5; ++j)
        std::cout << theta[j] << " ";
      std::cout << std::endl;
    }
  }
}

void LinearRegression::new_theta()
{
  std::vector<double> temp(FEATURE);
  for(int i=0; i<FEATURE; ++i)
  {
    temp[i] = theta[i] - learning_rate*(1/(double)CASE)*d_cost_function(i);
    theta[i] = temp[i];
  }
//  std::cout << theta[0] << " " <<theta[1] <<" " <<theta[2] <<" " <<theta[3] <<" " <<theta[4] << std::endl;
}

void LinearRegression::fillMat(std::ifstream& in)
{
  for(int i=0; i<CASE; ++i)
  {
    x_[i][0] = 1;
    for(int j=1; j<FEATURE; ++j)
      in >> x_[i][j];
    in >> y[i];
  }
}

double LinearRegression::test()
{
  double y = 0;
	x[0] = 1;

	for(int i = 1; i < FEATURE; i++)
		std::cin >> x[i];

	for(int i = 0; i < FEATURE; i++)
		y = y + theta[i] * x[i];
	return y;
}

int main()
{
  LinearRegression lr = LinearRegression();
  std::ifstream in("input.txt");
  lr.fillMat(in);
  lr.gradient_descent();
  std::cout << lr.test() << std::endl;
  return 0;
}
