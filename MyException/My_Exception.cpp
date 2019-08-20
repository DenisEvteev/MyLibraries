//
// Created by denis on 10.08.19.
//

#include "My_Exception.hpp"


My_Exception::My_Exception(CodeErrors codeEr, int line_, const char *file_,
        const char *name_function_, const char *message_, My_Exception* prev_)noexcept :

        codeEr(codeEr),
        line_(line_),
        file_(file_),
        name_function_(name_function_),
        message_(message_),
        prev_(prev_) {}


const char* My_Exception::what()const noexcept{
    return message_;
}


void My_Exception::dump_info_in_console() const {
    std::cout << "CODE OF THE ERROR is : " << static_cast<int>(codeEr) << std::endl;
    std::cout << "FILE is : " << file_ << std::endl;
    std::cout << "NAME_OF_FUNCTION is : " << name_function_ << std::endl;
    std::cout << "LINE is : " << line_ << std::endl;

    if(prev_){
        std::cout << "//--------------------------------------------//" << std::endl;
        std::cout << prev_->what() << std::endl;
        prev_->dump_info_in_console();
    }
}

void My_Exception::clear()noexcept{
    if(prev_ != nullptr)
        prev_->clear();
    delete this;
}
