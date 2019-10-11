#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

extern int n,m,k;

int get_random_number_between(int a, int b);

void initialise_all_tables(int n);

void initialise_all_chefs(int m);

void bring_in_all_students(int k);