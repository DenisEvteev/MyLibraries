//
// Created by denis on 22.07.19.
//

#include "String.hpp"

String::String(const char* str) {
    size_ = StrLen(str);
    num_bytes_ = CountBytes(str);
    try{
        str_ = new char[num_bytes_]{};
    }catch(const std::bad_alloc& ex){
        std::cout << ex.what() << std::endl;
        std::cout << "operator new can not give you the memory" << std::endl;
        return;
    }
    for(int i = 0; i < num_bytes_; ++i)
        str_[i] = str[i];
}

String::String(int bytes) {
    if(bytes <= 0)
        throw std::runtime_error("This constructor can create object of String only with positive bytes");

    num_bytes_ = bytes;
    try{
        str_ = new char[num_bytes_]{};
    }catch(const std::bad_alloc& ex){
        std::cout << ex.what() << std::endl;
        std::cout << "operator new can not give you the memory" << std::endl;
        return;
    }
}

String::String(const String& s){
    size_ = s.size_;
    num_bytes_ = s.num_bytes_;
    try{
        str_ = new char[num_bytes_]{};
    }catch(const std::bad_alloc& ex){
        std::cout << ex.what() << std::endl;
        std::cout << "operator new can not give you the memory" << std::endl;
        return;
    }
    for(int i = 0; i < num_bytes_; ++i)
        str_[i] = s.str_[i];
}

String::String(){
    size_ = 0;
    num_bytes_ = 0;
    str_ = nullptr;
}

String& String::operator=(const String& s){
    if(this == &s)
        return *this;
    if(num_bytes_ != 0){
        delete[] str_;
        size_ = 0;
        num_bytes_ = 0;
    }
    if(s.num_bytes_ != 0){
        size_ = s.size_;
        num_bytes_ = s.num_bytes_;
        try{
            str_ = new char[num_bytes_]{};
        }catch(const std::bad_alloc& ex){
            std::cout << ex.what() << std::endl;
            std::cout << "operator new can not give you the memory" << std::endl;
        }
        for(int i = 0; i < num_bytes_; ++i)
            str_[i] = s.str_[i];
    }
    return *this;
}

String::~String() {
    size_ = 0;
    num_bytes_ = 0;
    delete[] str_;
}

int String::CountBytes(const char* str) const{
    int bytes{0};
    while(*str != '\0'){
        ++bytes;
        ++str;
    }
    ++bytes;         //because of the last nul terminator
    return bytes;
}

int String::StrLen(const char *str) const {
    int len{0};
    while(*str != '\0'){
        ++len;
        IsThisByteAscii(*str) ? ++str : str += 2;
    }
    return len;
}

bool String::IsThisByteAscii(char c) const {
    return (c >= BOTTOM_ASCII && c <= TOP_ASCII);
}

