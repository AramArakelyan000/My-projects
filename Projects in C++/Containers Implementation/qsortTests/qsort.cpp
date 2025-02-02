    #include <iostream>
#include <cstdlib>

int compare(const void* a, const void* b) {
    int arg1 = *static_cast<const int*>(a);
    int arg2 = *static_cast<const int*>(b);
    return (arg1 > arg2) - (arg1 < arg2);
}

int main() {
    int arr[] = {5, 2, 9, 1, 5, 6};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    qsort(arr, n, sizeof(int), compare);

    for (size_t i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}
