#include<stdio.h>
#include<stdlib.h>

#define get(a) int a; scanf("%d", &a);


void insertion_sort(int arr[] , int low, int high)
{
    int n = high - low + 1;
    int j, key;
    for(int i = low+1 ; i<=(high) ; i++)
    {
        key = arr[i];
        j = i-1;
        while(j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
   
    return;
}


void swap(int * a,  int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    
    return;
}

int partition(int arr[], int low, int high)
{
    int pivot = rand()%high;
    if(pivot < low)
    {
        pivot = (low+high)/2;
    }

    swap( &arr[high], &arr[pivot] );
    int i = low - 1;
    for(int j = low ; j<= high -1 ; j++)
    {
        if(arr[j] < arr[high]) // because array[high] has the pivot element now
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);

    return i+1;
}

void quick_sort(int arr[], int low, int high)
{
    if( (high - low) <= 5 )
    {
        insertion_sort(arr, low, high);
        return;
    }
    if(low < high)
    {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi-1);
        quick_sort(arr, pi+1, high);
    }
    return;
}


int main()
{
    int arr[10000];
    get(n);
    for(int i = 0; i<n; i++)
    {
        get(ni);
        arr[i] = ni;
    }
    // now we have all the numbers of the array
    // now we can start the sorting

    quick_sort(arr, 0, n-1);
    //insertion_sort(arr, 0, n-1);

    for(int i = 0 ; i<n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
    
}
