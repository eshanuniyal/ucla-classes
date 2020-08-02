#include<iostream>
#include<vector>
// #include<string>
using namespace std;

// exercise 11
int HighlyCompositeTriangular(int minDivisors);
// exercise 12
int longestCollatzChain(int bound);
// exercise 14
int nPartitions(int n, vector<int> partSizes);
// exercise 15
int digitProduct(vector<int> digitIndices);

int main() {
    // exercise 11
    cout << "Exercise 11: " <<  HighlyCompositeTriangular(1000) << endl;
        // answer 842161320

    // exercise 12
    cout << "Exercise 12: " << longestCollatzChain(2000000) << endl;
        // answer 1723519

    // exercise 14
    cout << "Exercise 14: " << nPartitions(200, vector<int> { 1, 2, 5, 10, 20, 50, 100, 200 }) << endl;
        // answer 73682

    // exercise 15
    vector<int> digitIndices;
    for (int p = 0; p <= 6; p++)
        digitIndices.push_back(int(pow(10, p)));
    cout << "Exercise 15: " << digitProduct(digitIndices) << endl;
        // answer 210
}










/*int merge(int arr[], int beg, int mid, int end) {
    
    int swapCount = 0; // track of how many inversions swapped

    int left = mid - beg + 1;
    int right = end - mid;

    int* Left_arr = new int[left];
    int* Right_arr = new int[right];

    for (int i = 0; i < left; ++i)
        Left_arr[i] = arr[beg + i];

    for (int j = 0; j < right; ++j)
        Right_arr[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = beg;
    while (i < left && j < right) {
        if (Left_arr[i] <= Right_arr[j]) {
            arr[k] = Left_arr[i];
            i++;
        }
        else {
            arr[k] = Right_arr[j];
            j++;
            swapCount++;
            cout << Left_arr[i] << " " << Right_arr[j] << endl;
        }
        k++;
    }
    while (i < left) {
        arr[k] = Left_arr[i];
        i++; k++;
        swapCount += right;
    }
    while (j < right) {
        arr[k] = Right_arr[j];
        j++; k++;
    }
    return swapCount;
}

int merge_sort(int arr[], int beg, int end) {
    int swapCount = 0;
    if (beg < end) {
        int mid = (beg + end) / 2;
        swapCount += merge_sort(arr, beg, mid);
        swapCount += merge_sort(arr, mid + 1, end);
        swapCount += merge(arr, beg, mid, end);
    }
    return swapCount;
}

int main() {
    const int n = 10;
    int arr[n] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    
    cout << "Input array" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "Number of inversions: " << merge_sort(arr, 0, n - 1) << endl;

    cout << "\nArray sorted using merge sort" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}*/