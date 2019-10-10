#include "main.h"

int main()
{
    int m; // m is the number of chefs
    int n; // n is the number of serving tables
    int k; // k is the number of students

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