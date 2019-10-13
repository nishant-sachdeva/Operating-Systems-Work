#include "main.h"

#define YELLOW "\033[1;33m"
#define GREEN "\033[0;32;32m"
#define NONE "\033[m"

/////////////////////////////////
// MISC FUNCTIONS

int get_random_number_between(int  a, int b)
{
    if(b == a)
        return a;
    int ans = rand()%(b - a) + a; // assuming a is smaller
    return ans;
}

int min(int a, int b)
{
    return a<b?a:b;
}

int m; // m is the number of chefs
int n; // n is the number of serving tables
int k; // k is the number of students

volatile int students_left_to_serve;
volatile int students_left_to_feed;

//////////////////////////////////////
// SECTION FOR CHEF FUNCTIONS

struct chefs{
    int r; // vessels
    int p; // capacity of single containers
    int cooking;  // cooking status
    int lock;   // cooking lock
    int chef_number; // chef_number for idying the chef
 };

struct chefs c[100];

pthread_t chef_tids[100];

void init_all_chefs(int m)
{

    for(int i = 0 ;i<m ; i++)
    {
        c[i].chef_number = i; // this gives the chef number
        pthread_create(&chef_tids[i], NULL, start_cooking, &c[i]);
    }
    printf(YELLOW"All chefs are active\n");
    return;
}


void* start_cooking(void * arg)
{
    struct chefs* chef = (struct chefs*)arg;
    //  now we have the  guy with us; we have to start  it's cooking
    //  procedure
    chef->cooking = 1; // set the cooking status as 1
    chef->lock = 0;  // make it available for access
    chef->r = 0;
    chef->p = 0;
    printf(YELLOW"Robot chef %d ready to go\n", chef->chef_number);
    while(students_left_to_serve > 0)
    {
        printf(NONE"Chef %d going to make food. students left to serve are %d\n",chef->chef_number, students_left_to_serve);
        make_biryani(chef->chef_number);
        serve_biryani(chef->chef_number);
    }
    printf(YELLOW"Robot chef %d leaving. Students left to serve are %d\n", chef->chef_number,students_left_to_serve);
    pthread_exit(0);
}

void make_biryani(int chef_number)
{
    c[chef_number].cooking = 1;
    c[chef_number].lock = 1; 

    // so that noone uses it while it is serving

    int r = get_random_number_between(1, 10); // number of vessels
    int temp = min(10,students_left_to_serve);  
    int p = get_random_number_between(2,temp); // capacity of each server

    printf(YELLOW"chef %d is cooking \n", chef_number);

    int  w = get_random_number_between(2,5);
    sleep(w); // buffer time for chef to prepare food


    printf(YELLOW"The chef %d is ready with the %d vessles for %d ppl each and waiting to load\n", chef_number, r, p);

    c[chef_number].r = r; // number of vessels
    c[chef_number].p = p; // number of ppl each can serve

    // so that he can be searched by the container staff
    // now unlock the chef so that he can start loading
    students_left_to_serve -= (c[chef_number].r * c[chef_number].p ); 
    c[chef_number].cooking = 0;  // cooking not happpenning, we can start looking
    c[chef_number].lock = 0;

    // it is now that we are actally going to start looking for this chefs thing
    return;
}



void serve_biryani(int chef_number)
{
    while(c[chef_number].cooking == 0); // that means it is still waiting for it's food to be taken
    // now that it is back, we can actually check if more food is required or not and if it's not, we can leave in peace
    if(students_left_to_serve <= 0)
    {
        printf("chef number %d has left service\n", chef_number);
        pthread_exit(NULL);
    }
    return; 
}


struct containers
{
    int container_number;
    int lock;  //0 if currently in action
    int load; // 1 if loading is happenning, 0 if serving
    int students_to_feed;
};

struct containers container[100]; // assuming that the TAs are nice enough

pthread_t container_tids[100];

void init_all_containers(int n)
{

    // make threads however they are made I think
    for(int i = 0 ;i<n ; i++)
    {
        container[i].container_number = i+1; // this gives the chef number
        pthread_create(&container_tids[i], NULL, start_fetching, &container[i]);
    }
    printf("All containers ready to serve\n");
    return;
}


void * start_fetching(void * arg)
{
    struct containers * container = (struct containers* )arg;
    // we have the container number
    container->load = 1; // means it's loading
    container->lock = 0;  // means it is accessible
    container->students_to_feed = 0;

    printf(GREEN"Container number %d ready to go\n",container->container_number);
    
    // container should keep serving until all students have been fed
    while(students_left_to_feed > 0)
    {
        int students_that_can_be_served = get_biryani_from_handler(container->container_number);

        printf(GREEN"container number %d got biryani for %d students. Students left tofeed are %d\n",container->container_number, students_that_can_be_served, students_left_to_feed);

        while(students_that_can_be_served > 0 && students_left_to_feed >0) // what if the students are finished midway
        {
            int temp = get_random_number_between(1,10);
            int numm = min(temp, students_left_to_feed);
            int num = min(numm, students_that_can_be_served);

            students_that_can_be_served -= num; // because these will get biryanis at all costs

            container->students_to_feed = num;
            container->load = 0;
            container->lock = 0;
            // container->container number is already given
            ready_to_serve(container->container_number);
        }

        sleep(1); // to provide buffer time so that students may update perhaps
    }
    printf("container number %d is leaving service\n", container->container_number);
    pthread_exit(NULL);
}


pthread_mutex_t mutex_for_chef_container = PTHREAD_MUTEX_INITIALIZER;

