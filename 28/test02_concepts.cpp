#ifdef HAVE_ARMA
#include <armadillo>                     // arma::imat/imat22
#endif
#include <iostream>                      // std::cout/endl/boolalpha
#include <memory>                        // std::shared_ptr/unique_ptr

using namespace std;

#if defined(__cpp_concepts)

#if __cpp_concepts < 201811

#include <experimental/ranges/concepts>  // concepts defined in ranges
using namespace experimental::ranges;

#else

#include <concepts>                      // standard concepts

template <typename T>
concept readable = indirectly_readable<T>;
template <typename T, typename U>
concept writable = indirectly_writable<T, U>;

#endif

#else // defined(__cpp_concepts)

#error "No support for concepts!"

#endif

#define TEST_CONCEPT(Concept,      \
                     Type)         \
  cout << #Concept << '<' << #Type \
       << ">: "                    \
       << Concept<Type> << endl

#define TEST_CONCEPT2(             \
  Concept, Type1, Type2)           \
  cout << #Concept << '<'          \
       << #Type1 << ", " << #Type2 \
       << ">: "                    \
       << Concept<Type1,           \
                  Type2> << endl

int main()
{
    cout << boolalpha;
    cout << "__cpp_concepts is " << __cpp_concepts << endl;
    TEST_CONCEPT(regular, int);
    TEST_CONCEPT(regular, char);
    TEST_CONCEPT(integral, int);
    TEST_CONCEPT(integral, char);
    TEST_CONCEPT(readable, int);
    TEST_CONCEPT(readable, unique_ptr<int>);
    TEST_CONCEPT2(writable, unique_ptr<int>, int);
    TEST_CONCEPT2(writable, unique_ptr<int>, double);
    TEST_CONCEPT2(writable, unique_ptr<int>, int*);
    TEST_CONCEPT(semiregular, unique_ptr<int>);
    TEST_CONCEPT(semiregular, shared_ptr<int>);
    TEST_CONCEPT(equality_comparable, unique_ptr<int>);
#ifdef HAVE_ARMA
    TEST_CONCEPT(semiregular, arma::imat);
    TEST_CONCEPT2(assignable_from, arma::imat&, arma::imat&);
    TEST_CONCEPT(semiregular, arma::imat22);
    TEST_CONCEPT2(assignable_from, arma::imat22&, arma::imat22&);
#endif
}
