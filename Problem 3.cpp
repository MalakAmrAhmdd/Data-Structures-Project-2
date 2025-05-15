#include <bits/stdc++.h>
using namespace std;

int flip(int n, int *arr, int k) {
    int count = 0;
    for (int i = 0; i <= n - k; i++) {
        if (arr[i] == 0) {
            for (int j = i; j < i + k; j++) {
                arr[j] = 1 - arr[j];
            }
            count++;
        }
    }
    return count;
}

int main() {
    ifstream inFile("Problem 3.txt");
    if (!inFile) {
        cerr << "Cannot open file.\n";
        return 1;
    }

    int n, k;
    int i = 0;
    while (inFile >> n >> k) {
        cout << "Test " << ++i << '\n';
        int* arr = new int[n];  // dynamic array

        for (int i = 0; i < n; i++) {
            if (!(inFile >> arr[i])) {
                cerr << "Invalid input format.\n";
                delete[] arr;
                return 1;
            }
        }

        cout << "The elements of the array are: ";
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
        cout << '\n' << "The length of the segment is: " << k << '\n';

        int ans = flip(n, arr, k);

        cout << "The minimum number of segment flips required to turn all elements into 1 is: ";
        cout << ans << endl;

        delete[] arr;  // free memory
        cout << '\n';
    }

    return 0;
}