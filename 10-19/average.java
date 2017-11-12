/*************************************************************************
	> File Name: average.java
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月19日 星期四 09时26分49秒
 ************************************************************************/
import java.util.Scanner;
public class average{
    public static void main(String [] args){
        Scanner input = new Scanner(System.in);
        double total = 0 ;
        double score ;
        int t = 0 ;
        String name = input.next();
        score = input.nextDouble();
        while(score >= 0){
            total += score;
            t++;
            name = input.next();
            score = input.nextDouble();
        }
        if(t == 0)
            System.out.println("No data input");
        else
            System.out.println("total = " + total + " average = " + total/t);

    }
}
