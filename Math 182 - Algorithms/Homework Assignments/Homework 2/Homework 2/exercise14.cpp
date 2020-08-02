#include<unordered_map>
#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

int nPartitions(int n, vector<int> partSizes) {
	// returns the number of partitions of n composed of sizes from partSizes
	// dynamic programming solution
		
	vector<int> partitionSizes(n + 1, 0);
		// a list containing, for each number from 1 through n, the number of partitions it has
		// initialised to 0

	// base case: partitionSize[0] represents the termination of a partition
	partitionSizes[0] = 1;

	// iterating over part sizes
	for (int part : partSizes)
		// iterating from 1 through n
		for (int i = 1; i <= n; i++)
			// partitions(i) = partitions[i] + partitions[i - part]
				// (for only parts that have already been processed for smaller i)
			if (i - part >= 0)
				partitionSizes[i] += partitionSizes[i - part];

	// return partitions of n
	return partitionSizes[n];
}