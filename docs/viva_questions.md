# Viva Preparation — Short Questions and Answers

1. **What is a class?** A class is a user-defined type that groups data and functions. `Bike` is the main class.
2. **What is an object?** An object is an instance of a class, such as one bike record.
3. **Why are data members private?** To protect the data and control access through public functions.
4. **What is a static data member?** A member shared by all objects of the class. `totalBikes` is shared.
5. **What is an inline function?** A small function for which the compiler may substitute the function body at the call site. The getters are defined inside the class.
6. **What is a friend function?** A non-member function allowed to access private/protected members. `showBike` is a friend.
7. **What does `this` mean?** It is a pointer to the current object. It is used in the parameterised constructor to distinguish member names.
8. **Why use a pointer array?** A base-class pointer can point to a derived-class object, allowing polymorphism.
9. **Why is the destructor virtual?** So derived destructors are called correctly when an object is deleted through a base pointer.
10. **What is a copy constructor?** A constructor that creates an object from another object of the same class.
11. **Why not write a `std::string` object directly to a binary file?** Its internal representation may contain pointers/managed storage and is not a portable fixed record. The project writes a separate fixed-size structure.
12. **What is `seekg`?** It moves the input/get pointer in a file.
13. **What is `seekp`?** It moves the output/put pointer in a file.
14. **What is inheritance?** Creating a new class from an existing class. CommuterBike and SportsBike inherit Bike.
15. **What is polymorphism?** The same base pointer/function call can produce different derived behaviour at run time through virtual functions.
16. **What is operator overloading?** Giving an operator a meaning for a user-defined class, such as comparing two bikes by kilometres.
17. **What is a template?** A way to write generic code that works with more than one data type.
18. **What does `count_if` do?** Counts elements satisfying a condition.
19. **What does `find_if` do?** Finds the first element satisfying a condition.
20. **What is the unique key?** Registration number; it identifies one bike and duplicates are rejected.
