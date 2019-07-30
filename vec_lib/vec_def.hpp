//
// Created by denis on 21.07.19.
//

#ifndef VEC_LIB_VEC_DEF_HPP
#define VEC_LIB_VEC_DEF_HPP


#define MAKE_ID vec_id = num_count;\
++num_count;\

#include "vec.h"


template <class T, class Alloc>
size_t vec<T, Alloc>::num_count = 1;


template <class T, class Alloc>
vec<T, Alloc>::vec(size_t size){
    if(size <= 0)
        throw std::runtime_error("Constructor with argument size can take only positive value");
    size_ = size;
    capasity_ = size;
    data_ = std::allocator_traits<Alloc>::allocate(alloc, size); // only pick put a "raw" memory
    MAKE_ID
}

template <class T, class Alloc>
vec<T, Alloc>::vec(size_t size, T t){
    if(size <= 0)
        throw std::runtime_error("Constructor with argument size can take only positive value");
    size_ = size;
    capasity_ = size;
    data_ = std::allocator_traits<Alloc>::allocate(alloc, size);
    for(int i = 0; i < size_; ++i)
        std::allocator_traits<Alloc>::construct(alloc, data_+ i, t);
    MAKE_ID
}

/*template <class T>
vec<T>::vec(T t, int size) : vec<T>(size, t) {}*/

template <class T, class Alloc>
vec<T, Alloc>::vec(): size_(0), capasity_(0), data_(nullptr) {MAKE_ID}

template <class T, class Alloc>
vec<T, Alloc>& vec<T, Alloc>::operator = (const vec<T, Alloc>& right){
    if(this == &right)
        return *this;

    std::allocator_traits<Alloc>::destroy(alloc, data_);
    size_ = right.size_;

    if(capasity_ != right.capasity_){
        std::allocator_traits<Alloc>::deallocate(alloc, data_, capasity_);
        data_ = std::allocator_traits<Alloc>::allocate(alloc, right.capasity_);
    }

    for(int i = 0; i < size_; ++i)
        std::allocator_traits<Alloc>::construct(alloc, data_ + i, right.data_[i]);

    capasity_ = right.capasity_;
    return *this;
}

template <class T, class Alloc>
vec<T, Alloc>::vec(const vec<T, Alloc>& t){
    std::allocator_traits<Alloc>::allocate(alloc, data_, t.capasity_);
    size_ = t.size_;
    capasity_ = t.capasity_;

    for(int i = 0; i < size_; ++i)
        std::allocator_traits<Alloc>::construct(alloc, data_ + i, t.data_[i]);
    MAKE_ID
}

template <class T, class Alloc>
T& vec<T, Alloc>::operator[](int i){
    return data_[i];
}

template <class T, class Alloc>
const T& vec<T, Alloc>::operator[](int i) const{
    return data_[i];
}

template<class T, class Alloc>
T& vec<T, Alloc>::at(int i){
    if(i < 0 || i >= size_)
        throw std::out_of_range("You can not get access to this part of memory");
    return data_[i];
}

template<class T, class Alloc>
const T& vec<T, Alloc>::at(int i) const {
    if(i < 0 || i >= size_)
        throw std::out_of_range("You can not get access to this part of memory");
    return data_[i];

}

template <class T, class Alloc>
bool vec<T, Alloc>::operator<(const vec<T, Alloc> &t) const {
    int i{0};
    int j{0};
    while(i != size_ && j != t.size_){
        if(data_[i] < t.data_[j])
            return true;
        else if(data_[i] > t.data_[j])
            return false;
        ++i;
        ++j;
    }
    if(i == j || j == t.size_)
        return false;
    return true;
}

template <class T, class Alloc>
bool vec<T, Alloc>::operator > (const vec<T, Alloc>& t) const{
    return t < *this;
}

template <class T, class Alloc>
bool vec<T, Alloc>::operator == (const vec<T, Alloc>& t) const{
    return !(*this > t || *this < t);
}

template <class T, class Alloc>
bool vec<T, Alloc>::operator != (const vec<T, Alloc>& t) const{
    return !(*this == t);
}

template <class T, class Alloc>
bool vec<T, Alloc>::operator <= (const vec<T, Alloc>& t) const{
    return (*this < t || *this == t);
}

template <class T, class Alloc>
bool vec<T, Alloc>::operator >= (const vec<T, Alloc>& t) const{
    return (*this > t || *this == t);
}

template <class T, class Alloc>
vec<T, Alloc>::~vec(){
    for(int i = 0; i < size_; ++i)
        std::allocator_traits<Alloc>::destroy(alloc, data_ + i);
    std::allocator_traits<Alloc>::deallocate(alloc, data_, capasity_);
    vec_id = LOST_VEC;
    size_ = 0;
    capasity_ = 0;
}

template <class T, class Alloc>
std::ostream& operator << (std::ostream& out, const vec<T, Alloc>& v){
    out << "vec with id of this type : " << v.vec_id << std::endl;  // for different template parametres it can be the same
    out << "size is : " << v.size_ << std::endl;
    out << "capasity is : " << v.capasity_ << std::endl;
    out << "{";
    for(int i = 0; i < v.size_; ++i){
        i == 0 ?  out << v.data_[i] : out << ' ' <<  v.data_[i];
    }
    out << "}" << std::endl;
    return out;
}

template <class T, class Alloc>
std::istream& operator >> (std::istream& in, const vec<T, Alloc>& v){
    std::cout << "Enter " << v.size_ << " values" << std::endl;
    if(v.size_ <= 0)
        throw std::runtime_error("You can not use operator >> and enter not positive size_!!!");
    for(int i = 0; i < v.size_; ++i)
        in >> v.data_[i];
    return in;
}


