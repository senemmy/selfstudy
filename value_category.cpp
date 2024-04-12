#include <iostream>
#include <string>

template<typename T>
struct Tester {
	static constexpr const char *p = "R value expr.";
};


template<typename T>
struct Tester<T &> {
	static constexpr const char *p = "L value expr.";
};

template<typename T>
struct Tester<T &&> {
	static constexpr const char *p = "X value expr.";
};


using namespace std;

int &&foo();

int main()
{
	int x = 10;
	int *ptr = &x;

	cout << "value category : " << Tester<decltype((x))>::p << "\n";
	cout << "value category : " << Tester<decltype(*ptr)>::p << "\n";
	cout << "value category : " << Tester<decltype(10)>::p << "\n";
	cout << "value category : " << Tester<decltype(foo())>::p << "\n";

	return 0;
}