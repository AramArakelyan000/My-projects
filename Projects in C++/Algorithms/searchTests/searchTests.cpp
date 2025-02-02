#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include <string>

using namespace std;
using namespace std::chrono;

// ------------------------------- SEARCH ALGORITHMS ------------------------------- //

// 1. Linear Search
int linear_search(const vector<int>& arr, int x) {
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] == x) return i;
    }
    return -1;
}

// 2. Binary Search
int binary_search(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) return mid;
        if (arr[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 3. Jump Search
int jump_search(const vector<int>& arr, int x) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }
    for (int i = prev; i < min(step, n); ++i) {
        if (arr[i] == x) return i;
    }
    return -1;
}

// 4. Interpolation Search
int interpolation_search(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    while (low <= high && x >= arr[low] && x <= arr[high]) {
        int pos = low + (((double)(high - low) / (arr[high] - arr[low])) * (x - arr[low]));
        if (arr[pos] == x) return pos;
        if (arr[pos] < x) low = pos + 1;
        else high = pos - 1;
    }
    return -1;
}

// 5. Ternary Search
int ternary_search(const vector<int>& arr, int x) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        if (arr[mid1] == x) return mid1;
        if (arr[mid2] == x) return mid2;
        if (x < arr[mid1]) high = mid1 - 1;
        else if (x > arr[mid2]) low = mid2 + 1;
        else {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }
    return -1;
}

// 6. Exponential Search
int exponential_search(const vector<int>& arr, int x) {
    int n = arr.size();
    if (arr[0] == x) return 0;
    int i = 1;
    while (i < n && arr[i] <= x) i *= 2;
    return binary_search(vector<int>(arr.begin() + i / 2, arr.begin() + min(i, n)), x);
}

// ------------------------------- ARRAY GENERATION ------------------------------- //

void generate_linear(int n, vector<int>& arr) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
}

void generate_quadratic(int n, vector<int>& arr) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) arr[i] = i * i;
}

void generate_random(int n, int max_value, vector<int>& arr) {
    arr.resize(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, max_value);
    for (int i = 0; i < n; ++i) arr[i] = dis(gen);
    sort(arr.begin(), arr.end());
}

// ------------------------------- TIMER CLASS ------------------------------- //

class Timer {
public:
    Timer(const string& name) : m_name(name), start(steady_clock::now()) {}
    ~Timer() {
        auto end = steady_clock::now();
        cout << m_name << ": " << duration_cast<nanoseconds>(end - start).count() << " ns" << endl;
    }

private:
    string m_name;
    time_point<steady_clock> start;
};

// ------------------------------- TESTING ------------------------------- //

void test_search(const vector<int>& arr, int x) {
    {
        Timer t("Linear Search");
        linear_search(arr, x);
    }
    {
        Timer t("Binary Search");
        binary_search(arr, x);
    }
    {
        Timer t("Jump Search");
        jump_search(arr, x);
    }
    {
        Timer t("Interpolation Search");
        interpolation_search(arr, x);
    }
    {
        Timer t("Ternary Search");
        ternary_search(arr, x);
    }
    {
        Timer t("Exponential Search");
        exponential_search(arr, x);
    }
}

// ------------------------------- MAIN ------------------------------- //

int main() {
    int n = 1000000;
    int x = 99599;

    cout << "Linear Array Tests:\n";
    vector<int> linear_array;
    generate_linear(n, linear_array);
    test_search(linear_array, x);

    cout << "\nQuadratic Array Tests:\n";
    vector<int> quadratic_array;
    generate_quadratic(n, quadratic_array);
    test_search(quadratic_array, x * x);

    cout << "\nRandom Array Tests:\n";
    vector<int> random_array;
    generate_random(n, 100000, random_array);
    test_search(random_array, random_array[n / 2]);

    return 0;
}
