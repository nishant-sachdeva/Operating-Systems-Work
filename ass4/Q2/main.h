#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

extern int n,m,k;

int get_random_number_between(int a, int b);

int min(int a, int b);

void initialise_all_tables(int n);

void initialise_all_chefs(int m);

void bring_in_all_students(int k);


void make_biryani(int chef_number);

void serve_biryani(int chef_number);

void* start_cooking(void * arg);

void init_all_chefs(int m);

void * start_fetching(void * arg);

void init_all_containers(int n);

void ready_to_serve(int container_number);

int get_biryani_from_handler(int container_number);

int go_fetch_slot(int student_number);

void student_in_slot(int student_number, int container_number);

void* wait_for_slot(void  *arg);

void bring_all_students(int k);

void wait_for_threads_to_end();
