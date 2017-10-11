import java.util.Scanner;
public class shui
{
	public static void main(String [] args)
	{
		Scanner input = new Scanner(System.in);
		int n = input.nextInt() - 3;
		int i,j;
		long arr[][] = {
						{153,370,371,407},
						{1634,8208,9474},
						{54748,92727,93084},
						{548834},
						{1741725,4210818,9800817,9926315}
						
						};
		for(i=0;i<arr[n].length;i++)
		{
			System.out.println(arr[n][i]);
		}
	}
}
