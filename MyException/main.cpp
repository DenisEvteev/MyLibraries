#include "My_Exception.hpp"

#include <iostream>


void ReadFromFile();
void WorkWithFile();

int main() {
    try{
        WorkWithFile();
    }catch(My_Exception* ex){
        std::cout << ex->what() << std::endl;
        ex->dump_info_in_console();
        ex->clear();
    }
    return 0;
}


void WorkWithFile(){
    try{
        ReadFromFile();
    }catch(My_Exception* ex){
        THROW_NEXT(CodeErrors::ERROR_N, ex)
    }
}

void ReadFromFile(){

    FILE* file = fopen("Nonexistent_file.txt", "r");
    if(!file){
        const char* msg = "Cannot open Nonexistent_file.txt";
        FIRST_THROW(CodeErrors::ERROR_READ_FILE, msg)
    }
    fclose(file);
}