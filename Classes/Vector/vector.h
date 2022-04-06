#include <iostream>
#include <vector>
// Vector implementation

template<typename T>
class Vector {
    T* arr;
    size_t sz;
    size_t cap;

public:
    Vector(size_t n, const T& value = T());

    T& operator[](size_t i) {
        return arr[i];
    }

    T& at(size_t i) {
        if (i >= sz) throw std::out_of_range("...");
        return arr[i];
    }


    const T& operator[](size_t i) const {
        return arr[i];
    }

    const T& at(size_t i) const { // работает медленее чем []
        if (i >= sz) throw std::out_of_range("...");
        return arr[i];
    }

    size_t size() const {
        return sz;
    }
    void resize(size_t, const T& value = T()) {
        if (n < cap) reserve(cap);
        for (size_t i = sz; i < n; ++i) {
            // если n > sz, то наложить value
        }
    }

    size_t capacity() const {
        return cap;
    }

    void reserve(size_t n) { // должен выделить памяти столько, чтобы его хватило хотя бы на n элементов (меняет размер) 
        if (n < cap) return;

        // код на двойку (naive)
        T* newarr = new reinterpret_cast<T*>(new int8_t[n * sizeof(T)]). // оператор new может кинуть std::bad_alloc
        size_t i = 0;        
        

        // весь ниже try-catch оборачивается в функцию
        try {
            std::unitialized_copy(arr, arr + sz, newarr); // оборачивает в себя логику что получилось или не получилось скопировать, если не получилось - бросает исключение.
        } catch (...) {
            delete[] reinterpret_cast<int8_t*>(arr);
            throw;
        }

        for (size_t i = 0; i < sz; ++i) {
            (arr + i)->~T(); // можно решить через std::move

        }
    
        //delete[] arr; // arr - массив, но реально там не лежит capacity объектов типа T. Если написать delete[] то он capacity раз вызовет деструктор
        // nencpy можно только для тривиальных типов, где нет например ссылок
        delete reinterpret_cast<int8_t*>(arr);
        arr = newarr;
    }

    void push_back(const T& value) {
        if (sz == cap) reserve(2 * cap);
        // положить объект типа T по адресу
        new(arr + sz) T(value);
        ++sz;
    }

    void pop_back() {
        (arr+sz-1)->~T();
        --sz;
    }
};

template <>
class Vector<bool> {
    int8_t* arr;
    size_t sz;
    size_t cp;

    // структура позволяет присваивая экземпляру себя на самом деле менять исходный вектор
    struct BitReference {
        int8_t* cell;
        uint8_t num; // номер позиции в этой ячейке

        BitReference& operator=(bool b) {
            if (b) {
                *cell |= (1u << num); // создать бит
            } else {
                *cell &= ~(1u << num); // погасить бит
            }

            return *this;
        }

        operator bool() const {
            // конвертация BitReference в bool
            return *cell & (1u << num);
        }
    };
public:
    BitReference operator[](size_t i) {
        return BitReference{arr + i / 8, i % 8};
    }
};
