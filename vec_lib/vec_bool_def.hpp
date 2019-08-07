//
// Created by denis on 05.08.19.
//


#pragma once

#include "vec.h"

template <class Alloc>
size_t vec<bool, Alloc>::num_count = 1;

template<class Alloc>
vec<bool, Alloc>::vec(size_t num_bool, bool value) : size_(num_bool),
capasity_(static_cast<int>(num_bool / NUM_BITS_IN_CHAR) + 1){
    if(num_bool <= 0)
        throw std::runtime_error("You cannot call this constructor with such a num_bool. Try another one.");
    ptr_ = std::allocator_traits<Alloc>::allocate(alloc, capasity_);

    for(int i = 0; i < capasity_; ++i)
        ptr_[i] = 0;


    int pos_b{7};

    if(capasity_ == SINGLE_BYTE){
        for(int i = 0; i < size_; ++i){
            value ? (*ptr_ |= (1 << pos_b)) : (*ptr_ &= ~(1 << pos_b));
            --pos_b;
        }
    }

    else{
        for(int i = 0; i < capasity_ - 1; ++i)
            value ? *(ptr_ + i) = ALL_BYTES_ONE : *(ptr_ + i) = value;
        for(int i = 0; i < size_ - NUM_BITS_IN_CHAR * (capasity_ - 1); ++i){
            value ? (*(ptr_ + capasity_ - 1) |= (1 << pos_b)) :
            (*(ptr_ + capasity_ - 1) &= ~(1 << pos_b));
            --pos_b;
        }
    }
    MAKE_ID

}

template <class Alloc>
vec<bool, Alloc>::vec(bool value, size_t num_bool) : vec(num_bool, value) {}

template<class Alloc>
vec<bool, Alloc>::vec(size_t num_bool) : size_(num_bool),
capasity_(static_cast<int>(num_bool / NUM_BITS_IN_CHAR) + 1){
    if(num_bool <= 0)
        throw std::runtime_error("You cannot call this constructor with such a num_bool. Try another one.");
    ptr_ = std::allocator_traits<Alloc>::allocate(alloc, capasity_);
    MAKE_ID
}



template<class Alloc>
vec<bool, Alloc>::~vec(){
    std::allocator_traits<Alloc>::deallocate(alloc, ptr_, capasity_);
    size_ = capasity_ = 0;
    vec_id = LOST_VEC;
}

template<class Alloc>
vec<bool, Alloc>::vec(const vec<bool, Alloc>& v){
    size_ = v.size_;
    capasity_ = v.capasity_;
    ptr_ = std::allocator_traits<Alloc>::allocate(alloc, capasity_);
    for(int i = 0; i < capasity_; ++i)
        *(ptr_ + i) = *(v.ptr_ + i);
    MAKE_ID
}

template<class Alloc>
vec<bool, Alloc>& vec<bool, Alloc>::operator=(const vec<bool, Alloc>& v){
    if(&v == this)
        return *this;

    size_ = v.size_;

    if(!this->empty())
        std::allocator_traits<Alloc>::deallocate(alloc, ptr_, capasity_);

    ptr_ = std::allocator_traits<Alloc>::allocate(alloc, v.capasity_);
    for(int i = 0; i < v.capasity_; ++i)
        ptr_[i] = v.ptr_[i];

    capasity_ = v.capasity_;

    return *this;

}

template<class Alloc>
bool vec<bool, Alloc>::empty() const noexcept {
    return !size_;

}

template<class Alloc>
BoolProxy<Alloc> vec<bool, Alloc>::operator[](int index){
    if(index < 0 || index >= size_)
        throw std::runtime_error("You haven't got an access to this memory!");
    return BoolProxy<Alloc>(index % NUM_BITS_IN_CHAR, ptr_ + static_cast<int>(index / NUM_BITS_IN_CHAR));
}


template <class Alloc>
const BoolProxy<Alloc> vec<bool, Alloc>::operator[](int index)const{
    if(index < 0 || index >= size_)
        throw std::runtime_error("You haven't got an access to this memory!");
    return BoolProxy<Alloc>(index % NUM_BITS_IN_CHAR, ptr_ + static_cast<int>(index / NUM_BITS_IN_CHAR));
}

