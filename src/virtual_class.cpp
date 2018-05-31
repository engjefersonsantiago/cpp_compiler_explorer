#include <array>
#include <cstdint>
#include <algorithm>
#ifndef _SYNTHESIS__
#include <iostream>
#endif

//#define COMPILE_VIVADO_GOOD

class Base {
  protected:
    std::array<size_t, 2> member;
  public:
    Base(const std::array<size_t, 2>& member_) : member(member_){}
#ifdef COMPILE_VIVADO_GOOD
    virtual void math_function (size_t&) =0;
#else
    virtual void math_function (size_t&) {}  // Compiles as well
#endif
    void math (size_t&  result) { math_function(result); }
    virtual ~Base(){}
};

class Derived : public Base {
  public:
	Derived(const std::array<size_t, 2>& member_) : Base (member_){}
    void math_function (size_t&  result) {
        result = this->member[0] + this->member[1]; 
        this->member[0]--; this->member[1]++; 
    }
};

template<size_t N>
class Base_T {
  protected:
    std::array<size_t, 2> member;
  public:
    Base_T(const std::array<size_t, 2>& member_) : member(member_){}
#ifdef COMPILE_VIVADO_GOOD
    virtual void math_function (size_t&) {}
#else
    virtual void math_function (size_t&) =0;
#endif

#ifdef COMPILE_VIVADO_GOOD
    void math (size_t&  result) { this->math_function(result); }
#else
    void math (size_t&  result) {
    	math_function(result); // math_function not a member
    }
#endif
    virtual ~Base_T(){}
};

template<size_t N>
class Derived_T final : public Base_T<N> {
  public:
	Derived_T(const std::array<size_t, 2>& member_) : Base_T<N>(member_){}
    void math_function (size_t&  result) {
    	result = this->member[0] + this->member[1];
        this->member[0]--; this->member[1]++; 
    }
};

void fooSum (size_t& result, const size_t& a, const size_t& b){
  const std::array<size_t, 2> A = {a,b};
  size_t resultT = 0, result_ = 0;
  Derived fooDerived(A);
  fooDerived.math(result_);
  Derived_T<4> fooDerivedT(A);
  fooDerivedT.math(resultT);
  result = result_ + resultT;
}

size_t add(const std::array<size_t, 2>& a)
{
  size_t result = 0;
  fooSum(result, a[0], a[1]);
  return result;
}

#ifndef _SYNTHESIS__
int main ()
{
	const std::array<size_t, 2> a {{1,2}};
	if (2*std::accumulate(a.begin(), a.end(), 0) != add(a))
		std::cout << "ERROR!\n";
	else
		std::cout << "OK: add = " << add(a) << std::endl ;
}
#endif
