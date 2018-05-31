#include <array>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iterator>
template<size_t N>
struct S {
    std::array<size_t, N> a;

    const size_t &top() const {  std::cout << "const & top\n"; return a.front(); }
    size_t &top() { return a.front(); }

    const size_t &bottom () const { std::cout << "const & bottom\n"; return a.back(); }
    size_t &bottom() { return a.back(); }

    void print_elems() const {
        std::for_each(a.begin(), a.end(), [](const size_t n) {std::cout << n << " "; });
        std::cout << '\n';
    }
};

int main () {
    S<4> s {3,1,5,6};

    s.print_elems();
    s.top() = 16;
    s.print_elems();
    s.bottom() = 100;
    s.print_elems();
}
