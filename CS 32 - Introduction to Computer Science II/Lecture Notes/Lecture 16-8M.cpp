
// we may also have code with multiple parameters defining the size of a data; e.g. a matrix with R rows and C columns
for (int i = 0; i != R; i++) { // <=========== O(RClogC)
	a[i] *= 2;
	for (int j = 0; j != C; j++) // <========= O(ClogC)
		f(j, C); // <========================= O(logC) (assumed)
}

