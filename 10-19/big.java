import java.math.*;
public class big{
	public static void main(String [] args) {
		BigInteger i = new BigInteger(Long.MAX_VALUE + "");
	    i = i.add(BigInteger.ONE);
	    BigInteger f = new BigInteger("5");
	    BigInteger s = new BigInteger("6");
	    BigInteger z = new BigInteger("0");
	    int t = 0 ;
	    while(t < 10)
	    {
	        if(i.remainder(f)== z || i.remainder(s)==z)
	        {
	            System.out.print(i + " ");
	            t++;
	        }
	        i = i.add(BigInteger.ONE);
	    }
	}
}
