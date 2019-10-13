#include "main.h"
#define waitState 0
#define onRidePremier 1
#define onRidePoolFull 2
#define onRidePoolHalf 3

#define premier 10
#define pool 11

#define YELLOW "\033[1;33m" // for cabs
#define GREEN "\033[0;32;32m" // for passengers
#define NONE "\033[m"  // for payment servers

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

int total_passengers_left;

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
        c[i].cab_number = i;
        c[i].ride_status =  waitState;
        c[i].lock = 0;
        printf(YELLOW"Cab Number %d ready for service\n", c[i].cab_number);
    }
    printf(YELLOW"All the cabs are ready for service \n");
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
        printf(GREEN"passenger %d PREMIER cab\n", passenger->passenger_number);
        passenger->ride_type = premier; // premier
    }
    else
    {
        printf(GREEN"passenger %d POOL cab\n", passenger->passenger_number);
        passenger->ride_type = pool; // pool
    }
    take_cab(passenger->passenger_number);
    
    printf(GREEN"PASSENGER %d IS LEAVING", passenger->passenger_number);
    pthread_exit(NULL);
}


pthread_mutex_t mutex_for_passenger_cab = PTHREAD_MUTEX_INITIALIZER;

void take_cab(int passenger_number)
{
    printf(GREEN"passenger %d wait-max %d time\n", p[passenger_number].passenger_number, p[passenger_number].wait_time);
    
    pthread_mutex_lock(&mutex_for_passenger_cab);
    int time_to_wait = p[passenger_number].wait_time;

    int state_being_searched_for = p[passenger_number].ride_type;
    int cab_found = -1 ;
    if(state_being_searched_for == pool)
    {
        while(cab_found < 0 && time_to_wait >0)
        {
            printf(GREEN"passenger %d wait-left : %d\n", passenger_number, time_to_wait);
            sleep(0.5); // buffer time so that cab can be found
            time_to_wait--;
            for(int i = 0  ; i <n ; i++)  // n is the number of active cabs
            {
                if(c[i].lock == 0)
                {
                    if(c[i].ride_status == onRidePoolHalf)
                    {
                        c[i].ride_status = onRidePoolFull;
                        c[i].lock = 1;
                        cab_found = i;
                        printf(GREEN"passenger %d is starting pool cab (which was already in pool) with cab number %d - Ride is %d long\n", passenger_number, c[cab_found].cab_number, p[passenger_number].ride_time);
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
                        printf(GREEN"passenger %d is starting single pool cab with cab number %d - Ride is %d long\n", passenger_number, c[cab_found].cab_number, p[passenger_number].ride_time);

                        break;
                    }
                }
            }
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
                    printf(GREEN"passenger %d is starting premier cab with cab number %d - Ride is %d long\n", passenger_number, c[cab_found].cab_number, p[passenger_number].ride_time);
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
        printf(GREEN"Passenger %d didn't find a cab, leaving the system \n", passenger_number);
        total_passengers_left--;
        return ;
    }
    else
    {
        c[cab_found].lock = 0; // release the lock for further bookings if any
        sleep(p[passenger_number].ride_time);
        printf(YELLOW"Ride for cab %d is over: will wait for payment\n", cab_found);
        do_payment(cab_found, c[cab_found].ride_status, passenger_number);
    }
    return;
}

struct payment_servers{
    int cab_number;
    int reduce_status_to;
    int payment_status;
};

volatile struct payment_servers pay[500];
int current_empty_pay_slot = 0;


void init_all_payment_servers()
{
    for(int i = 0; i<500 ; i++)
    {
        pay[i].payment_status = 0;
    }
    return;
}



pthread_mutex_t mutex_for_payment = PTHREAD_MUTEX_INITIALIZER;


void do_payment(int cab_number, int status, int passenger_number)
{
    pthread_mutex_lock(&mutex_for_payment);
    printf(YELLOW"One cab ride for cab %d has ended\n", cab_number);
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
    wait_for_payment(cab_slot);
    printf(NONE"PAYMENT CONFIRMEND FOR CAB SLOT %d: PASSENGER NUMBER%d\n", pay[cab_slot].cab_number, passenger_number);
    return;
}

void wait_for_payment(int cab_slot)
{
    // printf("in the wait for payment function for cab_slot %d cab number %d\n", cab_slot , pay[cab_slot].cab_number);
    while(pay[cab_slot].payment_status == 1);
    return;
}

pthread_t server_tids[100];

void init_all_servers(int n)
{
    for (int  i = 0; i < n; i++)
    {
        pthread_create(&server_tids[i], NULL, server_in_action, NULL);
    }
    printf(NONE"All payment servers threads are active\n");
    return;
}

pthread_mutex_t mutex_for_payment_server = PTHREAD_MUTEX_INITIALIZER;

void * server_in_action(void * arg)
{
    // the server is here, so we will make a lock and try and find a server that is to be paed
    for(int i = 0 ; ; i =  (++i)%500)
    {
        if(total_passengers_left <= 0)
        {
            pthread_exit(NULL);
        }
        pthread_mutex_lock(&mutex_for_payment_server);
        if(pay[i].payment_status == 1)
        {
            // payment was pending
            c[pay[i].cab_number].ride_status = pay[i].reduce_status_to;
            sleep(2);
            pay[i].payment_status = 0;
            total_passengers_left -= 1;
            // printf(NONE"payment has been made for cab number %d : Cab slot number %d\n", pay[i].cab_number, i);
            // payment has been done, so great
        }
        pthread_mutex_unlock(&mutex_for_payment_server);
        sleep(0.01);
    }
}



void wait_for_passengers_to_be_over(int k)
{
    for (int i = 0; i < k; i++)
    {
        pthread_join(server_tids[i], NULL);
    }
    return;
}

int main()
{

    srand((unsigned)time(NULL)); // this is for giving proper random numbers for the values that we need for the servings
    init_all_payment_servers();
    printf(YELLOW"Enter the number of cabs\n");
    if(scanf("%d", &n));

    printf(GREEN"Enter the number of passengers that will be coming\n");
    if(scanf("%d", &m));

    printf(NONE"Enter the number of payment servers\n");
    if(scanf("%d", &k));

    total_passengers_left = m;

    init_all_cabs(n);
    init_all_servers(k);
    bring_in_passengers(m);
 
    wait_for_passengers_to_be_over(k);
    printf("WE ARE DONE FOR THE DAY ! :)\n\n\n");
    return 0;
}