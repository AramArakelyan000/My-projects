#include <iostream>

template <typename T>
T median_of_three(T& a, T& b, T& c) {
    if ((a > b) ^ (a > c)) return a;
    else if ((b > a) ^ (b > c)) return b;
    return c;
}

template <typename T>
void quick_sort(T arr[], int left, int right) {
    if (left >= right) return;
    
    
    int mid = left + (right - left) / 2;
    T p = median_of_three(arr[left], arr[mid], arr[right]);
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] < p) ++i;
        while (arr[j] > p) --j;

        if (i <= j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        }
    }

    quick_sort(arr, left, j);
    quick_sort(arr, i, right);
}

template <typename T>
void print_array(T arr[], int size) {
    if (size <= 0) {
        std::cout << "Array is empty" << std::endl;
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {3, 5, 67, 3, 0, 4, 22, 6};
    int size = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Before sorting: ";
    print_array(arr, size);

    quick_sort(arr, 0, size - 1);

    std::cout << "After sorting: ";
    print_array(arr, size);

    return 0;
}
