#include<stdio.h>

#define get(a) int a; scanf("%d", &a);


void quick_sort(int arr[])
{
    /*here the code for a normal quicksort will lie*/
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

    quick_sort(arr);
    for(int i = 0 ; i<n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
    
}
