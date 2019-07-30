//
// Created by denis on 21.07.19.
//
#include "TrackingAllocator.hpp"
#include "vec_def.hpp"
#include "/home/denis/CLionProjects/String_Lib/String.hpp"


#include <iostream>



int main(){

    //vec<String, TrackingAllocator<String>> test_v;
    try {
        vec<String, TrackingAllocator<String>> jf(3, "секс");

        String test("мама");
        jf.push_back(test);
        String test_2("sjfjоовалолыооыороjkjkskjfkf");
        jf.push_back(test_2);
        String test_3("Как же много инфы интересной вокруг");
        jf.push_back(test_3);

        jf.pop_back();
        jf.pop_back();




        std::cout << jf << std::endl;

    }catch(std::runtime_error& ex){
        std::cout << ex.what() << std::endl;
    }


    /*vec<float, TrackingAllocator<float>> hg(15, 6.444f);


    try{
        std::cout << jf.at(100);

    }catch(std::out_of_range& ex){
        std::cout << ex.what() << std::endl;
    }

    try{
        std::cout << hg.at(14) << std::endl;
    }catch(std::out_of_range& ex){
        std::cout << ex.what() << std::endl;
    }

*/
    return 0;
}