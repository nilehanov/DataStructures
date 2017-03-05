HOMEWORK 8: CITY CHASE
Description: hw8.pdf

NAME:  < Nail Hanov >


TIME SPENT ON THIS ASSIGNMENT:  <20>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassment, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Received help from Ben Ball 


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



EVADER STRATEGY:
Before making the next move the evader checks if there is a neighbor city he/she can 
move to that is not on the "neighboors" list of pursuer's current city.
This garanties that the pursuer won't get to him/her(evader) in his/her next move.
If there is more then one city that falls into this category, the evader 
checks which those cities have more neighbors. This is done to give the evader
more options for the move on next "TICK"(rounds) and prevents from being pinned down to 
a city that is only connected to one other city. 
The evader also checks if the next city is not the pursuer's current city. 
If both of the above conditions are satisfied and the map is relatively big,
the evader will be most likely to win. 
This strategy best works against one pursuer. It will also work if there are multiple pursuers 
because in that case the evader will look at all possible next moves of each pursuer, similar 
to the case when there was only one pursuer.
However, with multiple pursuers it is possible to pin down the evader if all pursuers work 
together and eventually get the evader into a corner.

PURSUER STRATEGY:
For one pursuer, capturing the evader on a map that is not small could be a very hard task.
To optimize this work, each time the pursuer moves to a city that has the most number of common 
neighbors with that of the evader current city's neighbors (in other words, if evader can move 
to A,B,C and the pursuer cannot get to those in one step and it can only move to D,E where 
     D is a neighbor of A; 
     E is neighbor of B and C;
then the pursuer will move to E)
The pursuer also checks if the evader just came to his/her(pursuer's) current city. If that is the
case, the pursuer simply stays in the current city. 
If the evader is in the neighbor city, the pursuer moves to that city; however if the evader is in the
neighbor city but that city is only connected to the pursuer's current city, the pursuer stays in the same city.
This is done because if:
	evader is in A that is only connected to B
	pursuer is in B that is connected to A,C,D
then if pursuer moves to A then the evader can escape by simply moving to B where there are so many other neighbor cities 
he/she can move to.
This last situation is easily solved if we have more than one pursuer. In that case pursuer_1 stays in the same city(B)
and pursuer_2 moves to A. Checkmate.
Other logic for multiple pursuers:
All the pursuers follow similar logic described above and also, each one of them, makes sure not to move to a city where 
another pursuer is currently located. 



NEW GRAPH NETWORK FOR EXTRA CREDIT:
Describe your new network and why it makes a fun game.


MISC. COMMENTS TO GRADER:  
Optional, please be concise!






