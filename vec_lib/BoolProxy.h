//
// Created by denis on 06.08.19.
//

#pragma once

#include "vec.h"

extern const size_t NUM_BITS_IN_CHAR;

#include <stdexcept>
#include <iostream>


template<class Alloc>
class BoolProxy{
public:

    BoolProxy(int index, unsigned char* bool_ptr);

    BoolProxy<Alloc>& operator=(bool value);


    BoolProxy<Alloc>& operator=(const BoolProxy& proxy) = default;
    BoolProxy(const BoolProxy& proxy) = default;
    ~BoolProxy() = default;

    friend std::ostream& operator << <>(std::ostream& out, const BoolProxy<Alloc>& proxy);

    friend std::istream& operator >> <>(std::istream& in, const BoolProxy<Alloc>& proxy);



private:
    int index_;                             // number of bits of the required bool value from the right place beginning with bool_ptr
    unsigned char* bool_ptr = nullptr;     // pointer which will link to the right place by ptr_ where the necessary bool value is situated
};

