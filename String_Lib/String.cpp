//
// Created by denis on 22.07.19.
//

#include "String.hpp"

String::String(const char* str) {
    size_ = StrLen(str);
    num_bytes_ = CountBytes(str);
    str_ = new char[num_bytes_]{};
    for(int i = 0; i < num_bytes_; ++i)
        str_[i] = str[i];
}

String::String(String&& st)noexcept{
    MoveData(std::move(st));
}

void String::MoveData(String&& st)noexcept {
    str_ = st.str_;
    size_ = st.size_;
    num_bytes_ = st.num_bytes_;
    is_english = st.is_english;
    st.size_ = 0;
    st.num_bytes_ = 0;
    st.str_ = nullptr;
}

String& String::operator=(String&& st) & noexcept{
    if(!this->empty())
        delete[] str_;
    MoveData(std::move(st));
    return *this;
}

String::String(int bytes) {
    if(bytes <= 0){
        FIRST_THROW(CodeErrors::ERROR_INVALID_SIZE_FOR_ALLOCATON, "Cannot call this constructor of String with such a num_bytes")
    }

    num_bytes_ = bytes;

    str_ = new char[num_bytes_]{};

    size_ = 0;
}

String::String(){
    size_ = num_bytes_ = 0;
    str_ = nullptr;
}

String::String(const String& s){
    size_ = s.size_;
    num_bytes_ = s.num_bytes_;
    str_ = new char[num_bytes_]{};
    for(int i = 0; i < num_bytes_; ++i)
        str_[i] = s.str_[i];

    is_english = s.is_english;
}

/*String::String(){
    size_ = 0;
    num_bytes_ = 0;
    str_ = nullptr;
}*/

String& String::operator=(const String& s) & {
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

        str_ = new char[num_bytes_]{};

        for(int i = 0; i < num_bytes_; ++i)
            str_[i] = s.str_[i];
    }
    is_english = s.is_english;
    return *this;
}

