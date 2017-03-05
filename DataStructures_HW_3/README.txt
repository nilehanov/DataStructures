HOMEWORK 3: JAGGED ARRAY 
Description: hw3.pdf


NAME:  < NAIL HANOV >


TIME SPENT ON THIS ASSIGNMENT:  <20>


COLLABORATORS:  
(You must do this assignment on your own, as described in "Academic
Integrity for Homework" handout.  If you did discuss the problem or
errors messages, etc. with anyone, please list their names here. )



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the number of elements
k = the number of elements

For unpacked version I have been able to accomplish the logic in 
1. void addElement function is in order of: O(2e) or just O(e)
2. functions: int numBins; int numElements; bool isPacked; int numElementsInBin; T getElement  -- are all O(1), since they only return one value
3. The constructor JaggedArray(int n) is in order of O(b)
4. void unpack() is one of the most resourse consuming  functions that can be expressed in notation O(3b+b*e) or just O(b*e)
5. void removeElement is a O(e+e) or O(e)
6. void clear() is O(e)
7. print() for unpacked O(b^2)

For packed we have the following order notation:
1. void pack()  is  one of the "heaviest" functions that turnes out to be O(2b+e^2) for any case. If we simplify it, we get O(b+e^2)
2. print() for packed O(b+e)

numElements
 unpacked:O(1)
 packed:O(1)

numBins
 unpacked:O(1)
 packed:O(1)

numElementsInBin
 unpacked:O(1)
 packed:O(1)

getElement
 unpacked:O(1)
 packed:O(1)

isPacked
 unpacked:O(1)
 packed:O(1)

clear
 unpacked:O(e)
 packed: can't

addElement
 unpacked:O(e)
 packed:can't

removeElement
 unpacked:O(e)
 packed:can't

pack
 unpacked:O(b+e^2)
 packed:O(b+e^2)

unpack
 unpacked: O(b^2)
 packed: O(b^2)

print 
 unpacked:O(b^2)
 packed:O(b+e)

constructor w/ integer argument
 unpacked:O(b)
 packed:O(b)

copy constructor
 unpacked:O(b)
 packed:O(b)

destructor
 unpacked:O(e)
 packed:O(e)

assignment operator
 unpacked: 
 packed:




MISC. COMMENTS TO GRADER:  

Please review the code and the output.

Thank you.

Best regards,
Nail Hanov
