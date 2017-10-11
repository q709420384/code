import java.util.Scanner;

public class week
{
	public static void main(String[] args)
	{
		String[] we = {"Saturday","Sunday","Monday","Tuesday","Wednesday","Thursday","Firday"};
		Scanner input = new Scanner(System.in);
		System.out.print("Enter year (e.g., 2012)");
		int year = input.nextInt();
		System.out.print("Enter month: 1-12: ");
		int month = input.nextInt();
		System.out.print("Enter the day of the month: 1-31: ");
		int day = input.nextInt();
		if(month < 3)
		{
			month = month + 12;
			year = year - 1;
		}
		int j = Math.abs(year / 100);
		int k = year % 100;
		int h = (day + (26*(month + 1) / 10) + k + k / 4 + j / 4 + 5* j) % 7;
		System.out.println("Day of the week is " + we[h] );
	}
}