//
// Created by denis on 21.07.19.
//

#pragma once
#include <iostream>
#include <algorithm>
#include <memory>
#include <exception>
#include <stdexcept>


#include "/home/denis/CLionProjects/String_Lib/String.hpp"


#define SUCCESS 100
#define LOST_VEC -230
#define ERROR_IN_FTELL -1L
#define SINGLE_BYTE 1
#define ALL_BYTES_ONE 255

extern const size_t NUM_BITS_IN_CHAR;



#define MAKE_ID vec_id = num_count;\
++num_count;\

template <class T, class Alloc = std::allocator<T>> class vec;
template <class T, class Alloc> std::ostream& operator << (std::ostream& out, const vec<T, Alloc>& v);  // compiler won't be capable to make an implicitly conversion of types!!!
template <class T, class Alloc> std::istream& operator >> (std::istream& in, const vec<T, Alloc>& v);  // we must call this friend function with exactly vec<T, Alloc> type


template<class Alloc>
int SortStrings(const char* str, vec<String, Alloc>& t);


template <class T, class Alloc>
class vec {
public:
    explicit vec(size_t size);
    vec(size_t size, T t);

    //vec(T t, size_t size); // delegating constructor, not work when T = int

    vec();
    vec<T, Alloc>& operator = (const vec<T, Alloc>& right);
    vec(const vec<T, Alloc>& t);
    ~vec();


    T& operator [] (int i);
    const T& operator [] (int i) const;         // operator [] this case won't throw an exception or give another

    T& at(int i);
    const T& at(int i)const;

    bool operator < (const vec<T, Alloc>& t) const;
    bool operator > (const vec<T, Alloc>& t) const;
    bool operator == (const vec<T, Alloc>& t) const;
    bool operator != (const vec<T, Alloc>& t) const;
    bool operator <= (const vec<T, Alloc>& t) const;
    bool operator >= (const vec<T, Alloc>& t) const;


    friend std::ostream& operator << <T, Alloc> (std::ostream& out, const vec<T, Alloc>& v);
    friend std::istream& operator >> <T, Alloc> (std::istream& in, const vec<T, Alloc>& v);

    T* begin()const;
    T* end()const;
    void SetSize(int size);
    void SetCapasity(int bytes);
    Alloc& GetAllocator();
    size_t GetCapasity()const;
    size_t GetSize()const;
    void SetData(T* ptr);

    void   push_back(const T& obj);
    void   pop_back();
    void   MakeNewData(size_t size_for_allocation, size_t size_for_construct);

    /*this method changes size_ and capasity_ at the same time
     * size_ is greater than new_size_ then the previous elements are copied by new pointer of data_ and
     * additional elements are appended in "raw" cells by calling a constructor of copy with the f
     * if size_ == new_size_  then return
     * if new_size_ is negative then this function throw an exception
     * */

    void   resize(size_t new_size_less);

    /*this method changes size_ and capasity_ at the same time
     * size_ is less than new_size_ then just new_size_ previous elements are copied
     * by new pointer of data_
     * if new_size_ is negative then this function throw an exception
     * */

    void   resize(size_t new_size_greater, T& t);

private:
    T*     data_;
    size_t size_;
    size_t capasity_;
    static size_t num_count;
    size_t vec_id = 0;
    Alloc  alloc;
};




template <class Alloc> class vec<bool, Alloc>;
template <class Alloc> std::ostream& operator << (std::ostream& out, const vec<bool, Alloc>& vec);
//template <class Alloc> std::istream& operator >> (std::istream& in, const vec<bool, Alloc>& vec);


template<class Alloc> class BoolProxy;
template<class Alloc> std::ostream& operator<<(std::ostream& out, const BoolProxy<Alloc>& proxy);
template<class Alloc> std::istream& operator>>(std::istream& in, const BoolProxy<Alloc>& proxy);

template <class Alloc>
class vec<bool, Alloc>{
public:
    vec(size_t num_bool, bool value);
    vec(bool value, size_t num_bool);
    vec(size_t num_bool);
    vec(const vec<bool, Alloc>& v);
    vec<bool, Alloc>& operator = (const vec<bool, Alloc>& v);
    vec() = default;
    ~vec();


    typedef BoolProxy<Alloc> proxy;

    /*Declaration class BoolProxy like inner class in vec<bool, Alloc>
     * won't allow to make definition of friend template overload operator << and operator >> in class BoolProxy*/

    //class BoolProxy;

    proxy operator[](int index);
    const proxy operator[](int index)const;       // this case operator [] throws runtime_error if index isn't available

    friend std::ostream& operator << <>(std::ostream& out, const vec<bool, Alloc>& vec);

    //friend std::istream& operator >> <>(std::istream& in, const vec<bool, Alloc>& vec);


    void   push_back(bool value);
    void   pop_back();
    void   flip()noexcept;

    bool   empty()const noexcept;

private:
    size_t size_ = 0;                 // number of bool values
    size_t capasity_ = 0;             // size of allocated memory
    unsigned char* ptr_ = nullptr;

    Alloc alloc;

    //-----------------------------//
    static size_t num_count;
    size_t vec_id = 0;
    //-----------------------------//
};


