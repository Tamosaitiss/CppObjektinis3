#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>

template <typename T>
class Vector {
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void increase_capacity(std::size_t new_cap);

public:
    inline static std::size_t resize_counter = 0;
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    Vector();                               // Default constructor
    explicit Vector(std::size_t size);      // Sized constructor
    Vector(std::initializer_list<T> init);  // Initializer list
    Vector(const Vector& other);            // Copy constructor
    Vector(Vector&& other) noexcept;        // Move constructor
    ~Vector();                              // Destructor

    Vector& operator=(const Vector& other); // Copy assignment
    Vector& operator=(Vector&& other) noexcept; // Move assignment

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    reference at(size_type index);
    const_reference at(size_type index) const;

    reference front();
    reference back();
    pointer data();
    const_pointer data() const;

    size_type size() const noexcept;
    size_type capacity() const noexcept;
    bool empty() const noexcept;
    void reserve(size_type new_cap);
    void resize(size_type new_size);
    void shrink_to_fit();

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void clear();

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
};

#include "Vector.tpp"