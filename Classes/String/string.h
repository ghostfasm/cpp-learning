#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>
// #include <string>
 
class String {
private:
    mutable size_t size = 0;
    mutable size_t m_sizeAlloc = 0;
    mutable char* str = nullptr;
 
    void swap(String& s) {
        std::swap(size, s.size);
        std::swap(str, s.str);
        std::swap(m_sizeAlloc, s.m_sizeAlloc);
    }
 
 
   inline void allocate_add_up(const size_t& s) {
      ensure_size(size + s);
   }
 
   void ensure_size(const size_t& sNew) {
 
    if (sNew <= m_sizeAlloc) {
        size = sNew;
        return;
    }

    m_sizeAlloc = sNew * 2;
    char* pstrNew = new char[m_sizeAlloc];
    if (str != nullptr) {
        memcpy(pstrNew, str, size);
        delete[] str;
    }
    
    str = pstrNew;
    size = sNew;
 
    }
 
public:
    friend std::istream& operator>>(std::istream& is, const String& a);
    friend std::ostream& operator<<(std::ostream& is, const String& a);
    friend bool operator==(const String& s1, const String& s2);
    
    String(size_t n = 0, char ch = '\0'): size(n), m_sizeAlloc(size * 2), str(new char[m_sizeAlloc]) {
        if (n) memset(str, ch, n);
    }

    String(char ch): size(1), m_sizeAlloc(size * 2), str(new char[1]) {
        str[0] = ch;
    }
 
    String(const char* cstr): size(std::strlen(cstr)), m_sizeAlloc(size * 2), str(new char[m_sizeAlloc]) {
        memcpy(str, cstr, size);
    }
 
    String(const String& s): String(s.size, '\0') {
        memcpy(str, s.str, size);
    }
 
    String& operator=(String s) {
        swap(s);
 
        return *this;
    }
 
    // String& operator=(const char* cstr) {
    //     size = std::strlen(cstr);
    //     if (str != nullptr) clear();
    //     str = new char[size];
    //     memcpy(str, cstr, size);
 
    //     return *this;
    // }
 
    const String& operator=(char cstr)  {
        ensure_size(1);
        str[0] = cstr;
        // if (str != nullptr) clear();
        // size = 1;
        // str = new char[size];
        // str[0] = cstr;
 
        return *this;
    }
 
    const String& operator=(const char* cstr) {
        size = strlen(cstr);
        ensure_size(size);
        memcpy(str, cstr, size);
 
        return *this;
        // if (str != nullptr) clear();
        // size = std::strlen(cstr);
        // str = new char[size];
        // memcpy(str, cstr, size);
 
        // return *this;
    }
 
    char& operator[](size_t& index) {
        return str[index];
    }
 
    const char& operator[](const size_t& index) const {
        return str[index];
    }
 
    void push_back(char& s) {
        allocate_add_up(1);
 
        str[size-1] = s;
 
        // char* temp = new char(s);
        // *this += temp;
        // delete[] temp;
    }
 
    void pop_back() {
      if (size == 0)
      {
 
         throw "invalid call";
 
      }
      size--;
    //   ensure_size(size);
 
 
        // String s = substr(0, size - 1);
        // *this = s;
    }
 
    char& front() {
 
        return str[0];
    }
 
    char& back() {
 
        return str[size - 1];
    }
 
    char front() const {
 
        return str[0];
    }
 
    char back() const {
 
        return str[size - 1];
    }
 
    String& operator+=(const String& s) {
        size_t currSize = size;
        allocate_add_up(s.size);
        memcpy(str + currSize, s.str, s.size);
 
        return *this;
    }
 
    String operator+(const String& str) {
        String temp = *this;
        temp += str;
 
        return temp;
    }
    
    bool isSubstr(const String& sub, const size_t pos) const {
        if (sub.size + pos > size) return false; //вылезли за пределы
        for (size_t i = 0; i < sub.size; i++) {
            if (sub.str[i] != str[i+pos]) return false;
        }
        return true;
    }
    
    String substr(const size_t& start, const size_t& count) const {
        String temp(count);
        for (size_t i = start, j = 0; i < start + count; i++, j++) {
            temp[j] = str[i];
        }
        // memcpy(temp.str, str + start, count);
 
        return temp;
    }
 
    void clear() {
        if (size != 0)
        {
            ensure_size(0);
            str[0] = ' ';
        }

    }
 
    bool empty() const {

        return size == 0 ? true : false;
    }
 
    size_t length() const {
 
        return size;
    }
 
    size_t find(const String& sub) const {

        if (size < sub.size) return size;
 
        for (size_t i = 0; i < size - sub.size; ++i) {
            if(isSubstr(sub, i))
                return i;
        }
 
        return size;
    }
 
    size_t rfind(const String& sub) const {

        if (size < sub.size) return size;
 
        for (size_t i = size - sub.size; i > 0; --i) {
            if(isSubstr(sub, i))
                return i;
        }
 
        return size;
    }

    ~String() {
        if (str != nullptr)
            delete[] str;
    }
    
};
 
std::ostream& operator<<(std::ostream& out, const String& str) {
    for (size_t i = 0; i < str.size; i++)
        out << str.str[i];
    // out << str.str;
    return out;
}
 
std::istream& operator>>(std::istream& in, String& str) {
    
    char* c = new char[5];
    in >> c;
    str = String(c);
    delete[] c;
 
    return in;
}
 
String operator+(const String& s1, const String& s2) {
    String temp = s1;
    temp += s2;
 
    return temp;
}
 
bool operator==(const String& s1, const String& s2) {
 
    // if (strcmp(s1.str, s2.str) == 0) return true;
    // else return false;

    if (s1.str == s2.str) return true; //это одна и так же строка, выходим
    if (s1.size != s2.size) return false; //размеры строк разные, строки разные, выходим
    if (s1.size == 0) return true; //это пустые строки, они очевидно равны
    return memcmp(s1.str, s2.str, s1.size) == 0; //сравниваем куски памяти

    // if (s1.length() != s2.length()) return false;
    // for (size_t i = 0; i < s1.length(); ++i) {
    //     if (s1[i] != s2[i]) return false;
    // }
 
    return true;
}
