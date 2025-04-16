#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <algorithm>

const int PARALLEL_THRESHOLD = 100000; // Adjust this for performance tuning

void generateRandomArray(std::vector<int>& arr) {
    for (auto& val : arr) {
        val = rand();
    }
}

bool isSorted(const std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void merge(std::vector<int>& arr, int left, int mid, int right, std::vector<int>& temp) {
    int i = left;
    int j = mid + 1;
    int k = left;

    // Merge both halves into temp
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // Copy back to arr
    for (int i = left; i <= right; ++i) {
        arr[i] = temp[i];
    }
}

void parallelMergeSort(std::vector<int>& arr, int left, int right, std::vector<int>& temp) {
    if (left >= right) return;

    int mid = (left + right) / 2;

    if (right - left > PARALLEL_THRESHOLD) {
        std::thread leftThread(parallelMergeSort, std::ref(arr), left, mid, std::ref(temp));
        std::thread rightThread(parallelMergeSort, std::ref(arr), mid + 1, right, std::ref(temp));
        leftThread.join();
        rightThread.join();
    } else {
        parallelMergeSort(arr, left, mid, temp);
        parallelMergeSort(arr, mid + 1, right, temp);
    }

    merge(arr, left, mid, right, temp);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <array_size>" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    if (n <= 0) {
        std::cerr << "Array size must be positive.\n";
        return 1;
    }

    std::vector<int> arr(n);
    std::vector<int> temp(n);

    generateRandomArray(arr);

    auto start = std::chrono::high_resolution_clock::now();

    parallelMergeSort(arr, 0, n - 1, temp);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (isSorted(arr)) {
        std::cout << "Sorted " << n << " elements in " << duration_ms << " ms\n";
    } else {
        std::cerr << "Array not sorted correctly!\n";
    }

    return 0;
}
