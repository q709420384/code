import java.util.Scanner;
public class Tdirectory {
	public static void main(String [] args) {
		Scanner input = new Scanner(System.in);
		String[][] arr  = new String [100][2];
		String name, num;
		int i , j;
		for(i = 0; i < 100; i++) {
			name = input.next();
			if(name.equals("noname"))
				break;
			arr[i][0] = name;
			arr[i][1] = input.next();
		}
		name = input.next();
		for(j = 0; j < i; j++) {
			if(arr[j][0].equals(name)) {
				System.out.println(arr[i][0]);
				return;
			}
		}
		System.out.println("Not found.");
	}
}

