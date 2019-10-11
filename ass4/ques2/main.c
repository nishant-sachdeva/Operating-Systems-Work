#include "main.h"


int m; // m is the number of chefs
int n; // n is the number of serving tables
int k; // k is the number of students


int main()
{
    srand((unsigned)time(NULL)); // this is for giving proper random numbers for the values that we need for the servings

    printf("Number of chefs: ");
    scanf("%d", &m);
    printf("Number of tables: ");
    scanf("%d", &n);
    printf("Number of students: ");
    scanf("%d", &k);

    printf("Thanks!, we'll start serving now!\n");

    // function_to_initialise_all_chefs (separate thread)
    // function_to_intialise_all_tables (separate thread)
    // function_to_bring_in_a_student_every_rand_seconds (separate thread)

    
    return 0;
}