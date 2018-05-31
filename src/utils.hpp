#include <tuple>
#include <array>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <numeric>
#ifndef __SYNTHESIS__
#include <iostream>
#endif

#ifndef _UTILS_HPP_
#define _UTILS_HPP_

namespace Util {

// Workaround non constexpr log
// Reference: https://hbfs.wordpress.com/2016/03/22/log2-with-c-metaprogramming/
template<typename T>
constexpr T numbits(T n) { return ((n<2) ? 1 : 1+numbits(n>>1)); }

template <size_t... I>
class index_sequence {};

template <size_t N, size_t ...I>
struct make_index_sequence : make_index_sequence<N-1, N-1,I...> {};

template <size_t ...I>
struct make_index_sequence<0,I...> : index_sequence<I...> {};

template<typename F, typename T>
T fold(const F&, T first) { return first; }

template<typename F, typename T>
T fold(const F& f, T first, T second) { return f(first, second); }

template<typename F, typename T, typename... Args>
T fold(const F& f, T first, T second, Args... args) {
  return fold (f, f(first, second), args...);
}


template <typename F, typename T, size_t... Is>
typename T::value_type array_fold_impl(const F& f, 
                                       const T& arr, index_sequence<Is...>) {
	return fold(f, arr[Is]...);
}

template <typename F, typename T>
typename T::value_type array_fold(const F& f, const T& arr) {
	auto Indices = make_index_sequence<std::tuple_size<T>::value>{};
    return array_fold_impl(f, arr, Indices);
}

} //namespace Util

#endif
