//
// Created by denis on 10.08.19.
//
#pragma once


#include <bits/exception.h>
#include <iostream>

#define MESSAGE_FARTHER "go farther"


#define FIRST_THROW(code, msg)\
throw new My_Exception(code, __LINE__, __FILE__,  __PRETTY_FUNCTION__, msg, nullptr);\


#define THROW_NEXT(code, prev_ex)\
throw new My_Exception(code, __LINE__, __FILE__, __PRETTY_FUNCTION__, MESSAGE_FARTHER, prev_ex);\




enum class CodeErrors : unsigned {
    ERROR_READ_FILE,
    ERROR_INVALID_PATH_TO_FILE,
    ERROR_IN_FTELL,
    ERROR_IN_CONSTRUCTOR,
    ERR0R_INVALID_INDEX,
    ERROR_INVALID_CUT_STRING,
    ERROR_INVALID_SIZE_FOR_ALLOCATON,
    ERROR_IN_STRING,
    ERROR_BAD_DATA,
    ERROR_INVALID_OPERATION,
    ERROR_N = 230
};



class My_Exception : public std::exception{

public:
    My_Exception(CodeErrors codeEr, int line_, const char* file_, const char* name_function_,
            const char* message_, My_Exception* prev_) noexcept;

    My_Exception() = delete;

    virtual const char* what() const noexcept override;

    My_Exception(const My_Exception& ex) = default;

    ~My_Exception() = default;

    void dump_info_in_console()const;

    void clear()noexcept;


private:
    CodeErrors          codeEr;
    const int           line_;
    const char*         file_;
    const char*         name_function_;
    const char*         message_;
    My_Exception*       prev_;


};
