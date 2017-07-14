package linearregression;

public class Test
{
	public static void main(String[] args)
	{
		LinearRegression reg = new LinearRegression();
		reg.initialize();
		reg.gradientDescent();
		reg.printResult();
	}
}
