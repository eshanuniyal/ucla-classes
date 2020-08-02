import java.math.BigInteger;

class Rational extends java.lang.Number {
	
	// fields
	private final BigInteger p;	// numerator of rational number (traditionally represented by p)
	private final BigInteger q;	// denominator of rational number (traditionally represented by q)

	// -----------------------------------------------------------------------------------------------------
	// constructors

	public Rational(int numerator, int denominator) {
		// calls constructor that takes BigInteger parameters
		this(BigInteger.valueOf(numerator), BigInteger.valueOf(denominator));
	}

	public Rational(BigInteger numerator, BigInteger denominator) {
		// takes BigInteger parameters and stores the rational number (in lowest terms) in p, q
		
		// computing common factor
		final BigInteger commonFactor = numerator.gcd(denominator);

		// setting p and q to numerator/commonFactor and denominator/commonFactor respectively
			// checking whether gcd is not 0 (which would only happen in case where both numerator and denominator passed in are 0)
		if (!commonFactor.equals(BigInteger.ZERO)) { 
			// value of rational number is preserved in lowest terms
			BigInteger lowP = numerator.divide(commonFactor);
			BigInteger lowQ = denominator.divide(commonFactor);

			// checking signs of numerator and denominator
				// both numerator and denominator are of the same sign -> rational is positive
			if ((lowP.signum() < 0 && lowQ.signum() < 0 ) || (lowP.signum() >= 0 && lowQ.signum() >= 0)) {
				p = lowP.abs();
				q = lowQ.abs();
			}
			// the numerator and denominator have different signs -> store the numerator as negative, denominator as positive
			else {
				p = lowP.abs().multiply(BigInteger.valueOf(-1));
				q = lowQ.abs();
			}
		}
		// both values passed in are zero; we store p and q in an invalid state of sorts
		else {
			p = BigInteger.ZERO;
			q = BigInteger.ZERO;
		}
	}
	// -----------------------------------------------------------------------------------------------------
	// abstract methods inherited from java.lang.Number

	public double doubleValue() {
		// return the most accurate double version of the rational
		// note: since a double is the widest type, the doubleValue is the most accurate representation of the rational number of any primitive types;
			// all other primitive type conversions (float, int and long below) therefore use doubleValue()

		// converting p and q to doubles
		double double_p = p.doubleValue();
		double double_q = q.doubleValue();

		// computing and returning quotient
		return double_p / double_q;
	}

	public float floatValue() {
		// return the most accurate float version of the rational
		return (float) this.doubleValue();
	}

	public int intValue() {
		// return the most accurate int version of the rational
		return (int) this.doubleValue();
	}

	public long longValue() {
		// return the most accurate long version of the rational
		return (long) this.doubleValue();
	}
	// -----------------------------------------------------------------------------------------------------
	// equals() and toString() methods inherited from java.lang.Object

	public boolean equals(Rational r) {
		// check if two rational objects are equal

		// numerator and denominator of both rationals are equal
		if (p.equals(r.p) && q.equals(r.q))
			return true;
		// both rationals are zero
		else if (p.equals(BigInteger.ZERO) && r.p.equals(BigInteger.ZERO))
			return true;
		// rationals are unequal
		else
			return false;
	}

	public String toString() {
		// return a string representation of the rational
		return p.toString() + "/" + q.toString();
	}
	// -----------------------------------------------------------------------------------------------------
	// operator functions (add, subtract, multiply, divide)

	public Rational add(Rational r) {
		// adds two rational numbers

		// we first compute the least common multiple of the denominators of both rationals
		BigInteger qProduct = q.multiply(r.q);	// q * r.q
		// at least one of the denominators is 0 -> return a Rational in an invalid state 
		if (qProduct.equals(BigInteger.ZERO))
			return new Rational(0, 0);
		
		BigInteger qGCD = q.gcd(r.q);	// gcd of q, r.q
		// both rational numbers are valid
		BigInteger qFinal = qProduct.divide(qGCD);	// from property of lcm: lcm(x,y) = x * y / gcd(x,y)
		
		// neither of the denominators are zero -> multiply numerator, denominator of each fraction by appropriate number to make numerators addable
		BigInteger m1 = qFinal.divide(q);	// desired multiple for numerator p
		BigInteger p1 = p.multiply(m1);		// multiplying numerator

		BigInteger m2 = qFinal.divide(r.q);	// desired multiple for numerator r.q
		BigInteger p2 = r.p.multiply(m2);	// multiplying numerator

		// adding numerators
		BigInteger pFinal = p1.add(p2);

		// returning resulting rational
		return new Rational(pFinal, qFinal);
	}

	public Rational subtract(Rational r) {
		// subtract two rational numbers
		BigInteger pNew = r.getNumerator().multiply(BigInteger.valueOf(-1));
		return add(new Rational(pNew, r.getDenominator()));
	}

	public Rational multiply(Rational r) {
		// multiply two rational numbers
		return new Rational(p.multiply(r.p), q.multiply(r.q));
	}

	public Rational divide(Rational r) {
		// divide two rational numbers
		return new Rational(p.multiply(r.q), q.multiply(r.p));
	}

	// -----------------------------------------------------------------------------------------------------
	// getter methods (getNumerator, getDenominator)

	public BigInteger getNumerator() { return p; }

	public BigInteger getDenominator() { return q; }

	// -----------------------------------------------------------------------------------------------------
	// additional factory methods (intToRational, BigIntegerToRational)

	public static Rational intToRational(int num) {
		return new Rational(num, 1);
	}
	public static Rational BigIntegerToRational(BigInteger num) {
		return new Rational(num, BigInteger.ONE);
	}

}