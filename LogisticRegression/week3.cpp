#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#define CASE 150
#define FEATURE 5
#define CLASS 3

class LogisticRegression
{
public:
  double x[CASE];
  double y[CASE][CLASS];
  double theta[CLASS][FEATURE];
  double x_[CASE][FEATURE];
  const double learning_rate;

  LogisticRegression();
  double hypothesis(int c, int n);
  double cost_function(int c);
  double d_cost_function(int c, int f);
  void gradient_descent();
  void new_theta(int c);
  void fillMat(std::ifstream& in);
  void test();
};

LogisticRegression::LogisticRegression() : learning_rate(0.05)
{

}

double LogisticRegression::hypothesis(int c, int n)
{
  double z=0, h=0;
  for(int i=0;i<FEATURE; ++i)
    z += theta[c][i]*x_[n][i];
  h = 1/(1 + pow(exp(1), (-1)*z));
  return h;
}

double LogisticRegression::cost_function(int c)
{
  double sum = 0.0;
  double cost;
  for(int i=0; i<CASE; ++i)
      sum += ((y[i][c]*log(hypothesis(c, i))) + ((1-y[i][c])*log(1-hypothesis(c, i))));
  cost = -(1/(double)CASE)*sum;
  // std::cout << "cost : " << cost << std::endl;
  return cost;
}

double LogisticRegression::d_cost_function(int c, int f)
{
  double sum = 0.0;
  double d_cost;
  for(int i=0; i<CASE; ++i)
    sum += (hypothesis(c, i)-y[i][c])*x_[i][f];
  d_cost = (1/(double)CASE)*sum;
  return d_cost;
}

void LogisticRegression::gradient_descent()
{
  double p_cost;
  for(int i=0; i<2000; ++i)
  {
    for(int j=0; j<CLASS; ++j)
    {
      p_cost = cost_function(j);
      new_theta(j);
    //  if(cost_function(j) > p_cost || cost_function(j) < 0)  break;

    }
    if(i%100==0)
    {
      //std::cout << "p_cost : " << p_cost << std::endl;
      std::cout <<"theta : ";
      for(int j=0; j<CLASS; ++j){
        for(int k=0; k<FEATURE; ++k)
          std::cout << theta[j][k] << " ";
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
  }
}

void LogisticRegression::new_theta(int c)
{
  double temp[FEATURE];
  for(int i=0; i<FEATURE; ++i)
  {
    temp[i] = theta[c][i] - learning_rate*d_cost_function(c, i);
    theta[c][i] = temp[i];
  }
}

void LogisticRegression::fillMat(std::ifstream& in)
{
  std::string temp;
  std::string type_1 = "Iris-setosa";
  std::string type_2 = "Iris-versicolor";
  std::string type_3 = "Iris-virginica";
  for(int i=0; i<CASE; ++i)
  {
    x_[i][0] = 1;
    for(int j=1; j<FEATURE; ++j)
    {
      in >> x_[i][j];
      y[i][j] = 0;
    }
    in >> temp;
    if(temp.compare(type_1)==0) y[i][0] = 1;
    else if(temp.compare(type_2)==0) y[i][1] = 1;
    else if(temp.compare(type_3)==0) y[i][2] = 1;
//    std::cout << y[i][0] << " " << y[i][1] << " " << y[i][2] <<std::endl;
  }
  for(int i=0; i<CLASS; ++i)
    for(int j=0; j<FEATURE; ++j)
      theta[i][j] = 0;
}

void LogisticRegression::test()
{
  double y_1 = 0, y_2 = 0, y_3 = 0;
  x[0]=1;
  for(int i=1; i<FEATURE; ++i)
    std::cin >> x[i];
  for(int i=0; i<FEATURE; ++i)
  {
    y_1 += theta[0][i]*x[i];
    y_2 += theta[1][i]*x[i];
    y_3 += theta[2][i]*x[i];
  }
  // std::cout << y_1 << " " << y_2 << " " << y_3<< std::endl;
  double max = y_1;
  if(y_2>max) max = y_2;
  if(y_3>max) max = y_3;

  if(max == y_1) std::cout <<"Iris-setosa" << std::endl;
  else if(max == y_2) std::cout << "Iris-versicolor" <<std::endl;
  else std::cout << "Iris-virginica" << std::endl;
}

int main()
{
  std::ifstream in("input3.txt");
  LogisticRegression lr = LogisticRegression();
  lr.fillMat(in);
  lr.gradient_descent();
  lr.test();
  return 0;
}