int get_biryani_from_handler(int container_number)
{
    int students_to_be_returned = 0;
    pthread_mutex_lock(&mutex_for_chef_container);

    if(students_left_to_feed <= 0)
    {
        printf(GREEN"Container %d leaving service\n", container_number);
        pthread_exit(NULL);
    }
    int guy_found = -1;

    for(int i = 0; ; i = (++i)%m)  // m is the number of chefs
    {
        printf(GREEN"CONTAINER %d WAITING FOR BIRYANI...\n", container_number);
        sleep(1);
        if(students_left_to_feed <= 0)
        {
            printf(GREEN"Container %d is leaving service\n", container_number);
            pthread_exit(NULL);
            // given that I still haven't fed anyone, it means that someone else completed the feeding and I need to leave
        }
        if(c[i].cooking == 0) // means cooking nai ho rhi, we can access 
        {
            if(c[i].lock == 0)
            {
                c[i].lock = 1;
                guy_found = i;
                // inka khaana arrange ho chuka hai
                break;
            }
        }
        // there is a chance that we may never get out of this loop, but I am okay with that cuz my code leaves when students left to feed are 0;
    }
    // so that none access it
    pthread_mutex_unlock(&mutex_for_chef_container);
    // now that we unlocked it, the others can start looking
    students_to_be_returned = c[guy_found].p ; // just one vessel is given
    c[guy_found].r-- ; // one vessel has been given away
    if(c[guy_found].r <= 0)
    {
        //  this  guy needs  to  leave the queue
        c[guy_found].cooking = 1;
        c[guy_found].lock = 0;
        return students_to_be_returned;
    }
    else
    {
        c[guy_found].lock = 0;
        return students_to_be_returned;
    }
    return 0;
}



void ready_to_serve(int container_number)
{
    while(container[container_number].load == 0);
    // our guy called this only for an appropriate number of students
    // this guy will never overstay or leave prematurely
    printf(GREEN"Container number %d is going back for loading  and checking\n", container_number);
    return;
}




//////////////////////////////////////
// SECTION FOR STUDENTS FUNCTIONS

struct students{
    int student_number;
    int container_number;
};

struct students s[100];

pthread_t student_tids[100];
void bring_all_students(int k)
{

    // make threads however they are made I think
    for(int i = 0 ;i<k ; i++)
    {
        s[i].student_number = i; // this gives the chef number
        printf(NONE"Student number %d has arrived in mess\n", s[i].student_number);
        pthread_create(&student_tids[i], NULL ,wait_for_slot , &s[i]);
        int temp_time = get_random_number_between(1,3);
        sleep(temp_time);
    }
    return;
}


void* wait_for_slot(void  *arg)
{
    struct students * student = (struct students* )arg;
    //student.student number hai hamaare paas

    int container_assigned = go_fetch_slot(student->student_number);
    student_in_slot(student->student_number, container_assigned);

    pthread_exit(NULL);
}


pthread_mutex_t mutex_for_student_container = PTHREAD_MUTEX_INITIALIZER;


int go_fetch_slot(int student_number)
{
    pthread_mutex_lock(&mutex_for_student_container);
    int container_found = -1;
    // this is the section where we check for which one is available and then deal with it
    for(int i = 0; ; i = (++i)%n) // n is the number of containers that are there
    {
        printf(NONE"Student %d waiting for slot...\n", student_number);
        if(container[i].load == 0) // means no cooking, it's available
        {
            if(container[i].lock == 0)
            {
                // means this is the our guy
                container[i].lock = 1;
                container_found = i;
                printf(NONE"student %d has found slot in container %d\n", student_number,container[i].container_number);
                students_left_to_feed--;
                container[container_found].students_to_feed-- ; // one vessel has been given away

                if(container[container_found].students_to_feed <= 0)
                {
                    //  this  guy needs  to  leave the queue
                    container[container_found].load = 1; // send the container back to loading
                    container[container_found].lock = 0;  // so that he's available to be checked
                }
                else
                {
                    container[container_found].lock= 0;
                    // still dosen't need to go for cooking, can still cook
                }
                break;
            }
        }
        sleep(1);
    }
    // so that none access it
    pthread_mutex_unlock(&mutex_for_student_container);
    // now that we unlocked it, the others can start looking
    return container[container_found].container_number;
}


void student_in_slot(int student_number, int container_number)
{
    sleep(1); // this wait is for the student to eat food
    printf(NONE"Student number %d has eaten at container_number %d and is leaving the mess\n",  student_number, container_number);
    return;
}


void wait_for_threads_to_end()
{
    
    for (int i = 0; i < k; i++)
    {
        if(pthread_join(student_tids[i], NULL)); // only wait for the students to return ,cuz the others may return or not
    }
    return;
}

int main()
{
    srand((unsigned)time(NULL)); // this is for giving proper random numbers for the values that we need for the servings

    printf(YELLOW"Number of chefs: ");
    if(scanf("%d", &m));
    printf(GREEN"Number of tables: ");
    if(scanf("%d", &n));
    printf(NONE"Number of students: ");
    if(scanf("%d", &k));

    printf("Thanks!, we'll start serving now!\n");

    students_left_to_serve  = k;
    students_left_to_feed = k;

    init_all_chefs(m);
    init_all_containers(n);
    bring_all_students(k);

    wait_for_threads_to_end();
    printf(YELLOW"WE ARE DONE FOR THE DAY !! :)\n\n\n");

    // we are done here I take it , now we can exit gracefully
    return 0;
}
