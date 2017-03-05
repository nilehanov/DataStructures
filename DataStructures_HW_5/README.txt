HOMEWORK 5: MULTI LINKED LISTS
Description: hw5.pdf

NAME:  < Nail Hanov >


TIME SPEND ON THIS ASSIGNMENT:  <# 35>



COLLABORATORS: 
You must do this assignment on your own, as described in the CS2
Academic Integrity Policy.  If you did discuss the problem or error
messages, etc. with anyone, please list their names here.



TESTING & DEBUGGING STRATEGY:
Used gdb, QT and Valgrind



ORDER NOTATION of the member functions of MultiLL?
(in terms of n, the number of elements currently in the list)

default constructor 
O(1)

copy constructor
Only one for loop
O(n)

assignment operator
O(1)

destructor
Have one while loop
O(n)

size
O(1)

empty
O(1)

clear
Calls destroy_list()
which is O(n)

add
Of order O(n)
because perform sorting.
Finding the right spot for each incoming element.

erase
Of order O(n)
Because loop through all the elements to get the previous of the random to re-link in a circular list

begin_chronological
O(1)
Returns chrono_head

end_chronological
O(1)
Returns NULL

begin_sorted
O(1)
Returns sorted_head

end_sorted
O(1)
Returns NULL

begin_random
For refering to creation of a unique number using MTRand  I'll use variable "m".
For getting all the unique number and placing them in my array the operation is:
O(n*m)
Second step: Linking random nodes
Takes only O(n)
Therefore, the total is O(nm+n)


ITERATOR INVALIDATION:
In what cases will iterators of the MultiLL be invalidated?  Justify
the need for each of the restrictions placed on your implementation.

Decrementing a random iterator would be invalid because we only have random_next but not random_previous



EXTRA CREDIT: 
Which function in your implementation can be improved by a
non-insertion sort sorting method?  Did you implement the improvement?
Describe.

I have not implemented the improvement due to time limits.
However, I understand that there is a better implementation.
In particular, this operation could be done efficiently using binary sort algorithim


MISC. COMMENTS TO GRADER:  
Please take a look at the passed cases of w/solution test(including w/solution valgrind).
Prof Cutler said that partial creadit can be given in case if some but not all requirements were satisfied.



