Ques 2 statement is given in the pdf. The following process explains how to go about the whole task:


INSTRUCTIONS TO RUN :

1. make
2. ./a.out

1. Initailise all threads for chefs and tables
2. All the students will be represented as threads. Although it remains a fact that they will arrive in real time and the threads will be initialised on the go.

=> Once initialised, the chefs start preparing the biryani based on the specifications given in the pdf

=> The chef once ready, will wait till all it's vessels are taken ( Or the students are all fed, in that event, we exit anyway)

=> Now, coming to the containers, 
        Here's the magical part, only one container can check for empty chefs at a time. The upside here is that if that one guy can't find an empty chef, then it is a given that no one else can find an empty slot either.  So, that way we are good to go.

        Every time I load a biryani vessel, I reduce the students and I reduce the the vessels. If at this point, the vessels are over, I gracefully ask the chef to go back. 

=> now, onto the students
        They arrive at random times. As soon as some student arrives, he/she looks for an empty slot. The process is same as that between the containers and the chefs.

        As soon as all the students are done, we will exit the code as we are done for the day.
