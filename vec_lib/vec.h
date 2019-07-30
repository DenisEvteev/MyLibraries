//
// Created by denis on 21.07.19.
//

#pragma once
#include <cassert>
#include <iostream>
#include <algorithm>
#include <memory>
#include <exception>
#include <stdexcept>
#include "/home/denis/CLionProjects/String_Lib/String.hpp"


#define SUCCESS 100
#define LOST_VEC -230
#define ERROR_IN_FTELL -1L


template <class T, class Alloc = std::allocator<T>> class vec;
template <class T, class Alloc> std::ostream& operator << (std::ostream& out, const vec<T, Alloc>& v);
template <class T, class Alloc> std::istream& operator >> (std::istream& in, const vec<T, Alloc>& v);


template<class Alloc>
int SortStrings(const char* str, vec<String, Alloc>& t);


template <class T, class Alloc>
class vec {
public:
    explicit vec(size_t size);
    ~vec();
    vec(size_t size, T t);
    //vec(T t, int size); // delegating constructor, not work when T = int
    vec();
    vec<T, Alloc>& operator = (const vec<T, Alloc>& right);
    vec(const vec<T, Alloc>& t);


    T& operator [] (int i);
    const T& operator [] (int i) const;

    T& at(int i);
    const T& at(int i)const;

    bool operator < (const vec<T, Alloc>& t) const;
    bool operator > (const vec<T, Alloc>& t) const;
    bool operator == (const vec<T, Alloc>& t) const;
    bool operator != (const vec<T, Alloc>& t) const;
    bool operator <= (const vec<T, Alloc>& t) const;
    bool operator >= (const vec<T, Alloc>& t) const;


    friend std::ostream& operator << <> (std::ostream& out, const vec<T, Alloc>& v);
    friend std::istream& operator >> <> (std::istream& in, const vec<T, Alloc>& v);

    T* begin()const;
    T* end()const;
    void SetSize(int size);
    void SetCapasity(int bytes);
    Alloc& GetAllocator();
    size_t GetCapasity()const;
    size_t GetSize()const;
    void SetData(T* ptr);

    void push_back(const T& obj);
    void pop_back();
    void MakeNewData(size_t size_for_allocation, size_t size_for_construct);

    /*this method changes size_ and capasity_ at the same time
     * size_ is less than new_size_ then the previous elements are copied by new pointer of data_ and
     * additional elements are appended in "raw" cells by calling a constructor of copy with the f
     * if size_ == new_size_  then return
     * if new_size_ is negative then this function throw an exception
     * */

    void resize(size_t new_size_less);

    /*this method changes size_ and capasity_ at the same time
     * size_ is greater than new_size_ then just new_size_ previous elements are copied
     * by new pointer of data_
     * if new_size_ is negative then this function throw an exception
     * */

    void resize(size_t new_size_greater, T& t);

private:
    T* data_;
    size_t size_;
    size_t capasity_;
    static size_t num_count;
    size_t vec_id = 0;
    Alloc alloc;
};

