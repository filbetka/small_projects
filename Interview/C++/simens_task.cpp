// What is the result of the given program?

#include <algorithm>
#include <iostream>
#include <vector>

struct A
{
    A() { hello(); }
    ~A() { std::cout << "Bye A" << std::endl; }

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
    std::vector<A*> *vec = new std::vector<A*>();
    vec->push_back( new A() );
    vec->push_back( new B() );
    vec->push_back( new C() );

    std::for_each(vec->cbegin(), vec->cend(), [](A* i){i->hello(); });
    delete vec;

    return 0;
}


