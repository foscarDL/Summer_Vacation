import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		MultiValueLinearRegression multiValueLinearRegression = new MultiValueLinearRegression();

		multiValueLinearRegression.readFile();
		multiValueLinearRegression.gradientDescent();
		multiValueLinearRegression.getOutput();
	}
}