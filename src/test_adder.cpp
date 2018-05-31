#include <tuple>
#include <array>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <numeric>
#include <iostream>

#include "utils.hpp"

template<size_t N, typename T>
int add(const std::array<T, N>& a)
{
  auto sum_lambda = [](const T a, const T b) -> T { return a + b; };
  return Util::array_fold(sum_lambda, a);
}

int main ()
{
	const std::array<int, 16> a {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	if (std::accumulate(a.begin(), a.end(), 0) != add(a))
		std::cout << "ERROR!\n";
	else
		std::cout << "OK: add = " << add(a) << '\n';
}
