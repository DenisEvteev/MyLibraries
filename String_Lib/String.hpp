//
// Created by denis on 22.07.19.
//

#ifndef STRING_LIB_STRING_HPP
#define STRING_LIB_STRING_HPP
#include "/home/denis/CLionProjects/MyExceptions/My_Exception.hpp"


#include <iostream>
#include <cstdio>
#include <exception>
#include <cstring>


#include <locale>
#include <codecvt>
#include <string>


#define TOP_ASCII 127
#define BOTTOM_ASCII 0
#define NUM_OF_BYTES_IN_RUSSIAN_ALPHABET 132 //due to lower and upper registers
#define NOT_RUSSIAN_LETTER -230
#define ERROR_FTELL -1L
#define NO_SUCH_LETTER -230
#define SIZE_ARRAY_FOR_STR 100

class String {
public:
    explicit String(const char* str);


    //move-constructor
    String(String&& st)noexcept;

    explicit String(int bytes);

    ~String();

    String();


    void MoveData(String&& st)noexcept;

    String& operator=(const String& s) & ;

    //move assignment operator
    String& operator=(String&& s) & noexcept;


    String(const String& s);

    bool empty()const;

    void MakeStrFromFile(const char * path_to_file);

    bool operator < (const String& s) const;  //only for english letters
    bool operator > (const String& s) const;
    bool operator == (const String& s) const;
    bool operator != (const String& s) const;
    bool operator <= (const String& s) const;
    bool operator >= (const String& s) const;

    String& operator += (const String& s);
    friend String operator + (const String& s1, const String& s2);

    /*____This Proxy class named letter will help you to manage with operator[]
     * for my container String.
     * The problem which can confuse you during working with operator[] without this Proxy class
     * in my container exists due to possibility of working with not ASCII letters which has
     * some difficulties when you work in utf-8____*/

    class letter{
    public:

        /*If size_b == 0 then it is a not ascii letter
         * if size_b == 1 then it is a ascii letter*/
        letter(char* ptr_, int type_ptr);
        letter() = delete;
        bool sz()const;
        char* ptr_()const;

        /*This operator works right only with ascii letters*/
        letter& operator=(char c);


        /*These operators were written for another project so their main goal to compare
         * only ASCII letters*/
        bool operator==(const char c)const;
        bool operator!=(const char c)const;
        //-----------------------------------------------------------------------------//

        /*This friend method is for debug*/
        friend std::ostream& operator<<(std::ostream& out, const String::letter& el);
    private:
        bool size_b = true;
        char* ptr_letter;
    };

    /*This operators will throw an object of My_Exception class
     * if _i_ will be invalid for getting the access*/

    letter operator[](int i);
    const letter operator[](int i)const;


    void SetNumBytes(int n);
    char* GetStr()const;
    int GetNumBytes()const;
    void SetSize(int size);
    int size()const;
    bool is_ascii()const;
    bool IsThisByteAscii(char c) const;

    bool operator()(const String& s1, const String& s2)const;   //class String can be a functor for comparison objects of String

    String operator()(int first_letter, int letter_after_last)const;


    /*This function will find the first entry of element c in String
     * and it will return it position in index form.
     * If there isn't any elements c in String it will return -230
     * it's a standard way to tell about not positive result ;)
     * And to say another important data about this function :
     * You shouldn't use it for not ascii element c due to it was written
     * to simplify work at another project*/

    int find_(const char c)const noexcept;

    friend std::ostream&operator<<(std::ostream& out, const String& s);
    friend std::istream&operator>>(std::istream& in, String& s);

    std::wstring to_wide_string()const;

private:
    char* str_;
    int size_;    //number of letters
    int num_bytes_;
    bool is_english = false;     // this value will show if the string is ASCII or not


    int StrLen(const char* str)const;
    int CountBytes(const char* str) const;
    int CodeRussianLetter(char c1, char c2)const;
    int CurrentPosByte(int i)const noexcept;
};

#endif //STRING_LIB_STRING_HPP
