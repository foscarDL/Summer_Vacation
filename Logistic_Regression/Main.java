import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) throws FileNotFoundException{
		LogisticRegression logisticRegression = new LogisticRegression();

		logisticRegression.readFile();
		logisticRegression.gradientDescent();
		logisticRegression.getOutput();
	}
}