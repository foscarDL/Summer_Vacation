import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class LogisticRegression {
	private static final double LEARING_RATE = 0.003;
	
	private static final int IRIS_SETOSA = 0;
	private static final int IRIS_VERSICOLOR = 1;
	private static final int IRIS_VIRGINICA = 2;

	private static int nData, nColumns, nFeature, nClass;
	private static double[][] matX;
	private static double[][] matTheta;
	private static int[][] matY;
	private static double[] matInput;

	private static Scanner input;

	public static void main(String[] args) throws FileNotFoundException {
		input = new Scanner(new File("input.dat"));

		nData = input.nextInt();
		nColumns = input.nextInt();
		nClass = input.nextInt();
		nFeature = nColumns - 1;

		matX = new double[nData][nFeature+1];
		matTheta = new double[nClass][nFeature+1];
		matY = new int[nData][nClass];
		matInput = new double[nFeature+1];

		for(int i = 0; i < nData; i++) {
			for(int j = 0; j < nColumns+1; j++) {
				if(j == 0)
					matX[i][j] = 1;
				else if(j != nFeature+1)
					matX[i][j] = input.nextDouble();
				else {
					String fClass = input.next();
					if(fClass.equals("Iris-setosa")) matY[i][0] = 1;
					else if(fClass.equals("Iris-versicolor")) matY[i][1] = 1;
					else matY[i][2] = 1;
				}
			}
		}

		for(int i = 0; i < 2000; i++) {
			updateTheta(0);
			updateTheta(1);
			updateTheta(2);

			if(i % 20 == 0) {
				for(int j = 0; j < nClass; j++) {
					for(int k = 0; k < nFeature+1; k++) {
						System.out.printf("θ%d%d : %.3f\t", j, k, matTheta[j][k]);
					}
					System.out.println();
				}
				System.out.println();
			}
		}

		judge();
	}

	public static double getThetaX(int noCase, int noThetaX) {
		double thetaX = 0;

		for(int i = 0; i < nFeature+1; i++) {
			thetaX = thetaX + (matTheta[noThetaX][i] * matX[noCase][i]);
		}

		return thetaX;
	}

	public static double getHypothesis(int noCase, int noThetaX) {
		double hypothesis = 1 / (1 + Math.pow(Math.exp(1), -1 * (getThetaX(noCase, noThetaX))));
		return hypothesis;
	}

	public static double getDifferentialValue(int noCase, int noThetaX) {
		double sum = 0;

		for(int i = 0; i < nData; i++) {
			sum = sum + (getHypothesis(i, noThetaX) - matY[i][noThetaX]) * matX[i][noCase];
		}

		return sum;
	}

	public static void updateTheta(int noThetaX) {
		double temp0, temp1, temp2, temp3, temp4;

		temp0 = matTheta[noThetaX][0] - (LEARING_RATE) * getDifferentialValue(0, noThetaX);
		temp1 = matTheta[noThetaX][1] - (LEARING_RATE) * getDifferentialValue(1, noThetaX);
		temp2 = matTheta[noThetaX][2] - (LEARING_RATE) * getDifferentialValue(2, noThetaX);
		temp3 = matTheta[noThetaX][3] - (LEARING_RATE) * getDifferentialValue(3, noThetaX);
		temp4 = matTheta[noThetaX][4] - (LEARING_RATE) * getDifferentialValue(4, noThetaX);

		matTheta[noThetaX][0] = temp0;
		matTheta[noThetaX][1] = temp1;
		matTheta[noThetaX][2] = temp2;
		matTheta[noThetaX][3] = temp3;
		matTheta[noThetaX][4] = temp4;
	}

	public static void judge() {
		input = new Scanner(System.in);
		matInput[0] = 1;

		System.out.print("Input data : ");
		for(int i = 1; i < nFeature+1; i++) {
			matInput[i] = input.nextDouble();
		}

		double y1 = 0;
		double y2 = 0;
		double y3 = 0;

		for(int i = 0; i < nFeature+1; i++) {
			y1 = y1 + matTheta[0][i] * matInput[i];
			y2 = y2 + matTheta[1][i] * matInput[i];
			y3 = y3 + matTheta[2][i] * matInput[i];
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