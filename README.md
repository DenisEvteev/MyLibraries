MyLibraries
==========================
This repository contains source code of 
String_Lib(class for working with C-strings)
and Vector_Lib(template dynamic array class)

###***[String_Lib](https://github.com/DenisEvteev/MyLibraries/tree/master/String_Lib)***
It'll provide user with :

* Correct work with russian strings(in utf-8 russian letters consist of two bytes)
   * It has function for comparison russian strings
   * Overload operator [] returns object of proxy class (which contains 
   the pointer for the letter and flag which shows if the letter is ascii or not)
* It has overload operators "<<" and ">>" which allow entering object of String from streaming input
and giving the data of object in streaming output
* String class has move-constructor and move assignment operator

###***[Vector_Lib](https://github.com/DenisEvteev/MyLibraries/tree/master/vec_lib)***
It is a template container -- emulation of std::vector from standard library
#### ***TODO List for vec container***
- [ ] Write move-constructor
- [ ] Write move assignment operator 
- [ ] Write classes for removing references and pointers 
- [ ] Update push_back method


