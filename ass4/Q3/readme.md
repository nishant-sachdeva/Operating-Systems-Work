Problem Statement is as given in the pdf of the assignment

Approach:

=> All the cabs are modelled as structs. 
=> All the passengers are moelled as threads. These threads arrive at different times and wait for a certain times.
    They wait for an available cab and if they can't find one ,  they leave the system

    ==> Now assuming they found a cab, the cab status is set according to the question demands in the pdf.
    ==> The cab ride goes on for the ride time specefied by the passenger. After the ride is done, the passenger makes the payment and exits the system.

=> All the payment servers are modelled as threads. They iterate through the list of pending payments and keep satisfying payment requirements for the customers
and restore the status of the cabs that were being used.


Once all the customers have either confirmed payment or exited the system, we are free to leave the system as well.