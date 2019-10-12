#include "main.h"
#define waitState 0
#define onRidePremier 1
#define onRidePoolFull 2
#define onRidePoolHalf 3

#define premier 10
#define pool 11

int get_random_number_between(int  a, int b)
{
    if(b == a)
        b = a+5;
    int ans = (rand()%(b - a) + a); // assuming a is smaller
    return ans;
}

int min(int a, int b)
{
    return a<b?a:b;
}



int n; // the number of cabs
int m; // the number of passengers
int k; // the number of payment servers

//////////////////
// CABS SECITON

struct cabs
{
    int lock; // so that noone else books it until I am dealing with it or initing it or anything
    int cab_number; // cab_number
    int ride_status; // whether what is the status
};

struct cabs c[100];

void init_all_cabs(int n)
{
    // as it turns out , cabs don't need to be separate threads
    for(int i = 0; i<n ; i++)
    {
        // just init with a cab number
        c[i].cab_number = i+1;
        c[i].ride_status =  waitState;
        c[i].lock = 0;
        printf("Cab Number %d ready for service\n", c[i].cab_number);
    }
    printf("All the cabs are ready for service \n");
    return;
}

struct passengers{
    int passenger_number;
    int ride_time;
    int wait_time;
    int ride_type;
};

struct passengers p[100];

pthread_t passenger_tids[100];

void bring_in_passengers(int m)
{
    // here i need to make threads of the passengers and send them to the init function wherefrom tehy will be sent to the ride paths

    for(int i = 0 ;i<m ; i++)
    {
        p[i].passenger_number = i; // this gives the chef number
        pthread_create(&passenger_tids[i], NULL, passenger_init, &p[i]);
        int time = get_random_number_between(2,5);
        sleep(time);
    }
    return;
}


void * passenger_init(void * arg)
{
    struct passengers * passenger = (struct passengers*) arg;
    // now I have the passenger
    passenger->ride_time = 4;
    passenger->wait_time = 20;
    if(passenger->passenger_number % 2 == 0)
    {
        passenger->ride_type = premier; // premier
    }
    else
    {
        passenger->ride_type = pool; // pool
    }
    printf("passenger %d has arrived and wants a %d cab\n", passenger->passenger_number, passenger->ride_type);
    take_cab(passenger->passenger_number);
    
    printf("passenger %d is leaving\n", passenger->passenger_number);
    pthread_exit(NULL);
}


pthread_mutex_t mutex_for_passenger_cab = PTHREAD_MUTEX_INITIALIZER;

void take_cab(int passenger_number)
{
    printf("passenger %d will wait for at max %d time before leaving\n", p[passenger_number].passenger_number, p[passenger_number].wait_time);
    int time_to_wait = p[passenger_number].wait_time;
    pthread_mutex_lock(&mutex_for_passenger_cab);
    int state_being_searched_for = p[passenger_number].ride_type;
    int cab_found = -1 ;
    if(state_being_searched_for == pool)
    {
        while(cab_found < 0 && time_to_wait >0)
        {
            sleep(0.5);
            for(int i = 0  ; i <n ; i++)
            {
                if(c[i].lock == 0)
                {
                    if(c[i].ride_status == onRidePoolHalf)
                    {
                        c[i].ride_status = onRidePoolFull;
                        c[i].lock = 1;
                        cab_found = i;
                        break;
                    }
                }
            }

            for(int i = 0;  i<n ; i++)
            {
                if(c[i].lock == 0)
                {
                    if(c[i].ride_status == waitState)
                    {
                        c[i].lock = 1;
                        c[i].ride_status = onRidePoolHalf ;
                        cab_found = i;
                        break;
                    }
                }
            }
            time_to_wait--;
        }
    }
    else
    {
        for(int i = 0; time_to_wait > 0  ; i = (++i)%n)
        {
            // this is an inf loop and we are looking for a prem ride
            if(c[i].lock == 0)
            {
                if(c[i].ride_status == waitState)
                {
                    // this is our cab
                    c[i].lock = 1;
                    c[i].ride_status = onRidePremier;
                    cab_found = i;
                    break;
                }
            }
            time_to_wait--;
            sleep(0.5);
        }
        // keep inf search for premier
    }
    
    pthread_mutex_unlock(&mutex_for_passenger_cab);
    if(cab_found < 0)
    {
        printf("Passenger %d didn't find a cab, leaving the system \n", passenger_number);
        return ;
    }
    else
    {
        printf("passenger %d is starting cab with cab number %d. Ride is %d long\n", passenger_number, c[cab_found].cab_number, p[passenger_number].ride_time);
        c[cab_found].lock = 0; // release the lock for further bookings if any
        sleep(p[passenger_number].ride_time);
        printf("now cab %d will wait for payment\n", cab_found);
        do_payment(cab_found, c[cab_found].ride_status);
    }
    return;
}

