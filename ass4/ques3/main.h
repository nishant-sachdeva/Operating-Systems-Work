#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>


int get_random_number_between(int  a, int b);

int min(int a, int b);

void init_all_cabs(int n);

void bring_in_passengers(int m);

void * passenger_init(void * arg);

void take_cab(int passenger_number);

void init_all_payment_servers();

void do_payment(int cab_number, int status);

void init_all_servers(int n);

void * server_in_action(void * arg);

void wait_for_passengers_to_be_over(int k);