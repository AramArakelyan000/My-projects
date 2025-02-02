#include <iostream>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

int fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

unordered_map<int, long long> memo;
long long fibonacci_memoization(int n) {
    if (n <= 1) return n;
    if (memo.find(n) != memo.end()) return memo[n];
    memo[n] = fibonacci_memoization(n - 1) + fibonacci_memoization(n - 2);
    return memo[n];
}

int main() {
    int n;
    cout << "Enter Fibonacci number index: ";
    cin >> n;

    auto start_recursive = high_resolution_clock::now();
    int result_recursive = fibonacci_recursive(n);
    auto end_recursive = high_resolution_clock::now();
    auto duration_recursive = duration_cast<microseconds>(end_recursive - start_recursive);

    cout << "Recursive method: " << result_recursive << endl;
    cout << "Execution time (microseconds): " << duration_recursive.count() << endl;

    auto start_memo = high_resolution_clock::now();
    long long result_memo = fibonacci_memoization(n);
    auto end_memo = high_resolution_clock::now();
    auto duration_memo = duration_cast<microseconds>(end_memo - start_memo);

    cout << "Memoization method: " << result_memo << endl;
    cout << "Execution time (microseconds): " << duration_memo.count() << endl;

    return 0;
}
