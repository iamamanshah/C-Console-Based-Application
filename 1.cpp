#include <iostream>
#include <vector>
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time()
#include <algorithm>  // For swap()
#include <chrono>     // For timing

using namespace std;
using namespace std::chrono;

// Function to generate N random numbers
vector<int> generateRandomNumbers(int N) {
    vector<int> arr;
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < N; i++) {
        arr.push_back(rand() % 100); // Generate random numbers between 0 and 99
    }
    return arr;
}

// Selection Sort Algorithm
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

// Merge Sort Functions
void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) 
        R[i] = arr[mid + 1 + i];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) 
            arr[k++] = L[i++];
        else 
            arr[k++] = R[j++];
    }
    while (i < n1) 
        arr[k++] = L[i++];
    while (j < n2) 
        arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Binary Search Algorithm
int binarySearch(vector<int> &arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) 
            return mid;
        else if (arr[mid] < key) 
            left = mid + 1;
        else 
            right = mid - 1;
    }
    return -1;
}

// Interpolation Search Algorithm
int interpolationSearch(vector<int> &arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right && key >= arr[left] && key <= arr[right]) {
        if (left == right) {
            if (arr[left] == key) 
                return left;
            return -1;
        }
        int pos = left + (((double)(right - left) / (arr[right] - arr[left])) * (key - arr[left]));
        if (arr[pos] == key) 
            return pos;
        if (arr[pos] < key) 
            left = pos + 1;
        else 
            right = pos - 1;
    }
    return -1;
}

int main() {
    int N;
    cout << "Enter the number of elements: ";
    cin >> N;
    
    vector<int> arr = generateRandomNumbers(N);
    
    cout << "Generated Array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    
    int choice;
    cout << "Choose sorting algorithm: \n1. Selection Sort \n2. Merge Sort\nChoice: ";
    cin >> choice;
    
    // Measure sorting time
    auto sort_start = high_resolution_clock::now();
    if (choice == 1) {
        selectionSort(arr);
        cout << "Array sorted using Selection Sort: ";
    } else if (choice == 2) {
        mergeSort(arr, 0, N - 1);
        cout << "Array sorted using Merge Sort: ";
    } else {
        cout << "Invalid choice!";
        return 0;
    }
    auto sort_end = high_resolution_clock::now();
    auto sort_duration = duration_cast<milliseconds>(sort_end - sort_start).count();
    
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    cout << "Time taken for sorting: " << sort_duration << " ms" << endl;
    
    cout << "Choose search algorithm: \n1. Binary Search \n2. Interpolation Search\nChoice: ";
    cin >> choice;
    
    int key;
    cout << "Enter element to search: ";
    cin >> key;
    
    // Measure search time
    auto search_start = high_resolution_clock::now();
    int index = -1;
    if (choice == 1) {
        index = binarySearch(arr, key);
    } else if (choice == 2) {
        index = interpolationSearch(arr, key);
    } else {
        cout << "Invalid choice!";
        return 0;
    }
    auto search_end = high_resolution_clock::now();
    auto search_duration = duration_cast<microseconds>(search_end - search_start).count();
    
    if (index != -1) {
        cout << "Element found at index " << index << endl;
    } else {
        cout << "Element not found!" << endl;
    }
    cout << "Time taken for searching: " << search_duration << " microseconds" << endl;
    
    return 0;
}