template <class T, class Alloc>
T* vec<T, Alloc>::begin()const{
    return data_;

}

template <class T, class Alloc>
T* vec<T, Alloc>::end()const{
    return data_ + size_ - 1;
}


template <class T, class Alloc>
void vec<T, Alloc>::SetCapasity(int bytes) {
    capasity_ = bytes;
}

template <class T, class Alloc>
void vec<T, Alloc>::SetSize(int size){
    size_ = size;
}

template <class T, class Alloc>
Alloc& vec<T, Alloc>::GetAllocator(){
    return alloc;
}

template<class T, class Alloc>
size_t vec<T, Alloc>::GetCapasity() const {
    return capasity_;
}

template <class T, class Alloc>
size_t vec<T, Alloc>::GetSize() const {
    return size_;
}

template<class T, class Alloc>
void vec<T, Alloc>::SetData(T *ptr) {
    data_ = ptr;
}

template <class Alloc>
int SortStrings(const char *str, vec<String, Alloc>& t) {
    FILE* info = fopen(str, "r");
    if(!info){
        throw std::runtime_error("file with info can not be openned");
    }

    fseek(info, 0, SEEK_END);
    int num_bytes = ftell(info);
    if(num_bytes == 0 || num_bytes == ERROR_IN_FTELL)
        throw std::runtime_error("ERROR IN FTELL");

    rewind(info);

    vec<char> all_data(num_bytes + 1);

    int right_number_bytes = fread(all_data.begin(), sizeof(char), num_bytes, info) + 1;

    all_data.SetSize(right_number_bytes);
    all_data.SetCapasity(right_number_bytes);
    all_data[right_number_bytes - 1] = '\n';

    int i{0};
    int num_strings{0};
    while(i < right_number_bytes){
        if(all_data[i] == '\n'){
            all_data[i] = '\0';
            ++num_strings;
            ++i;
            while(all_data[i] == '\n'){
                ++i;
                if(i == right_number_bytes)
                    break;
            }
        }
        ++i;
    }
    i = 0;
    int ip_{0};
    for(int j = 0; j < t.GetSize(); ++j)
        std::allocator_traits<Alloc>::destroy(t.GetAllocator(), t.begin() + j);

    std::allocator_traits<Alloc>::deallocate(t.GetAllocator(), t.begin(), t.GetCapasity());
    t.SetData(std::allocator_traits<Alloc>::allocate(t.GetAllocator(), num_bytes));

    t.SetSize(num_strings);
    t.SetCapasity(num_strings);

    while(ip_< t.GetSize()){
        std::allocator_traits<Alloc>::construct(t.GetAllocator(), t.begin() + ip_, &all_data[i]);
        i += t.begin()[ip_].GetNumBytes();
        while(all_data[i] == '\n'){
            ++i;
            if(i == right_number_bytes)
                break;
        }
        ++ip_;
    }
    std::sort(t.begin(), t.end() + 1, *t.begin());

    std::cout << t << std::endl;

    fclose(info);
    return SUCCESS;
}

template<class T, class Alloc>
void vec<T, Alloc>::push_back(const T &obj) {
    if(size_ < capasity_){
        std::allocator_traits<Alloc>::construct(alloc, data_ + size_, obj);
        ++size_;
    }
    else{
        size_t new_capasity{0};
        capasity_ == 0 ? new_capasity = 2 : new_capasity = capasity_ * 2;
        MakeNewData(new_capasity, size_);
        std::allocator_traits<Alloc>::construct(alloc, data_ + capasity_, obj);
        ++size_;
        capasity_ = new_capasity;
    }
}

template <class T, class Alloc>
void vec<T, Alloc>::pop_back() {
    if(size_ == 0)
        return;
    std::allocator_traits<Alloc>::destroy(alloc, data_ + size_ - 1);
    --size_;
}

template<class T, class Alloc>
void vec<T, Alloc>::resize(size_t new_size_greater, T& t) {
    if(new_size_greater < 0)
        throw std::runtime_error("Resize can change size_ of vec but argument must be positive!!!");
    if(new_size_greater == size_)
        return;
    if(new_size_greater < size_){
        std::cout << "Use another overload version of resize" << std::endl;
        return;
    }
    MakeNewData(new_size_greater, size_);

    for(int j = size_; j < new_size_greater; ++j)
        std::allocator_traits<Alloc>::construct(alloc, data_ + j, t);

    capasity_ = size_ = new_size_greater;
}

template <class T, class Alloc>
void vec<T, Alloc>::resize(size_t new_size_less) {
    if(new_size_less < 0)
        throw std::runtime_error("Resize can change size_ of vec but argument must be positive!!!");
    if(new_size_less == size_)
        return;
    if(new_size_less > size_){
        std::cout << "Use another overload version of resize" << std::endl;
        return;
    }
    MakeNewData(new_size_less, new_size_less);
    capasity_ = size_ = new_size_less;
}

template <class T, class Alloc>
void vec<T, Alloc>::MakeNewData(size_t size_for_allocation, size_t size_for_construct){
    typename std::allocator_traits<Alloc>::pointer ptr =
            std::allocator_traits<Alloc>::allocate(alloc, size_for_allocation);
    for(int i = 0; i < size_for_construct; ++i)
        std::allocator_traits<Alloc>::construct(alloc, ptr + i, data_[i]);
    for(int i = 0; i < size_; ++i)
        std::allocator_traits<Alloc>::destroy(alloc, data_ + i);
    std::allocator_traits<Alloc>::deallocate(alloc, data_, capasity_);
    data_ = ptr;
}



#endif //VEC_LIB_VEC_DEF_HPP
