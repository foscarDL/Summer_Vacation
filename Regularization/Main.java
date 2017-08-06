import java.io.FileNotFoundException;

public class Main {
	public static void main(String[] args) throws FileNotFoundException {
		Regularization regularization = new Regularization();

		regularization.readFile();
		regularization.gradientDescent();
		regularization.crossValidation();
	}
}