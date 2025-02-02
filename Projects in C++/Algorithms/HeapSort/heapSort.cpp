#include <iostream>
#include <algorithm>

template <typename T>
void heap_sort(T arr[], int n) {

    for (int i = n - 1; i > 0; --i) {
        int j = (i - 1) / 2;

        if (arr[i] > arr[j])
            std::swap(arr[i], arr[j]);
    }
    std::swap(arr[0], arr[n-1]);
    if (n > 1)
        heap_sort(arr, n - 1);
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    heap_sort(arr, n);

    std::cout << "sorted array: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}
