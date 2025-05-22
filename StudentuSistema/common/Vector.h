#pragma once

// TEST MODE: naudok tik kai nori palyginti su std::vector
//#define USE_STD_VECTOR

#ifdef USE_STD_VECTOR
    #include <vector>
    template <typename T>
    using Vector = std::vector<T>;
#else
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
        using iterator = T*;
        using const_iterator = const T*;

        // Konstruktoriai ir destruktorius
        Vector();
        explicit Vector(std::size_t size);
        Vector(std::initializer_list<T> init);
        Vector(const Vector& other);
        Vector(Vector&& other) noexcept;
        ~Vector();

        // Priskyrimo operatoriai
        Vector& operator=(const Vector& other);
        Vector& operator=(Vector&& other) noexcept;

        // Prieigos operatoriai
        reference operator[](size_type index);
        const_reference operator[](size_type index) const;
        reference at(size_type index);
        const_reference at(size_type index) const;
        reference front();
        reference back();
        pointer data();
        const_pointer data() const;

        // Dydis ir talpa
        size_type size() const noexcept;
        size_type capacity() const noexcept;
        bool empty() const noexcept;
        void reserve(size_type new_cap);
        void resize(size_type new_size);
        void shrink_to_fit();

        // Modifikatoriai
        void push_back(const T& value);
        void push_back(T&& value);
        void pop_back();
        void clear();
        iterator insert(iterator pos, iterator first, iterator last);
        iterator erase(iterator first, iterator last);

        // Iteratoriai
        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
    };

    #include "Vector.tpp"
#endif