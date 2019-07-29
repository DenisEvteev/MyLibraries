//
// Created by denis on 22.07.19.
//

#ifndef STRING_LIB_STRING_HPP
#define STRING_LIB_STRING_HPP

#include <iostream>
#include <cstdio>
#include <exception>

#define TOP_ASCII 127
#define BOTTOM_ASCII 0
#define NUM_OF_BYTES_IN_RUSSIAN_ALPHABET 132 //due to lower and upper registers
#define NOT_RUSSIAN_LETTER -230


class String {
public:
    String(const char* str);

    explicit String(int bytes);

    ~String();

    String();

    String& operator=(const String& s);

    String(const String& s);

    bool empty()const;

    bool operator < (const String& s) const;  //only for english letters
    bool operator > (const String& s) const;
    bool operator == (const String& s) const;
    bool operator != (const String& s) const;
    bool operator <= (const String& s) const;
    bool operator >= (const String& s) const;

    String& operator += (const String& s);
    friend String operator + (const String& s1, const String& s2);


    void SetNumBytes(int n);
    char* GetStr()const;
    int GetNumBytes()const;
    void SetSize(int size);

    bool operator()(const String& s1, const String& s2)const;   //class String can be a functor for comparison objects of String

    friend std::ostream&operator<<(std::ostream& out, const String& s);
    friend std::istream&operator>>(std::istream& in, String& s);

private:
    char* str_;
    int size_;    //number of letters
    int num_bytes_;


    int StrLen(const char* str)const;
    bool IsThisByteAscii(char c) const;
    int CountBytes(const char* str) const;
    int CodeRussianLetter(char c1, char c2)const;
};


#endif //STRING_LIB_STRING_HPP
