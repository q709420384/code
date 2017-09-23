import java.util.Scanner;
import java.text.DateFormat;
public class print
{

	public static void main(String[] args) 
	{
		Scanner input = new Scanner(System.in);
		
		System.out.print("Enter employee's name:");
		String name = input.nextLine();
		
		System.out.print("Enter number of hours worked in a week:");
		double workhour = input.nextDouble();
		
		System.out.print("Enter hourly pay rate:");
		double pay = input.nextDouble();
		
		System.out.print("Enter federal tax withholding rate:");
		double federaltax = input.nextDouble();
		
		System.out.print("Enter state tax withholding rate:");
		double statetax = input.nextDouble();
		
		double crosspay = pay*workhour ;
		double deduction =crosspay*(statetax+federaltax);
		
		System.out.println("\n");
		System.out.println("Employee Name: " + name);
		System.out.println("Hours Worked: " + workhour);
		System.out.println("Pay Rate:$" + pay);
		System.out.println("Gross Pay:$" + crosspay);
		System.out.println("Deductions:");
		System.out.printf("Federal Withholding (%.1f%%):$%.2f\n",federaltax*100,crosspay*federaltax);
		System.out.printf("State Withholding (%.1f%%):$%.2f\n",statetax*100,crosspay*statetax);
		System.out.println("Total Deduction:$"+String.format("%.2f",deduction));
		System.out.println("Net Pay:$"+String.format("%.2f", crosspay-deduction));
	}

}
