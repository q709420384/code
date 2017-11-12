/*************************************************************************
	> File Name: prefix.java
	> Author:Sanjingye 
	> Mail: 
	> Created Time: 2017年10月19日 星期四 09时45分19秒
 ************************************************************************/
import java.util.Scanner;
public class prefix{
    public static int Getstart(String str1 , String str2){
        char[] c1=str1.toCharArray();
        char[] c2=str2.toCharArray();
        int min = c1.length > c2.length ? c2.length : c1.length ;
        if(c1[0] != c2[0])
            return -1;
        int i = 0;
        for(; i < min ; i++){
            if(i==min-1&&c1[i]==c2[i])
                return i;
            if(c1[i]!=c2[i])
            {
                System.out.println("i = " + i);
                return i;
            }
        }
        return i-1;
    }
    public static void main(String [] args){
        Scanner input = new Scanner(System.in);
        String s1 = input.nextLine();
        String s2 = input.nextLine();
        int i = Getstart(s1 , s2);
        if(i == -1)
            System.out.println("No common prefix");
        else
            System.out.println("Common prefix is " + s1.substring(0 , i));
    }
}

