### Lab 1: Dynamic Array
Implement  in  C++  the  given container(ADT) using  a given  representation  and  a dynamic  array as a data structure. 
You are not allowed to use the vector from STL or from any other library.

exercise 4. **ADT Bag**
  - represented using a dynamic array of <element,  frequency> pairs (or  two dynamic arrays).
  - For example, the bag [5, 10, -1, 2, 3, 10, 5, 5, -5] will be represented as [(5,3), (10, 2), (-1, 1), (2, 1), (3, 1),(-5, 1)]
 
 Obs:
  - Since your implementation will use dynamic allocation, it is a good practice to implement a destructor,\
   copy  constructor  and  assignment  operator  as  well  (even  if  they  are  not  on  the interface).
  - You are not allowed to use  the functions memcpy and realloc, because it is not safe to use memcpy and realloc on memory that was allocated with new.\
    Also, if the  memory location contains  objects,  undefined  behavior  can  occur. The implementation  might  still  work  with these functions,\
    but it is not a good practice to use them.
  - If you need auxiliary functions, fell free  to add them to the interface of the ADT,  but  make them private.
