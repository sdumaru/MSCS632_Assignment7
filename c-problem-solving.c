#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int cmp_int(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

// Function to calculate the mean
double calculate_mean(int arr[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum / size;
}

// Function to calculate the median
double calculate_median(int *arr, int size)
{
    // Sort a copy to not modify the original array if needed elsewhere,
    // or sort in place if modification is acceptable.
    // Let's sort in place for simplicity here.
    qsort(arr, size, sizeof(int), cmp_int);
    if (size % 2 == 1)
    {
        return (double)arr[size / 2];
    }
    else
    {
        int mid1 = arr[size / 2 - 1];
        int mid2 = arr[size / 2];
        return (double)(mid1 + mid2) / 2.0;
    }
}

// Function to calculate the mode
void calculate_mode(int arr[], int size)
{
    // Sort the array to group identical elements
    qsort(arr, size, sizeof(int), cmp_int);

    int maxCount = 1, currCount = 1;
    int modes[size], modeCount = 0;
    for (int i = 1; i < size; i++)
    {
        if (arr[i] == arr[i - 1])
        {
            currCount++;
        }
        else
        {
            if (currCount > maxCount)
            {
                maxCount = currCount;
                modeCount = 0;
                modes[modeCount++] = arr[i - 1];
            }
            else if (currCount == maxCount)
            {
                modes[modeCount++] = arr[i - 1];
            }
            currCount = 1;
        }
    }
    // check last run
    if (currCount > maxCount)
    {
        maxCount = currCount;
        modeCount = 0;
        modes[modeCount++] = arr[size - 1];
    }
    else if (currCount == maxCount)
    {
        modes[modeCount++] = arr[size - 1];
    }

    printf("Mode (%d occurrence%s): ", maxCount, maxCount > 1 ? "s" : "");
    for (int i = 0; i < modeCount; i++)
    {
        printf("%d%s", modes[i], i + 1 < modeCount ? ", " : "");
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        fprintf(stderr, "Invalid size\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr)
    {
        perror("malloc");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    double m = calculate_mean(arr, n);
    double med = calculate_median(arr, n);

    printf("Mean:   %.2f\n", m);
    printf("Median: %.2f\n", med);
    calculate_mode(arr, n);

    free(arr);
    return 0;
}
