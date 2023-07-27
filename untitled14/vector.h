/*
 * vector.h
 *
 *  Created on: Dec 1, 2016
 *      Author: jkath
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <algorithm> // std::copy
using std::copy;

namespace myStd
{
template <typename T>
class vector
{
    int size_v; 
    T *elem; 
    int space; 
public:
    vector() : size_v{0}, elem{nullptr}, space{0} {}

    explicit vector(int s) : size_v{s}, elem{new T[s]}, space{s}
    {
        for (int i = 0; i < size_v; ++i)
            elem[i] = T{}; 
    }

    vector(const vector &src) : size_v{src.size_v}, elem{new T[src.size_v]}, space{src.space} 
    {
        std::copy(src.elem, src.elem + size_v, elem); 
    }

    vector &operator=(const vector &src)
    {
        T *p = new T[src.size_v]; 
        std::copy(src.elem, src.elem + src.size_v, p); 
        delete[] elem; 
        elem = p; 
        size_v = src.size_v;
        return *this;  
    }
    vector& operator=(vector&& src) noexcept
    {
    if (this != &src) // prevent self-move
    {
        delete[] elem; // delete old elements
        elem = src.elem;
        size_v = src.size_v;
        space = src.space;

        // leave src in a valid state
        src.elem = nullptr;
        src.size_v = 0;
        src.space = 0;
    }
    return *this;
}


    ~vector() { delete[] elem; }

    T &operator[](int n) { return elem[n]; }

    const T &operator[](int n) const { return elem[n]; }

    int size() const { return size_v; }

    int capacity() const { return space; }

    void resize(int newsize) 
    {
        reserve(newsize);
        for (int i = size_v; i < newsize; ++i)
            elem[i] = T{}; 
        size_v = newsize;
    }

    void push_back(T d)
    {
        if (space == 0)
            reserve(8);         
        else if (size_v == space)
            reserve(2 * space); 
        elem[size_v] = d;       
        ++size_v;               
    }

    void reserve(int newalloc)
    {
        if(newalloc <= space) return;
        T *newElem = new T[newalloc];
        for(int i = 0; i < size_v; i++) {
            newElem[i] = elem[i];
        }
        delete[] elem;
        elem = newElem;
        space = newalloc;
    }

    using iterator = T *;
    using const_iterator = const T *;

    iterator begin()
    {
        if (size_v == 0) return nullptr;
        return &elem[0];
    }

    const_iterator begin() const
    {
        if (size_v == 0) return nullptr;
        return &elem[0];
    }

    iterator end()
    {
        if (size_v == 0) return nullptr;
        return &elem[size_v];
    }

    const_iterator end() const
    {
        if (size_v == 0) return nullptr;
        return &elem[size_v];
    }

    iterator insert(iterator p, const T &val)
    {
        int index = p - begin();
        if(size_v == space) {
            if(space == 0) reserve(8);
            else reserve(space * 2);
        }
        iterator position = begin() + index;
        for(iterator it = end(); it != position; it--) {
            *it = *(it - 1);
        }
        *position = val;
        ++size_v;
        return position;
    }

    iterator erase(iterator p)
    {
        if (p == end()) return p;
        for (iterator pos = p + 1; pos != end(); ++pos)
            *(pos - 1) = *pos;
        --size_v;
        return p;
    }
};

}

#endif /* VECTOR_H_ */
