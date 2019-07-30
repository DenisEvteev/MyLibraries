//
// Created by denis on 28.07.19.
//

#ifndef VEC_LIB_TRACKINGALLOCATOR_HPP
#define VEC_LIB_TRACKINGALLOCATOR_HPP


#include <iostream>

template <class T>
class TrackingAllocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;

    TrackingAllocator() = default;
    ~TrackingAllocator() = default;


    template <class U>
    TrackingAllocator(const TrackingAllocator<U>& alloc) {}

    template <class U>
    TrackingAllocator<T>&operator=(const TrackingAllocator<U>& alloc) {}


    pointer allocate(std::size_t num_objects)const{
        ++count_allocations;
        return static_cast<pointer>(operator new(sizeof(T) * num_objects));
    }

    void deallocate(pointer ptr, std::size_t num_objects)const{
        operator delete(ptr);
    }

    template <class U, class... Args>
    void construct(U* ptr, const Args&... args)const{
        new(ptr) U(args...);
    }

    template <class U>
    void destroy(U* ptr)const{
        ptr->~U();
    }

    std::size_t GetNumberAllocations()const{
        return count_allocations;
    }


private:
    static std::size_t count_allocations;

};

template<class T>
typename std::size_t TrackingAllocator<T>::count_allocations = 0;

#endif //VEC_LIB_TRACKINGALLOCATOR_HPP
