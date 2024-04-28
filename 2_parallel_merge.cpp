#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void merge(int arr[], int low, int mid, int high)
{
    int size = high - low + 1;
    int temp[size];
    int ptr1 = low;
    int ptr2 = mid + 1;
    int k = 0;

    while (ptr1 <= mid && ptr2 <= high)
    {
        if (arr[ptr1] < arr[ptr2])
        {
            temp[k] = arr[ptr1];
            ptr1++;
        }
        else
        {
            temp[k] = arr[ptr2];
            ptr2++;
        }
        k++;
    }

    while (ptr1 <= mid)
    {
        temp[k] = arr[ptr1];
        ptr1++;
        k++;
    }

    while (ptr2 <= high)
    {
        temp[k] = arr[ptr2];
        ptr2++;
        k++;
    }

    for (int i = 0; i < size; i++)
    {
        arr[low + i] = temp[i];
    }
}

void parallelMergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

#pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main()
{
    int n = 5;
    double start_time, end_time;
    int arr1[n] = {1, 4, 2, 5, 3};
    int arr2[n] = {1, 4, 2, 5, 3};

    start_time = omp_get_wtime();
    mergeSort(arr1, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";
    for (auto it : arr1)
    {
        cout << it << " ";
    }
    cout << endl;

    start_time = omp_get_wtime();
    parallelMergeSort(arr2, 0, n - 1);
    end_time = omp_get_wtime();
    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds\n";
    for (auto it : arr2)
    {
        cout << it << " ";
    }
    cout << endl;
    return 0;
}