struct payment_servers{
    int cab_number;
    int reduce_status_to;
    int payment_status;
};

struct payment_servers pay[500];
int current_empty_pay_slot = 0;


void init_all_payment_servers()
{
    for(int i = 0; i<500 ; i++)
    {
        pay[i].payment_status = 0;
    }
    return;
    // now we can just keep paying and be fine
    // I am assuming that there won't be a total number of payments more than 500;
}



pthread_mutex_t mutex_for_payment = PTHREAD_MUTEX_INITIALIZER;


void do_payment(int cab_number, int status)
{
    pthread_mutex_lock(&mutex_for_payment);
    pay[current_empty_pay_slot].payment_status = 1;
    pay[current_empty_pay_slot].cab_number = cab_number;
    if(status == onRidePoolFull )
    {
        pay[current_empty_pay_slot].reduce_status_to = onRidePoolHalf;
    }
    else if( status == onRidePoolHalf)
    {
        pay[current_empty_pay_slot].reduce_status_to = waitState;
    }
    else if (status == onRidePremier)
    {
        pay[current_empty_pay_slot].reduce_status_to = waitState;
    }
    // now we know everything , now we just need to wait for the payment to happen
    current_empty_pay_slot++;
    int cab_slot = current_empty_pay_slot -1;
    pthread_mutex_unlock(&mutex_for_payment);
    printf("cab %d is waiting for payment\n", cab_number);
    while(pay[cab_slot].payment_status == 1); // wait for payment to reduce
    return;
}

pthread_t server_tids[100];

void init_all_servers(int n)
{
    for (int  i = 0; i < n; i++)
    {
        pthread_create(&server_tids[i], NULL, server_in_action, NULL);
    }
    return;
}


void * server_in_action(void * arg)
{
    // the server is here, so we will make a lock and try and find a server that is to be paed
    pthread_mutex_lock(&mutex_for_payment);
    for(int i = 0 ; ; i =  (++i)%500)
    {
        if(pay[i].payment_status == 1)
        {
            // payment was pending
            printf("payment has been made for cab number %d \n", pay[i].cab_number);
            c[pay[i].cab_number].ride_status = pay[i].reduce_status_to;
            sleep(2);
            pay[i].payment_status = 0;
            break;
        }
    }
    pthread_mutex_unlock(&mutex_for_payment);
    pthread_exit(NULL);
}



void wait_for_passengers_to_be_over(int k)
{
    for (int i = 0; i < k; i++)
    {
        pthread_join(passenger_tids[i], NULL);
    }
    return;
}

int main()
{

    srand((unsigned)time(NULL)); // this is for giving proper random numbers for the values that we need for the servings
    init_all_payment_servers();
    printf("Enter the number of cabs\n");
    if(scanf("%d", &n));

    printf("Enter the number of passengers that will be coming\n");
    if(scanf("%d", &m));

    printf("Enter the number of payment servers\n");
    if(scanf("%d", &k));

    init_all_cabs(n);
    init_all_servers(k);
    bring_in_passengers(m);
 
    wait_for_passengers_to_be_over(k);
    printf("WE ARE DONE FOR THE DAY ! :)\n\n\n");
    return 0;
}