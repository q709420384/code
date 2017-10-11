import java.util.Scanner;

public class interest
{
	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);
		System.out.printf("Enter investment amount:");
		double amount = input.nextDouble();
		System.out.printf("Enter annual interest rate in percentage:");
		double rate = input.nextDouble();
		System.out.printf("Enter number of years:");
		double year = input.nextDouble();
		System.out.printf("Accumulated value is $%.2f\n",amount * Math.pow((1 + rate/100),year));
	}
}
