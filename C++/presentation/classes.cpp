#include <iostream>

using namespace std;


class Abstract
{
    public:
        virtual void someMethod() = 0;
};


class Next : public Abstract
{
    public:
        virtual void someMethod() override {}
};


class End : public Next
{
    public:
        
        End(End&& object) { cout << "move\n"; }
        //End(const End& object) { cout << "copy\n"; }
        End() = default;
    
        virtual void someMethod() final {}
        void anotherMethod() = delete;
        void noexceptMethod() noexcept {}
        
        /*template <typename T1, typename T2>
        auto myMethod(T1 a, T2 b) -> decltype(a * b)
        {
            return a * b;
        }*/
};


int main(void)
{
    End some1;
    End some2(some1);
    End some3(move(some1));
    
    //cout << some2.myMethod(123);
    
    return 0;
}
