HOMEWORK 4: PREFERENCE LISTS
Description: hw4.pdf

NAME:  < NAIL HANOV >


TIME SPENT ON THIS ASSIGNMENT:  <20>


COLLABORATORS: 
You must do this assignment on your own, as described in the DS
Academic Integrity Policy.  If you did discuss the problem or error
messages, etc. with anyone, please list their names here.



ORDER NOTATION:

This was a little ambiguous since we have two add_school functions(same with add_student). One is part of 
main.cpp the other is inside the class implementation. Therefore, I included the full names of 
functions
 
add_school  void AddSchool(std::istream &istr, std::list<School> &schools)
Is of notation O(m+s), where m is the number of schools already in the list and s
existing student slots. 
O(m) comes from the for loop that checks if the new school is already in the list.
O(s) checks if student is already in the prefered list

insert_student_into_school_preference_list  void InsertStudentIntoSchoolPreferenceList(std::istream &istr, std::list<School> &schools) 
This function has a similar to add_school structure. It checks if student already 
in the list and then checks if the new student is already in the prefered list which gives us O(m+s) 

print_school_preferences void PrintSchoolPreferenceList(std::istream &istr, const std::list<School> &schools, std::ostream &ostr)
The order of this function is O(m+s) where m is the #of students in the preference list and s is prefered student list. 

add_student  void School::AddStudent(string student) 
Notation O(n+p), where n is the number of students already in the list. O(n) comes from 
the for loop that checks if the new student is already in the list. p is schools in pref list

remove_school_from_student_preference_list   void RemoveSchoolFromStudentPreferenceList(std::istream &istr, std::list<Student> &students)
This function depends on where in the list is our student that we want to remove. 
Since we are dealing with lists we have to iterate through each element that comes before 
to get to the element we want to remove. Therefore, the worst case here is O(n+p) where n is 
the size of the list and p is the last position in the preferred schools list.The best case is O(1+1), meaning both elements are at the very beginning 
of each list. Average of the two is O(n/2 + p/2)

print_student_preferences  void PrintStudentPreferenceList(std::istream &istr, const std::list<Student> &students, std::ostream &ostr)
Case O(n+p)
Same explanation as before

perform_matching
PrepareToMakeOffers() and PrepareToReceiveOffers()  were commented out as there was no need for those two functions.
We have a one for loop inside of another. One iterates through each  school, the other through each student. This gives us (mn)
In each n (students) loop we have matching functions :
 bool tentative_acceptance  ---- of notation O(p)
 another preferred school iterator ------ O(p)
This gives us O(mn(p+p))
The outer loop depends on how many students each school has on its preferred list so, in math terms, it is f(s) where school is function of s
where s is how many students are in the pref list. Therefore, the final order notation has other order notations inside of itself:
O(m(s)*n(p))
n(p) was simplified from n(p+p)

print_school_enrollments
If we follow the approach described above we have:
O(m(s))

print_student_decisions
This is a simple case of O(n) since each student will only choose one school to enroll to 



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
