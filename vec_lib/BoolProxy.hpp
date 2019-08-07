//
// Created by denis on 05.08.19.
//

#include "BoolProxy.h"


#define SIZE_ARRAY_BITS 7

template <class Alloc>
BoolProxy<Alloc>::BoolProxy(int index, unsigned char* bool_ptr) : index_(index), bool_ptr(bool_ptr) {}


template<class Alloc>
BoolProxy<Alloc>& BoolProxy<Alloc>::operator=(bool value){
    if(!bool_ptr)
        throw std::runtime_error("ERROR! You cannot get access to this memory!");
    int pos_value{SIZE_ARRAY_BITS - index_};
    value ? (*bool_ptr |= (1 << pos_value)) : (*bool_ptr &= ~(1 << pos_value));
    return *this;
}


template<class Alloc>
std::ostream& operator << (std::ostream& out, const BoolProxy<Alloc>& proxy){
    int pos_required_bool{SIZE_ARRAY_BITS - proxy.index_};
    out << "//------------------------------//" << std::endl;
    out << "The required value is : " << static_cast<bool>((1 << pos_required_bool) & *proxy.bool_ptr) << std::endl;
    out << "//-----------------------------//" << std::endl;
    return out;
}

template<class Alloc>
std::istream& operator >> (std::istream& in, const BoolProxy<Alloc>& proxy){
    int pos_required_bool{SIZE_ARRAY_BITS - proxy.index_};
    bool value{false};
    std::cout << "Enter the bool value : " << std::endl;
    in >> value;
    value ? (*proxy.bool_ptr |= (1 << pos_required_bool)) : (*proxy.bool_ptr &= ~(1 << pos_required_bool));
    return in;
}