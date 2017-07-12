import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class MultiLinearRegression {
	private static final double LEARNING_RATE = 0.00003;

	private static int nData, nColumns, nFeature;
	private static int[][] matX;
	private static int[] matY;
	private static double[] matTheta;
	private static int[] matInput;

	private static Scanner input;

	public static void main(String[] args) throws FileNotFoundException {
		input = new Scanner(new File("input.dat"));

		nData = input.nextInt();
		nColumns = input.nextInt();
		nFeature = nColumns - 1;

		matX = new int[nData][nFeature+1];
		matY = new int[nData];
		matTheta = new double[nFeature+1];
		matInput = new int[nFeature+1];

		for(int i = 0; i < nData; i++) {
			for(int j = 0; j < nColumns+1; j++) {
				if(j == 0)
					matX[i][j] = 1;
				else if(j != nFeature+1)
					matX[i][j] = input.nextInt();
				else
					matY[i] = input.nextInt();
			}
		}

		for(int i = 0; i < 2000; i++) {
			updateTheta();

			if(i % 20 == 0) {
				System.out.println("θ0 = " + matTheta[0] + "\nθ1 = " + matTheta[1] + "\nθ2 = " + matTheta[2] + "\nθ3 = " + matTheta[3] + "\nθ4 = " + matTheta[4] + "\n");
			}
		}

		judge();
	}

	public static double hypothesis(int noCase) {
		double h = 0;

		for(int i = 0; i < nFeature+1; i++) {
			h = h + (matTheta[i] * matX[noCase][i]);
		}

		return h;
	}

	public static double getDifferentialValue(int noCase) {
		double sum = 0;

		for(int i = 0; i < nData; i++) {
			sum = sum + (hypothesis(i) - matY[i]) * matX[i][noCase];
		}

		return sum;
	}

	public static void updateTheta() {
		double temp0, temp1, temp2, temp3, temp4;

		temp0 = matTheta[0] - (LEARNING_RATE / nData) * getDifferentialValue(0);
		temp1 = matTheta[1] - (LEARNING_RATE / nData) * getDifferentialValue(1);
		temp2 = matTheta[2] - (LEARNING_RATE / nData) * getDifferentialValue(2);
		temp3 = matTheta[3] - (LEARNING_RATE / nData) * getDifferentialValue(3);
		temp4 = matTheta[4] - (LEARNING_RATE / nData) * getDifferentialValue(4);

		matTheta[0] = temp0;
		matTheta[1] = temp1;
		matTheta[2] = temp2;
		matTheta[3] = temp3;
		matTheta[4] = temp4;
	}

	public static void judge() {
		double y = 0;

		input = new Scanner(System.in);
		matInput[0] = 1;

		System.out.print("Input data : ");
		for(int i = 1; i < nFeature+1; i++) {
			matInput[i] = input.nextInt();
		}

		for(int i = 0; i < nFeature+1; i++) {
			y = y + matTheta[i] * matInput[i];
		}

		System.out.println("Output : " + y);
	}
}