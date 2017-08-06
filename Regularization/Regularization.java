import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Regularization {
	private final double LEARNING_RATE = 0.0001;
	private final double LAMBDA = 0.32;

	private int nData, nColumns, nFeature, nCrossValidation;
	private int[][] matrixX;
	private int[] matrixY;
	private double[] matrixTheta;
	private double[] matrixTemp;
	private int[] matrixInput;

	private int[][] matrixCV;
	private int[] matrixCVOutput;

	private Scanner input;

	public void readFile() throws FileNotFoundException {
		input = new Scanner(new File("input.dat"));

		nData = input.nextInt();
		nColumns = input.nextInt();
		nFeature = nColumns - 1;

		nCrossValidation = input.nextInt();

		init();

		for(int i = 0; i < nData; i++) {
			for(int j = 0; j < nColumns+1; j++) {
				if(j == 0)
					matrixX[i][j] = 1;
				else if(j != nFeature+1)
					matrixX[i][j] = input.nextInt();
				else
					matrixY[i] = input.nextInt();
			}
		}

		for(int i = 0; i < nCrossValidation; i++) {
			for(int j = 0; j < nColumns+1; j++) {
				if(j == 0)
					matrixCV[i][j] = 1;
				else if(j != nFeature+1) 
					matrixCV[i][j] = input.nextInt();
				else
					matrixCVOutput[i] = input.nextInt();
			}
		}
	}

	public void init() {
		matrixX = new int[nData][nFeature+1];
		matrixY = new int[nData];
		matrixTheta = new double[nFeature+1];
		matrixTemp = new double[nFeature+1];
		matrixInput = new int[nFeature+1];

		matrixCV = new int[nCrossValidation][nFeature+1];
		matrixCVOutput = new int[nCrossValidation];
	}

	public double getHypothesis(int nthCase) {
		double hypothesis = 0;

		for(int i = 0; i < nFeature+1; i++) {
			hypothesis = hypothesis + (matrixTheta[i] * matrixX[nthCase][i]);
		}

		return hypothesis;
	}

	public double getCVHypothesis(int nthCase) {
		double hypothesis = 0;

		for(int i = 0; i < nFeature+1; i++) {
			hypothesis = hypothesis + (matrixTheta[i] * matrixCV[nthCase][i]);
		}

		return hypothesis;
	}

	public double getDifferentialValue(int nthCase) {
		double sumOfDifferentialValue = 0;

		for(int i = 0; i < nData; i++) {
			sumOfDifferentialValue = sumOfDifferentialValue + (getHypothesis(i) - matrixY[i]) * matrixX[i][nthCase];
		}

		return sumOfDifferentialValue;
	}

	public void updateTheta() {
		double[] temp = new double[nFeature+1];

		for(int i = 0; i < nFeature+1; i++) {
			temp[i] = matrixTheta[i] - (LEARNING_RATE / nData) * getDifferentialValue(i);
		}

		for(int i = 0; i < nFeature+1; i++) {
			matrixTheta[i] = temp[i];
		}
	}

	public double getSumOfTheta() {
		double sumOfTheta = 0;

		for(int i = 1; i < nFeature+1; i++) {
			sumOfTheta = sumOfTheta + Math.pow(matrixTheta[i], 2);
		}

		return sumOfTheta;
	}

	public double getCost() {
		double sumOfCost = 0;

		for(int i = 0; i < nData; i++) {
			sumOfCost = sumOfCost + Math.pow(getHypothesis(i) - matrixY[i], 2);
		}

		return (sumOfCost / (2 * nData)) + ((getSumOfTheta() * LAMBDA) / (2 * nData));
	}

	public void gradientDescent() {
		int iter = 0;
		double preCost, postCost;

		while(true) {
			preCost = getCost();
			updateTheta();
			postCost = getCost();

			System.out.printf("Step : %d\n", ++iter);
			System.out.printf("θ0 : %.3f\tθ1 : %.3f\tθ2 : %.3f\tθ3 : %.3f\tθ4 : %.3f\n", 
								matrixTheta[0], matrixTheta[1], matrixTheta[2], matrixTheta[3], matrixTheta[4]);

			System.out.printf("Cost : %.6f\n", postCost);

			if(preCost < postCost) break;
		}
	}

	public void crossValidation() {
		double sumOfCost = 0;

		for(int i = 0; i < nCrossValidation; i++) {
			sumOfCost = sumOfCost + Math.pow(getCVHypothesis(i) - matrixCVOutput[i], 2);
		}

		double cvCost = (sumOfCost / (2 * nData));

		System.out.printf("\nλ : %.2f\n", LAMBDA);
		System.out.printf("Cross-Validation Cost : %.6f\n", cvCost);

	}
}