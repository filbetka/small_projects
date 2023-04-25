#include <iostream>
#include <string>

using namespace std;


template <typename T>
void templateFunction(T value)
{
    cout << value << endl;
}


template <typename T1, typename T2>
class TemplateClass
{

    private:
    
        T2 content;
    
    public:
    
       TemplateClass(T1 value) {}
       
       void set(T2 value) { content = value; }
       T2 get() { return content; }
    
};


int main(void)
{
    templateFunction("some text");
    templateFunction(123);
    templateFunction(55.12f);
    
    TemplateClass<int, string> myClass(12);
    myClass.set("another text");
    cout << myClass.get() << endl;

    return 0;
}
