#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <thread>

using namespace std;

// Insertion sort
template <typename T>
void insertionSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Shell sort
template <typename T>
void shellSort(vector<T>& arr) {
    int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

// Merge sort
template <typename T>
void merge(vector<T>& arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<T> L(n1), R(n2);
    for (i = 0; i < n1; i++) {
        L[i] = arr[l+i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m+1+j];
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSortHelper(vector<T>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

template <typename T>
void mergeSort(vector<T>& arr) {
    int n = arr.size();
    mergeSortHelper(arr, 0, n-1);
}

// Quick sort
template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

template <typename T>
void quickSortHelper(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi-1);
        quickSortHelper(arr, pi+1, high);
    }
}

template <typename T>
void quickSort(vector<T>& arr) {
    int n = arr.size();
    quickSortHelper(arr, 0, n-1);
}

vector<int> presorted(int n) {
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = i+1;
    }
    return arr;
}

vector<int> revsorted(int n) {
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = n-i;
    }
    return arr;
}

vector<int> randomfewdup(int n) {
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = rand()%n;
    }
    return arr;
}

vector<int> manysame(int n) {
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = rand()%10;
    }
    return arr;
}

vector<int> alldup(int n) {
    vector<int> arr(n, 0);
    return arr;
}

template <typename T>
void test_sorting(vector<T>& arr, int n) {
    vector<T> arr_copy;
    double time_taken;
    const double MAX_TIME = 30.0; // Maximum time allowed in seconds
    cout << "Running tests on array of size " << n << endl;

    // insertion sort
    arr_copy = arr;
    auto start = chrono::steady_clock::now();
    bool timeout = false;
    for (int i = 0; i < n && !timeout; i++) {
        insertionSort(arr_copy);
        auto end = chrono::steady_clock::now();
        time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6;
        if (time_taken > MAX_TIME) {
            timeout = true;
        }
    }
    if (timeout) {
        cout << "Insertion sort timed out." << endl;
    } else {
        cout << "Insertion sort took " << time_taken << " seconds." << endl;
    }

    // shell sort
    arr_copy = arr;
    start = chrono::steady_clock::now();
    timeout = false;
    for (int i = 0; i < n && !timeout; i++) {
        shellSort(arr_copy);
        auto end = chrono::steady_clock::now();
        time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6;
        if (time_taken > MAX_TIME) {
            timeout = true;
        }
    }
    if (timeout) {
        cout << "Shell sort timed out." << endl;
    } else {
        cout << "Shell sort took " << time_taken << " seconds." << endl;
    }

    // merge sort
    arr_copy = arr;
    start = chrono::steady_clock::now();
    timeout = false;
    for (int i = 0; i < n && !timeout; i++) {
        mergeSort(arr_copy);
        auto end = chrono::steady_clock::now();
        time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6;
        if (time_taken > MAX_TIME) {
            timeout = true;
        }
    }
    if (timeout) {
        cout << "Merge sort timed out." << endl;
    } else {
        cout << "Merge sort took " << time_taken << " seconds." << endl;
    }

    // quick sort
    arr_copy = arr;
    start = chrono::steady_clock::now();
    timeout = false;
    for (int i = 0; i < n && !timeout; i++) {
        quickSort(arr_copy);
        auto end = chrono::steady_clock::now();
        time_taken = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1e6;
        if (time_taken > MAX_TIME) {
            timeout = true;
        }
    }
    if (timeout) {
        cout << "Quick sort timed out." << endl;
    } else {
        cout << "Quick sort took " << time_taken << " seconds." << endl;
    }
}



int main() {
    //srand(time(NULL)); // seed the random number generator

    // Test on pre-sorted array
    for(int n : {100, 1000, 10000}) {
        vector<int> arr = presorted(n);
        cout << "Testing on pre-sorted array of size " << n << endl;
        test_sorting(arr, n);
    }

    // Test on reverse-sorted array
    for(int n : {100, 1000, 10000}) {
        vector<int> arr = revsorted(n);
        cout << "Testing on reverse-sorted array of size " << n << endl;
        test_sorting(arr, n);
    }

    // Test on random array with few duplicates
    for(int n : {100, 1000, 10000}) {
        vector<int> arr = randomfewdup(n);
        cout << "Testing on random array with few duplicates of size " << n << endl;
        test_sorting(arr, n);
    }

    // Test on array with many duplicates
    for(int n : {100, 1000, 10000}) {
        vector<int> arr = manysame(n);
        cout << "Testing on array with many duplicates of size " << n << endl;
        test_sorting(arr, n);
    }

    // Test on array of all duplicates
    for(int n : {100, 1000, 10000}) {
        vector<int> arr = alldup(n);
        cout << "Testing on array of all duplicates of size " << n << endl;
        test_sorting(arr, n);
    }
    
    

    return 0;
}
