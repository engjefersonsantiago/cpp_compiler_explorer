#include <cstdint>
#include <iostream>

template <typename T>
class Sum {
public:
    T operator()(const T& a, const T& b) const {
        return a + b;
    }
};

inline int sum (const int& a, const int& b) { return a + b; }

template <typename F, typename... Args>
int get_sum (const F& f, Args... args) { return f(args...); }

int lambda_ptr (const int& a, const int& b) {
    // Object c is a functor
    Sum<int> c;
    // fptr is a function point
    int(*fptr)(const int&, const int&) = *sum;
    // Lambda is a lambda expression
    auto lambda = [](const int& a, const int& b) -> int { return a + b; };

    return get_sum(c, a, b) + get_sum(lambda, a, b) + get_sum(fptr, a, b);
}

int main () {
    std::cout << lambda_ptr(1,2) << '\n';
}
