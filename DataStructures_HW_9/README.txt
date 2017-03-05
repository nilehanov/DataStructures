HOMEWORK 9: PERFECT HASHING
Description: hw9.pdf

NAME:  < Nail Hanov >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassment, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Nathan, Cris (ALAC) 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



SUMMARY OF RESULTS: 
Summarize your results on the provided examples.  Were you able to
construct a perfect hash function?  If not, how close did you get (how
many collisions)?  If yes, what was the smallest perfect hash you were
able to construct for the different examples?  What was your
compression ratio?  Did you make any additional test cases?

I didn't get the perfect hash function; however, I came relatively close. 
My code worked well for generating an offset table but it couldn't 
distribute pixels well into a hash table. I followed all the directions
(e.g. make sure hash table size and offset table size don't share common 
factors; start distributing data starting from the most populated cells 
in the offset table, etc.)



OFFSET SEARCH FOR EXTRA CREDIT:
If you implemented a search strategy instead of or in addition to the
greedy method from the paper, describe it here.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
Please go over the code for placing data into a hash table(void find_place_in_hash)
if you find it reasonable, I hope you will give some points back since the logic for 
this fuction is almost complete with the exception of that small bug that I couldn't 
find.







