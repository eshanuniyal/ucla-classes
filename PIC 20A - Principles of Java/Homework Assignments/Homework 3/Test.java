public class Test {
	public static void main(String[] args) {
		Rational r1 = new Rational(1, 2);
		Rational r2 = new Rational(-2, -4);
		Rational r3 = new Rational(0, 0);
		System.out.println(r1);
		System.out.println(r2); //output should be the same.
		System.out.println(r3);
		System.out.println(r1.equals(r2)); //output true
		System.out.println(r1.equals(r3));	// output false
		System.out.println(r1.floatValue());
		System.out.println(r1.intValue());
		System.out.println(r1.doubleValue());
		System.out.println(r1.longValue());
	}
}