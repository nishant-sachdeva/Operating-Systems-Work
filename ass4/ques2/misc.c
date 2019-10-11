#include "main.h"

int get_random_number_between(int a, int b)
{
    int ans = rand()%(b  - a) + a ; //assuming a is the smaller
    return  ans;
}