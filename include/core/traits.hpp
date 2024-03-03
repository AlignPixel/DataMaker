//copy from [std::void_t - cppreference.com](https://en.cppreference.com/w/cpp/types/void_t)#ifndef TRAITS_HPP
#define TRAITS_HPP
#pragma once
#include <type_traits>
#include <fstream>

namespace DATA_MAKER {

    template <typename T, typename = void>
    struct is_iterable : std::false_type {};

    template <typename T>
    struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()),
        decltype(std::declval<T>().end())>>
        : std::true_type {};

    template <typename T, typename = void>
    struct is_outable : std::false_type {};

    template <typename T>
    struct is_outable<T,
        std::void_t<decltype( std::declval<std::ofstream&>() << std::declval<T>() )>
            > : std::true_type {};


    template<size_t N>
    constexpr size_t __get_char_array_size(const char (&a)[N]){ return N;}
    template<typename T,typename = void>
    struct is_const_char_array : std::false_type {};

    template<typename T>
    struct is_const_char_array<T,
        std::void_t<decltype( std::declval<std::ofstream&>() << std::declval<T>() )>
            >
    : std::true_type {};


} // namespace DATA_MAKER
#endif //TRAITS_HPP