std::istream& operator>>(std::istream& in, String& s){
    std::cout << "Enter number of bytes :" << std::endl;
    int byte{0};
    in >> byte;       // without nul terminator
    if(byte < 0){
        throw std::runtime_error("byte can be only positive");
    }
    try{
        int i{0};
        char* str_from_console = new char[byte + 1]{}; // because of nul terminator
        char c{'\0'};
        std::cout << "Enter the str : " << std::endl;
        while(i < byte){
            scanf("%c", &c);
            if(c == '\n'){
                continue;
            }
            str_from_console[i] = c;
            ++i;
        }
        str_from_console[byte] = '\0';
        s = String(str_from_console);
        delete[] str_from_console;
        return in;
    }catch(std::bad_alloc& ex){
        std::cout << ex.what() << std::endl;
        std::cout << "operator new can not give you the memory" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out, const String& s){
    out << "Size of str_ is : " << s.size_ << std::endl;
    out << "Number of bytes is : " << s.num_bytes_ << std::endl;
    if(s.num_bytes_ == 0)
        out << "{}" << std::endl;
    else{
        out << "{" << s.str_ << "}" << std::endl;
    }
    return out;
}

bool String::operator<(const String &s) const {
    int i{0};
    int j{0};
    if(size_ != num_bytes_ - 1 || s.size_ != s.num_bytes_ - 1)
        throw std::runtime_error("operators of comparison work only with Ascii codes due to default operators to compare letters");
    if(num_bytes_ == 0 && s.num_bytes_ != 0)
        return true;
    if(num_bytes_ != 0 && s.num_bytes_ == 0)
        return false;
    if(num_bytes_ == 0 && s.num_bytes_ == 0)
        return false;

    while(i < num_bytes_ || j < s.num_bytes_){
        if(str_[i] < s.str_[j])
            return true;
        else if(str_[i] > s.str_[j])
            return false;
        ++i;
        ++j;
    }
    return false;
}

bool String::operator>(const String &s) const {
    return s < *this;
}

bool String::operator==(const String &s) const {
    return !(*this < s || *this > s);
}

bool String::operator!=(const String &s) const {
    return !(*this == s);
}

bool String::operator<=(const String& s) const{
    return (*this < s || *this == s);

}

bool String::operator>=(const String& s) const{
    return (*this > s || *this == s);
}

bool String::operator()(const String &s1, const String &s2) const {
    if(s1.size_ == s1.num_bytes_ - 1 && s2.size_ == s2.num_bytes_ - 1){
        return s1 < s2;
    }
    else{
        int i{0};
        int j{0};
        try{
            while(i < s1.num_bytes_ || j < s2.num_bytes_){
                if(s1.CodeRussianLetter(s1.str_[i], s1.str_[i + 1]) == NOT_RUSSIAN_LETTER && i < s1.num_bytes_ - 1){
                    ++i;
                    continue;
                }
                if(s2.CodeRussianLetter(s2.str_[j], s2.str_[j + 1]) == NOT_RUSSIAN_LETTER && j < s2.num_bytes_ - 1){   //stop at the last letter
                    ++j;
                    continue;
                }
                if(i == s1.num_bytes_ - 1 && j < s2.num_bytes_ - 1)
                    return true;
                if(j == s2.num_bytes_ - 1 && i < s1.num_bytes_ - 1)
                    return false;
                if(s1.CodeRussianLetter(s1.str_[i], s1.str_[i + 1]) ==
                   s2.CodeRussianLetter(s2.str_[j], s2.str_[j + 1])){
                    i += 2;
                    j += 2;
                    continue;
                }
                else
                    return(s1.CodeRussianLetter(s1.str_[i], s1.str_[i + 1]) <
                           s2.CodeRussianLetter(s2.str_[j], s2.str_[j + 1]));
            }
        }catch(std::runtime_error& ex){
            std::cout << ex.what() << std::endl;
            return false;
        }

    }
    return false;
}

String& String::operator+=(const String &s){
    if((this->empty() && s.empty()) || (s.empty() && !this->empty()))
        return *this;
    int new_bytes{0};
    num_bytes_ == 0 ? new_bytes = s.num_bytes_ : new_bytes = this->num_bytes_ + s.num_bytes_ - 1;
    String new_str(new_bytes);
    new_str.SetSize(size_ + s.size_);

    int i{0};
    int j{0};
    while (i < new_bytes) {
        if (i < num_bytes_ - 1) {
            new_str.GetStr()[i] = str_[i];
            ++i;
            continue;
        }
        new_str.GetStr()[i] = s.GetStr()[j];
        ++j;
        ++i;
    }
    *this = new_str;
    return *this;
}

String operator+(const String& s1, const String& s2){
    String sum = s1;
    return sum += s2;
}

void String::SetNumBytes(int n) {
    num_bytes_ = n;
}

char* String::GetStr() const {
    return str_;
}

int String::GetNumBytes() const {
    return num_bytes_;
}

int String::CodeRussianLetter(char c1, char c2) const {
    static FILE* file_with_russian_alphabet = fopen("/home/denis/CLionProjects/String_Lib/rus_alphabet.txt", "r");
    if(!file_with_russian_alphabet){
        throw std::runtime_error("File rus_alphabet can not be openned");
    }
    static char rus_letters[NUM_OF_BYTES_IN_RUSSIAN_ALPHABET] = {};
    static int check_bytes = fread(rus_letters, sizeof(char), NUM_OF_BYTES_IN_RUSSIAN_ALPHABET, file_with_russian_alphabet);
    for(int i = 0; i < check_bytes; ++i){
        if(c1 == rus_letters[i] && c2 == rus_letters[i + 1])
            return i;
        ++i;
    }
    static int nul = fclose(file_with_russian_alphabet);
    return NOT_RUSSIAN_LETTER;
}

bool String::empty() const {
    if(num_bytes_ == 0)
        return true;
    else
        return false;
}

void String::SetSize(int size) {
    size_ = size;
}