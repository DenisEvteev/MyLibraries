#include <iostream>
#include <new>
#include <cstdlib>
#include "String.hpp"


void MyNewHandler();

int main() {


    /*change the pointer for function new_handler which will
     *finish the process of program if new won't manage with allocation the memory.
     *This will deliver us from generating bad_alloc */
    std::set_new_handler(MyNewHandler);

    try{
        String string(__DATE__);

        String string_2 = std::move(string);

        std::cout << string_2;

    }catch(My_Exception* ex){
        std::cout << ex->what() << std::endl;
        ex->dump_info_in_console();
        ex->clear();
    }


    return 0;
}

void MyNewHandler(){
    printf("Cannot allocate memory. The program will end!\n");
    std::abort();
}