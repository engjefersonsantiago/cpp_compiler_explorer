#include <iostream>
#include <type_traits>

template<typename C, bool B>
struct Dummy {
    C a;

    template<bool Boolean>
    typename std::enable_if<Boolean, void>::type get_member() { a = 1; }

    template<bool Boolean>
    typename std::enable_if<!Boolean, void>::type get_member() { a = 0; }

    template<typename F> C method (const F& f);
};

template<typename C, bool B>
template<typename F>
C Dummy<C,B>::method (const F& f) {
    get_member<B>();
    f(a);
    return a;
}

int main () {

    Dummy<int,true> dt;
    Dummy<int,false> df;

    dt.method([](int c) { std::cout << c << '\n'; });
    df.method([](int c) { std::cout << c << '\n'; });

}
