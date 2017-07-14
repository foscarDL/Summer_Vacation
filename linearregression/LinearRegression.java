package linearregression;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class LinearRegression {
	private final double LEARNING_RATE = 0.001;

	private int num_TrainingSet;// M
	private int num_Feature;// n

	private int[][] x = new int[num_TrainingSet][num_Feature];// x1,x2,x3,x4.;
	private double[] theta = new double[num_Feature + 1];// theta0,theta1,theta2...;
	private int[] y = new int[num_TrainingSet];// output;

	public void initialize() {
		initTheta();
		initFile();		
	}

	public void initTheta() {
		for (int i = 0; i <= num_Feature; i++)
			theta[i] = 0;
		for(int i=0;i<num_TrainingSet;i++)
		{
			for(int j=0;j<num_Feature;j++)
			{
				x[i][j]=0;
			}
		}
	}

	public void initFile() {
		try {
			File file = new File("src/linearregression/data.txt");
			Scanner scanner = new Scanner(file);
			while (scanner.hasNext()) {
				num_Feature = scanner.nextInt();
				num_TrainingSet = scanner.nextInt();
				for (int i = 0; i < num_TrainingSet; i++) {
					for (int j = 0; j < num_Feature; j++) {
						x[i][j] = 0;
					}
				}
				for (int i = 0; i < num_TrainingSet; i++) {
					for (int j = 0; j < num_Feature; j++) {
						System.out.printf("%d ", x[i][j]);
					}
				}
				for (int i = 0; i < num_TrainingSet; i++) {
					for (int j = 0; j <= num_Feature; j++) {
						if (j == num_Feature)
							y[i] = scanner.nextInt();
						else {
							x[i][j] = scanner.nextInt();
						}
					}
					System.out.println("");
				}
			}
			scanner.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

	public double getHypothesis(int number) {
		double sum = 0;
		try {
			for (int i = 0; i < num_Feature; i++) {
				sum += (theta[i] * x[number][i]);
			}
			sum += theta[num_Feature];
		} catch (Exception e) {
			e.printStackTrace();
		}
		return sum;
	}

	public double getCost() {
		double sum = 0;
		for (int i = 0; i < num_TrainingSet; i++) {
			sum += ((getHypothesis(i) - y[i]) * (getHypothesis(i) - y[i]));
		}
		return sum / (2 * num_TrainingSet);
	}

	public double getPartialDerivative(int index)
	{
		double sum=0;
		try
		{
			for (int i = 0; i < num_TrainingSet; i++) {
				sum = sum + ((getHypothesis(i) - y[i]) * x[i][index]);
			}
			sum /= num_TrainingSet;
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		return sum;
	}

	public void updateTheta() {
		for (int i = 0; i <= num_Feature; i++) {
			theta[i] = theta[i] - LEARNING_RATE * getPartialDerivative(i);
		}
	}

	public void gradientDescent()
	{
		int iter = 0;
		double prevCost;
		double nextCost;
		do
		{
			iter++;
			prevCost = getCost();
			updateTheta();
			nextCost = getCost();
			System.out.printf("%d ¹øÂ° GradientDescent Cost %f\n", iter, getCost());
		} while (prevCost > nextCost);
	}

	public void printResult()
	{
		System.out.println("Data set ¼ö " + num_TrainingSet);
		for (int i = 0; i <= num_Feature; i++)
		{
			if (i == num_Feature)
			{
				System.out.printf("Theta0 = %f\n", theta[num_Feature]);
			} else
			{
				System.out.printf("Theta%d = %f\n", i + 1, theta[i]);
			}
		}
	}
}