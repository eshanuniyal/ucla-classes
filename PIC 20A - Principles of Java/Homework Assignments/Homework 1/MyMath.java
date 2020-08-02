public class MyMath {	
	public static double sqrt(double d) {
		// computes the square root of d up to a certain precision

		int nDivisions = 0;		// number of times d is divided by 4

		// modifying d; while d > 1, divide d by 4 and increment nDivisions
		while (d > 1) {
			d /= 4;
			nDivisions++;
		}

		// d is now between 0 and 1
		double l = 0;	// lower bound for modified d
		double u = 1;	// upper bound for modified d

		double precision = 0.0000000001;	// 10^-10, desired maximal size (or precision) of interval [l, u]

		// performing bisection process until our interval (represented by u - l) is less than 10^-10
		while (u - l >= precision) {

			double m = (l + u) / 2;		// midpoint of current interval
			
			// finding new interval for root of modified d
			if (d <= m * m)
				u = m;	// root d lies between [l, m]
			else
				l = m; // root d lies between [m, u]
		}

		// tight interval for root of modified d found; estimating root
		double rootD = (l + u) / 2;

		// multiplying by 2 nDivisions times to get actual root of d
		rootD *= Math.pow(2, nDivisions);

		return rootD;
	}

	public static void main(String[] args) {
		// tests and compares MyMath.sqrt with Math.sqrt with 100,000 numbers between 0 and 100

		int nIterations = 10000000;		// number of times we test each function

		long startTime = System.currentTimeMillis();	// starting time for test of MyMath.sqrt
		
		// testing MyMath.sqrt
		for (int i = 0; i != nIterations; i++){
			// finding random number
			double rand = 100 * Math.random();
			// computing square root of a random number between 0 and 100
			sqrt(100 * Math.random());
		}
		
		// finding total time taken for MyMath.sqrt
		long myMathTime = System.currentTimeMillis() - startTime;

		// updating start time
		startTime = System.currentTimeMillis();

		// testing Math.sqrt
		for (int i = 0; i != nIterations; i++){
			// finding random number
			double rand = 100 * Math.random();
			// computing square root of a random number between 0 and 100
			Math.sqrt(100 * Math.random());
		}

		// finding total time taken for Math.sqrt
		long mathTime = System.currentTimeMillis() - startTime;

		// updating start time
		startTime = System.currentTimeMillis();

		// generating random numbers (to find time taken to generate random numbers)
		for (int i = 0; i != nIterations; i++) {
			double rand = 100 * Math.random();
		}
		
		// finding total time taken to generate random numbers
		long randTime = System.currentTimeMillis() - startTime;

		// adjusting myMathTime and mathTime for time taken to generate random numbers
		myMathTime -= randTime;
		mathTime -= randTime;

		// computing average times
		double avgMyMathTime = (double)(myMathTime) / nIterations;
		double avgMathTime = (double)(mathTime) / nIterations;

		// printing results
		System.out.println("Average time taken with MyMath.sqrt: " + avgMyMathTime + " ms");
		System.out.println("Average time taken with Math.sqrt is: " + avgMathTime + " ms");
	}
}