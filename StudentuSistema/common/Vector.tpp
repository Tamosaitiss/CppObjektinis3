#pragma once

#include <algorithm>

template <typename T>
Vector<T>::Vector() : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
Vector<T>::Vector(std::size_t size)
    : data_(new T[size]()), size_(size), capacity_(size) {}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : data_(new T[init.size()]), size_(init.size()), capacity_(init.size()) {
    std::copy(init.begin(), init.end(), data_);
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] data_;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] data_;
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type index) {
    return data_[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type index) const {
    return data_[index];
}

template <typename T>
typename Vector<T>::reference Vector<T>::at(size_type index) {
    if (index >= size_) throw std::out_of_range("Index out of bounds");
    return data_[index];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::at(size_type index) const {
    if (index >= size_) throw std::out_of_range("Index out of bounds");
    return data_[index];
}

template <typename T>
typename Vector<T>::reference Vector<T>::front() {
    return data_[0];
}

template <typename T>
typename Vector<T>::reference Vector<T>::back() {
    return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::pointer Vector<T>::data() {
    return data_;
}

template <typename T>
typename Vector<T>::const_pointer Vector<T>::data() const {
    return data_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
void Vector<T>::reserve(size_type new_cap) {
    if (new_cap > capacity_) {
        increase_capacity(new_cap);
    }
}

template <typename T>
void Vector<T>::resize(size_type new_size) {
    if (new_size > capacity_) {
        increase_capacity(new_size);
    }
    size_ = new_size;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (size_ < capacity_) {
        T* new_data = new T[size_];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        increase_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = value;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (size_ == capacity_) {
        increase_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    data_[size_++] = std::move(value);
}

template <typename T>
void Vector<T>::pop_back() {
    if (size_ > 0) --size_;
}

template <typename T>
void Vector<T>::clear() {
    size_ = 0;
}

template <typename T>
void Vector<T>::increase_capacity(size_type new_cap) {
    ++resize_counter;
    T* new_data = new T[new_cap];
    for (size_type i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
}

template <typename T>
T* Vector<T>::begin() {
    return data_;
}

template <typename T>
T* Vector<T>::end() {
    return data_ + size_;
}

template <typename T>
const T* Vector<T>::begin() const {
    return data_;
}

template <typename T>
const T* Vector<T>::end() const {
    return data_ + size_;
}