template <class Alloc>
std::ostream& operator << (std::ostream& out, const vec<bool, Alloc>& vec){
    if(vec.empty()){
        out << "Vector_Bool with id : " << vec.vec_id << " is empty" << std::endl;
        return out;
    }
    else{
        out << "Vector_Bool with id : " << vec.vec_id << " has size = " << vec.size_ << std::endl;
        out << "Capasity of this Vector_bool is : "  << vec.capasity_ << std::endl;
        out << "It contains the elements : { " ;

        int start_pos{NUM_BITS_IN_CHAR - 1};

        for(int i = 0; i < vec.capasity_ - 1; ++i){
            for(int j = 0; j < NUM_BITS_IN_CHAR; ++j){
                out << static_cast<bool>((1 << start_pos) & *(vec.ptr_ + i));
                --start_pos;
            }
            start_pos = NUM_BITS_IN_CHAR - 1;
        }


        int rest_size_ = vec.size_ - (vec.capasity_ - 1) * NUM_BITS_IN_CHAR;

        for(int i = 0; i < rest_size_; ++i)
            out << static_cast<bool>((1 << NUM_BITS_IN_CHAR - 1 - i) & *(vec.ptr_ + vec.capasity_ - 1));

        out << " }" << std::endl;

        return out;
    }
}

template<class Alloc>
void vec<bool, Alloc>::push_back(bool value) {

    if(this->empty()){
        ptr_ = std::allocator_traits<Alloc>::allocate(alloc, 1);
        value ? *ptr_ |= (1 << NUM_BITS_IN_CHAR - 1) : *ptr_ &= (1 << NUM_BITS_IN_CHAR - 1);
        ++size_;
        ++capasity_;
        return;
    }


    size_t vacant_{capasity_ * NUM_BITS_IN_CHAR};
    if(vacant_ > size_){
        int right_pos_value = NUM_BITS_IN_CHAR - (size_ - (capasity_ - 1) * NUM_BITS_IN_CHAR) - 1;
        value ? *(ptr_ + capasity_ - 1) |= (1 << right_pos_value) : *(ptr_ + capasity_ - 1) &= ~(1 << right_pos_value);
        ++size_;
    }

    else{
        typename std::allocator_traits<Alloc>::pointer new_ptr_ =
                std::allocator_traits<Alloc>::allocate(alloc, 2 * capasity_);
        ++size_;
        for(int i = 0; i < capasity_; ++i)
            new_ptr_[i] = ptr_[i];
        int pos_value{7};
        value ? *(new_ptr_ + capasity_) |= (1 << pos_value) : *(new_ptr_ + capasity_) &= ~(1 << pos_value);
        std::allocator_traits<Alloc>::deallocate(alloc, ptr_, capasity_);
        capasity_ *= 2;
        ptr_ = new_ptr_;
    }
}


template <class Alloc>
void vec<bool, Alloc>::pop_back() {

    if(this->empty()){
        std::cout << "This Vector_Bool is empty" << std::endl;
        return;
    }

    else{
        if(size_ % NUM_BITS_IN_CHAR == 1){
            typename std::allocator_traits<Alloc>::pointer new_ptr =
                    std::allocator_traits<Alloc>::allocate(alloc, capasity_ - 1);

            for(int i = 0; i < capasity_ - 1; ++i)
                new_ptr[i] = ptr_[i];

            std::allocator_traits<Alloc>::deallocate(alloc, ptr_, capasity_);
            --capasity_;
            --size_;
            ptr_ = new_ptr;
        }
        else
            --size_;
    }
}

template<class Alloc>
void vec<bool, Alloc>::flip() noexcept {
    if(this->empty()){
        std::cout << "flip() cannot convert empty Vector_Bool" << std::endl;
        return;
    }
    else{
        int start_pos{7};
        for(int i = 0; i < capasity_ - 1; ++i){
            for(int j = 0; j < NUM_BITS_IN_CHAR; ++j){

                *(ptr_ + i) ^= (1 << start_pos);
                --start_pos;
            }
            start_pos = NUM_BITS_IN_CHAR - 1;
        }

        int rest_size_ = size_ - (capasity_ - 1) * NUM_BITS_IN_CHAR;

        for(int i = 0; i < rest_size_; ++i)
            *(ptr_ + capasity_ - 1) ^= (1  << NUM_BITS_IN_CHAR - 1 - i);

    }
}

#include "BoolProxy.hpp"