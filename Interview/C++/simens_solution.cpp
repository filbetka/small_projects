// What is the result of the given program?

#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;


struct A
{
    A() { hello(); }
    virtual ~A() { std::cout << "Bye A" << std::endl; }

    virtual void hello() const { std::cout << "Hello A" << std::endl; }
};

struct B : public A
{
    ~B() { std::cout << "Bye B" << std::endl; }

    virtual void hello() const { std::cout << "Hello B" << std::endl; }
};

struct C : public B
{
    ~C() { std::cout << "Bye C" << std::endl; }

    virtual void hello() const { std::cout << "Hello C" << std::endl; }
};

int main()
{
	// na początku wersja na surowych wskaźnikach
	// również wektor był alokowany na stercie
    std::vector<unique_ptr<A>> vec; // 
    vec.push_back( make_unique<A>() ); // Hello A\n
    vec.push_back( make_unique<B>() ); // Hello A\n
    vec.push_back( make_unique<C>() ); // Hello A\n

    std::for_each(vec.cbegin(), vec.cend(), [](const auto& i){ i->hello(); }); // Hello A\nHello B\nHello C\n

    return 0;
}// Bye A\nBye B\nBye A\nBye C\nBye B\nBye A\n


