//
// Created by denis on 21.07.19.
//
#include "TrackingAllocator.hpp"

#include "vec_def.hpp"

#include "/home/denis/CLionProjects/String_Lib/String.hpp"

#include <iostream>

#define REST_OF_SUMMER 24

int main(){

    //_____________Example of some methods VECTOR_BOOL___________________//
    try{
        vec<bool, TrackingAllocator<unsigned char>> bool_vec(10, true);

        bool_vec.push_back(false);

        std::cin >> bool_vec[0];

        bool_vec[7] = false;

        std::cout << bool_vec << std::endl;

        bool_vec.flip();
    }catch(std::runtime_error& ex){
        std::cout << ex.what() << std::endl;
    }

    //_______________Examples of some methods of common vec<type, TrackingAllocator<type>>______________//

    try{
        vec<String, TrackingAllocator<String>> vec_str(3802, "_еда_");

        String sadness("нет еды");
        vec_str.push_back(sadness);
        vec_str.pop_back();
        vec_str.resize(REST_OF_SUMMER);

    }catch(std::runtime_error& ex){
        std::cout << ex.what() << std::endl;
    }
    return 0;
}