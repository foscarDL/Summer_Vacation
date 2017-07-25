import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class LogisticRegression {
	private final double LEARNING_RATE = 0.074;
	
	private final int IRIS_SETOSA = 0;
	private final int IRIS_VERSICOLOR = 1;
	private final int IRIS_VIRGINICA = 2;

	private int nData, nColumns, nFeature, nClass;
	private double[][] matrixX;
	private double[][] matrixTheta;
	private int[][] matrixY;
	private double[] matrixInput;

	private Scanner input;

	public void readFile() throws FileNotFoundException {
		input = new Scanner(new File("input.dat"));

		nData = input.nextInt();
		nColumns = input.nextInt();
		nClass = input.nextInt();
		nFeature = nColumns - 1;

		init();

		for(int i = 0; i < nData; i++) {
			for(int j = 0; j < nColumns+1; j++) {
				if(j == 0)
					matrixX[i][j] = 1;
				else if(j != nFeature+1)
					matrixX[i][j] = input.nextDouble();
				else {
					String fClass = input.next();
					if(fClass.equals("Iris-setosa")) matrixY[i][0] = 1;
					else if(fClass.equals("Iris-versicolor")) matrixY[i][1] = 1;
					else matrixY[i][2] = 1;
				}
			}
		}
	}

	public void init() {
		matrixX = new double[nData][nFeature+1];
		matrixTheta = new double[nClass][nFeature+1];
		matrixY = new int[nData][nClass];
		matrixInput = new double[nFeature+1];
	}

	public double getThetaX(int noCase, int noThetaX) {
		double thetaX = 0;

		for(int i = 0; i < nFeature+1; i++) {
			thetaX = thetaX + (matrixTheta[noThetaX][i] * matrixX[noCase][i]);
		}

		return thetaX;
	}

	public double getHypothesis(int noCase, int noThetaX) {
		double hypothesis = 1 / (1 + Math.pow(Math.exp(1), -1 * (getThetaX(noCase, noThetaX))));
		return hypothesis;
	}

	public double getDifferentialValue(int noCase, int noThetaX) {
		double sum = 0;

		for(int i = 0; i < nData; i++) {
			sum = sum + (getHypothesis(i, noThetaX) - matrixY[i][noThetaX]) * matrixX[i][noCase];
		}

		return sum;
	}

	public void updateTheta(int noThetaX) {
		double[] temp = new double[nFeature+1];

		for(int i = 0; i < nFeature+1; i++) {
			temp[i] = matrixTheta[noThetaX][i] - (LEARNING_RATE / nData) * getDifferentialValue(i, noThetaX);
		}

		for(int i = 0; i < nFeature+1; i++) {
			matrixTheta[noThetaX][i] = temp[i];
		}
	}

	public double getCost(int noThetaX) {
		double sumOfCost = 0;

		for(int i = 0; i < nData; i++) {
			sumOfCost = (-1 * matrixY[i][noThetaX] * Math.log10(getHypothesis(i, noThetaX))) - (1 - matrixY[i][noThetaX]) * Math.log10(1 - getHypothesis(i, noThetaX)); 
		}

		return sumOfCost / nData;
	}

	public void gradientDescent() {
		int iter = 0;
		double preCost, postCost;

		for(int i = 0; i < nClass; i++) {
			while(true) {
				preCost = getCost(i);
				updateTheta(i);
				postCost = getCost(i);

				if(++iter % 10000 == 0) {
					System.out.printf("Step : %d\n", iter);
					for(int j = 0; j < nClass; j++) {
						for(int k = 0; k < nFeature+1; k++) {
							System.out.printf("θ%d%d : %.3f\t", j, k, matrixTheta[j][k]);
						}
						System.out.println();
					}

					System.out.printf("\nCost1 : %.9f, Cost2 : %.6f, Cost3 : 3%.6f\n", getCost(0), getCost(1), getCost(2));
				}

				if(preCost < postCost) break;
			}
		}

		// double preCost0, preCost1, preCost2, postCost0, postCost1, postCost2;

		// while(true) {
		// 		preCost0 = getCost(0);
		// 		preCost0 = getCost(1);
		// 		preCost0 = getCost(2);

		// 		updateTheta(0);
		// 		updateTheta(1);
		// 		updateTheta(2);

		// 		postCost0 = getCost(0);
		// 		postCost0 = getCost(1);
		// 		postCost0 = getCost(2);

		// 		if(++iter % 100 == 0) {
		// 			System.out.printf("Step : %d\n", iter);
		// 			for(int j = 0; j < nClass; j++) {
		// 				for(int k = 0; k < nFeature+1; k++) {
		// 					System.out.printf("θ%d%d : %.3f\t", j, k, matrixTheta[j][k]);
		// 				}
		// 				System.out.println();
		// 			}

		// 			System.out.printf("Cost1 : %.9f, Cost2 : %.6f, Cost3 : 3%.6f\n\n", getCost(0), getCost(1), getCost(2));
		// 		}

		// 		if(iter == 10000) break;
		// 	}

	}

	public void getOutput() {
		input = new Scanner(System.in);
		matrixInput[0] = 1;

		System.out.print("Input data : ");
		for(int i = 1; i < nFeature+1; i++) {
			matrixInput[i] = input.nextDouble();
		}

		double y1 = 0;
		double y2 = 0;
		double y3 = 0;

		for(int i = 0; i < nFeature+1; i++) {
			y1 = y1 + matrixTheta[0][i] * matrixInput[i];
			y2 = y2 + matrixTheta[1][i] * matrixInput[i];
			y3 = y3 + matrixTheta[2][i] * matrixInput[i];
		}

		System.out.print("Output : ");
		if(y1 >= 0 && y2 < 0 && y3 < 0)
			System.out.println("IRIS_SETOSA");
		else if(y1 < 0 && y2 < 0 && y3 >= 0)
			System.out.println("IRIS_VIRGINICA");
		else
			System.out.println("IRIS_VERSICOLOR");
	}
}