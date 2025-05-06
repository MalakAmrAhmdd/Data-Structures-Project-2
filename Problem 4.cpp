#include <bits/stdc++.h>
using namespace std;

int flip(int n, vector<int> &arr, int k) {
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

int main(){
    ifstream inFile("Problem 3.txt");
    if (!inFile) {
        cerr << "Cannot open file.\n";
        return 1;
    }
    int k;
    vector<int> arr;
    inFile >> k;

    int x;
    while (inFile >> x) {
        arr.push_back(x);
    }

    int n = arr.size();
    int ans = flip(n, arr, k);
    cout << "The minimum number of segment flips required to turn all elements in arr into 1 is: ";
    if (ans) cout << ans << endl;
    else cout << -1 << endl;

}
