#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>

/**
 * @brief Dinaminis konteineris, veikiantis kaip std::vector analogas.
 *
 * @tparam T Saugojamas duomenų tipas
 */
template <typename T>
class Vector {
private:
    T* data_;               ///< Pointeris į duomenų masyvą
    std::size_t size_;      ///< Esamų elementų skaičius
    std::size_t capacity_;  ///< Skirta talpa masyve

    /**
     * @brief Talpos didinimas nurodytam dydžiui
     * @param new_cap Naujas talpos dydis
     */
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

    /** @brief Sukuria tuščią vektorių */
    Vector();

    /**
     * @brief Sukuria vektorių su nurodytu dydžiu
     * @param size Pradinis dydis
     */
    explicit Vector(std::size_t size);

    /**
     * @brief Sukuria vektorių iš sąrašo
     * @param init Inicializacijos sąrašas
     */
    Vector(std::initializer_list<T> init);

    /** @brief Kopijavimo konstruktorius */
    Vector(const Vector& other);

    /** @brief Perkėlimo konstruktorius */
    Vector(Vector&& other) noexcept;

    /** @brief Destruktorius */
    ~Vector();

    /** @brief Kopijavimo priskyrimo operatorius */
    Vector& operator=(const Vector& other);

    /** @brief Perkėlimo priskyrimo operatorius */
    Vector& operator=(Vector&& other) noexcept;

    /**
     * @brief Prieiga prie elemento per indeksą (nesaugi)
     * @param index Indeksas
     * @return Nuoroda į elementą
     */
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    /**
     * @brief Saugi prieiga prie elemento
     * @param index Indeksas
     * @return Nuoroda į elementą
     */
    reference at(size_type index);
    const_reference at(size_type index) const;

    /** @brief Grąžina pirmą elementą */
    reference front();
    /** @brief Grąžina paskutinį elementą */
    reference back();

    /** @brief Grąžina duomenų pointerį */
    pointer data();
    const_pointer data() const;

    /** @brief Grąžina elementų skaičių */
    size_type size() const noexcept;
    /** @brief Grąžina šiuo metu rezervuotą talpą */
    size_type capacity() const noexcept;
    /** @brief Patikrina ar tuščias */
    bool empty() const noexcept;

    /** @brief Rezervuoja daugiau vietos */
    void reserve(size_type new_cap);
    /** @brief Pakeičia dydį */
    void resize(size_type new_size);
    /** @brief Apkarpo talpą iki dydžio */
    void shrink_to_fit();

    /** @brief Prideda elementą į galą */
    void push_back(const T& value);
    void push_back(T&& value);

    /** @brief Pašalina paskutinį elementą */
    void pop_back();

    /** @brief Išvalo visus elementus */
    void clear();

    /** @brief Iteratorių metodai */
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    /**
     * @brief Įterpia elementus nurodytoje pozicijoje
     * @param pos Vieta, kur įterpti
     * @param first Pradžia
     * @param last Pabaiga
     * @return Iteratorius į pirmą įterptą elementą
     */
    iterator insert(iterator pos, iterator first, iterator last);

    /**
     * @brief Pašalina intervalą
     * @param first Pradžia
     * @param last Pabaiga
     * @return Iteratorius į vietą po paskutinio pašalinto elemento
     */
    iterator erase(iterator first, iterator last);
};

#include "Vector.tpp"
