import java.util.Scanner;

public class Equation
{
	public static void main(String[] args) 
	{
		
		Scanner input = new Scanner(System.in);
		
		System.out.print("Enter a, b, c:");
		double a = input.nextDouble();
		double b = input.nextDouble();
		double c = input.nextDouble();
		
		double temp = b*b - 4*a*c;
		if(temp <0 )
		{
			System.out.println("The equation has no real roots");
		}
		else if(temp == 0)
		{
			System.out.printf("The root is %.6f\n", (-b+Math.sqrt(temp))/(2*a));
		}
		else
		{
			System.out.printf("The roots are %.6f and %.6f\n", (-b+Math.sqrt(temp))/(2*a), (-b-Math.sqrt(temp))/(2*a));
		}
	}
}
