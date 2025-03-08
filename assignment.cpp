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

// Modified Binary Search to return the first occurrence of the key
int binarySearchFirst(vector<int> &arr, int key) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            result = mid;
            // Continue search on the left side for the first occurrence
            right = mid - 1;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Modified Interpolation Search to return the first occurrence of the key
int interpolationSearchFirst(vector<int> &arr, int key) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    while (left <= right && key >= arr[left] && key <= arr[right]) {
        if (left == right) {
            if (arr[left] == key)
                return left;
            else
                break;
        }
        // Avoid division by zero
        if (arr[right] == arr[left])
            break;
            
        int pos = left + (int)(((double)(right - left) / (arr[right] - arr[left])) * (key - arr[left]));
        if (pos < left || pos > right)
            break;
        if (arr[pos] == key) {
            result = pos;
            // Continue search on the left side to find earlier occurrence
            right = pos - 1;
        } else if (arr[pos] < key) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    return result;
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
    
    string sortAlgorithm;
    // Measure sorting time
    auto sort_start = high_resolution_clock::now();
    if (choice == 1) {
        sortAlgorithm = "Selection Sort";
        selectionSort(arr);
    } else if (choice == 2) {
        sortAlgorithm = "Merge Sort";
        mergeSort(arr, 0, N - 1);
    } else {
        cout << "Invalid choice!";
        return 0;
    }
    auto sort_end = high_resolution_clock::now();
    auto sort_duration = duration_cast<milliseconds>(sort_end - sort_start).count();
    
    cout << "Array sorted using " << sortAlgorithm << ": ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    cout << sortAlgorithm << " took " << sort_duration << " ms" << endl;
    
    cout << "Choose search algorithm: \n1. Binary Search \n2. Interpolation Search\nChoice: ";
    cin >> choice;
    
    int key;
    cout << "Enter element to search: ";
    cin >> key;
    
    string searchAlgorithm;
    // Measure search time
    auto search_start = high_resolution_clock::now();
    int index = -1;
    if (choice == 1) {
        searchAlgorithm = "Binary Search";
        index = binarySearchFirst(arr, key);
    } else if (choice == 2) {
        searchAlgorithm = "Interpolation Search";
        index = interpolationSearchFirst(arr, key);
    } else {
        cout << "Invalid choice!";
        return 0;
    }
    auto search_end = high_resolution_clock::now();
    auto search_duration = duration_cast<microseconds>(search_end - search_start).count();
    
    if (index != -1) {
        // Check if there are duplicates by verifying if the next element is the same
        if (index + 1 < arr.size() && arr[index] == arr[index + 1]) {
            cout << "Element found at first occurrence index " << index << " using " << searchAlgorithm << endl;
        } else {
            cout << "Element found at index " << index << " using " << searchAlgorithm << endl;
        }
    } else {
        cout << "Element not found using " << searchAlgorithm << "!" << endl;
    }
    cout << searchAlgorithm << " took " << search_duration << " microseconds" << endl;
    
    return 0;
}