String::~String() {

    if(num_bytes_)
        delete[] str_;

    str_ = nullptr;

    size_ = 0;
    num_bytes_ = 0;

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
    if(!str)
        throw std::runtime_error("This string is invalid, so it is not available to give it's length");
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

    int flag{0};
    char c{'\0'};

    char static_array[SIZE_ARRAY_FOR_STR];
    for(int i = 0; i < SIZE_ARRAY_FOR_STR; ++i)
        static_array[i] = '\0';

    std::cout << "Enter the str : " << std::endl;

    //--------------------------------------------------------//
    int i{0};
    while(c != '\n'){
        scanf("%c", &c);
        if(c == '\n' && flag == 0){
            flag = 1;
            continue;
        }
        static_array[i] = c;
        ++i;
    }
    //______________________________________________________//

    s = String(static_array);

    return in;
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
    /*if(size_ != num_bytes_ - 1 || s.size_ != s.num_bytes_ - 1)
        throw std::runtime_error("operators of comparison work only with Ascii codes due to default operators to compare letters");*/
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

char* String::GetStr() const{
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


void String::MakeStrFromFile(const char *path_to_file) {

    if(!path_to_file) {
        const char* error_msg = "__ERROR__ This pointer is pointed to NULL";
        FIRST_THROW(CodeErrors::ERROR_INVALID_PATH_TO_FILE, error_msg)
    }


    FILE* file_with_data = fopen(path_to_file, "r");

    if(!file_with_data){
        FIRST_THROW(CodeErrors::ERROR_READ_FILE, "Cannot open this file")
    }

    fseek(file_with_data, 0, SEEK_END);


    int bytes_ = ftell(file_with_data);

    if(bytes_ == ERROR_FTELL){
        const char* error_msg = "__ERROR__ Function ftell() returned with an error";
        fclose(file_with_data);
        FIRST_THROW(CodeErrors::ERROR_IN_FTELL, error_msg)
    }


    if(!this->empty())
        delete[] str_;


    str_ = new char[bytes_ + 1]{};

    num_bytes_ = bytes_ + 1;

    rewind(file_with_data);

    size_t rigth_bytes = fread(str_, sizeof(char), bytes_, file_with_data);

    str_[bytes_] = '\0';

    size_ = StrLen(str_);

    fclose(file_with_data);
}


String::letter String::operator[](int i){
    if(i < 0 || i >= size_){
        FIRST_THROW(CodeErrors::ERR0R_INVALID_INDEX, "__ERROR__ You won't be able to get access to this memory!!!")
    }

    int num_letter{0};

    for(int ip = 0; ip < num_bytes_ - 1; ++ip) {
        if (i == num_letter)
            return letter(&str_[ip], static_cast<int>(IsThisByteAscii(str_[ip])));
        ++num_letter;
        if (!IsThisByteAscii(str_[ip]))
            ++ip;
    }
}

const String::letter String::operator[](int i)const{

    if(i < 0 || i >= size_){
        FIRST_THROW(CodeErrors::ERR0R_INVALID_INDEX, "__ERROR__ You won't be able to get access to this memory!!!")
    }

    int num_letter{0};

    for(int ip = 0; ip < num_bytes_ - 1; ++ip) {
        if (i == num_letter)
            return letter(&str_[ip], static_cast<int>(IsThisByteAscii(str_[ip])));
        ++num_letter;
        if (!IsThisByteAscii(str_[ip]))
            ++ip;
    }

}

String::letter::letter(char *ptr_, int type_ptr) : ptr_letter(ptr_), size_b(type_ptr) {}

bool String::letter::sz()const{
    return String::letter::size_b;

}

char* String::letter::ptr_() const {
    return String::letter::ptr_letter;
}

std::ostream& operator<<(std::ostream& out, const String::letter& el){
    out << "The letter is : ";
    if(el.sz())
        out << *el.ptr_() << std::endl;
    else
        out << *el.ptr_() << *(el.ptr_() + 1) << std::endl;
    return out;
}

bool String::letter::operator==(const char c)const {
    return (static_cast<int>(*String::letter::ptr_letter) == static_cast<int>(c));
}

bool String::letter::operator!=(const char c)const{
    return !(*this == c);
}

String String::operator()(int first_letter, int letter_after_last)const{
    if((first_letter < 0 || first_letter >= size_) ||
       (letter_after_last <= 0 || letter_after_last > size_)) {
        FIRST_THROW(CodeErrors::ERROR_INVALID_CUT_STRING, "You cannot cut such a part of this String")
    }

    int start_pos = CurrentPosByte(first_letter);
    int pos_after_last_byte = CurrentPosByte(letter_after_last);

    try{
        String new_str(pos_after_last_byte - start_pos + 1);

        for(int i = 0; i <= new_str.num_bytes_ - 1; ++i){
            if(i == new_str.num_bytes_ - 1){
                new_str.str_[i] = '\0';
                break;
            }
            new_str.str_[i] = str_[start_pos];
            ++start_pos;
        }

        new_str.size_ = StrLen(new_str.str_);

        if(new_str.size_ == new_str.num_bytes_ - 1)
            new_str.is_english = true;

        return new_str;

    }catch(My_Exception* ex){
        std::cout << ex->what() << std::endl;
        THROW_NEXT(CodeErrors::ERROR_IN_STRING, ex)
    }

}

int String::CurrentPosByte(int i)const noexcept{
    int cur_b{0};
    int cur_l{0};
    while(cur_b < num_bytes_){
        if(cur_l == i)
            return cur_b;
        ++cur_l;
        IsThisByteAscii(str_[cur_b]) ? ++cur_b : cur_b += 2;
    }
}

bool String::is_ascii()const {
    return (size_ == num_bytes_ - 1);
}

int String::find_(const char c) const noexcept {
    for(int i = 0; i < size_; ++i){
        if(str_[i] == c)
            return i;
    }
    return NO_SUCH_LETTER;
}

String::letter& String::letter::operator=(char c){
    if(size_b)
        *ptr_letter = c;
    else{
        FIRST_THROW(CodeErrors::ERROR_INVALID_OPERATION, "You cannot use operator = for not ASCII symbols")
    }
    return *this;
}

int String::size()const{
    return size_;
}

std::wstring String::to_wide_string() const{

    static std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str_);
}
