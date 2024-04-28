#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void bubblesort_s(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
void bubblesort_p(int arr[], int n)
{
	for (int i = 0; i < n - 1; ++i)
	{
#pragma omp parallel for
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}
void showArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main()
{
	int size = 5;

	int arr_s[size] = {1, 4, 2, 5, 3};
	int arr_p[size] = {1, 4, 2, 5, 3};

	double start, stop, result;

	start = omp_get_wtime();
	bubblesort_s(arr_s, size);
	stop = omp_get_wtime();
	result = stop - start;
	cout << "Time req by seq is " << result << "\n";
	cout << "Sorted array ";
	showArray(arr_s, size);

	start = omp_get_wtime();
#pragma omp parallel num_threads(4)
	{
		bubblesort_p(arr_p, size);
	}
	stop = omp_get_wtime();
	result = stop - start;
	cout << "Time req by parallel is " << result << "\n";
	cout << "Sorted array ";
	showArray(arr_p, size);
	return 0;
}