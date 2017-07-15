package linearregression;

import java.io.FileNotFoundException;

public class Test
{
	public static void main(String[] args) throws FileNotFoundException
	{
		LinearRegression reg = new LinearRegression();
		reg.gradientDescent();
	}
}
