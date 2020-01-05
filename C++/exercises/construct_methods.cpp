#include <iostream>
#include <memory>
using namespace std;


class Animal
{
    
    public:
    
        virtual ~Animal() = default;
    
};

class Fish : public Animal
{

    public:
    
        explicit Fish(int number): Fish("", number)
        {
        }
    
        Fish(string value, int number): Animal()
        {
            cout << "Fish::params: " 
                 << value << " "
                 << number << endl;
        }
        
};

class Bird : public Animal
{

    public:
    
        explicit Bird(int number): Bird("", number)
        {
        }
    
        Bird(string value, int number): Animal()
        {
            cout << "Bird::params: " 
                 << value << " "
                 << number << endl;
        }
        
};


class Factory
{
    
    public:
    
        template<class T, typename... Ts>
        auto Make(Ts&&... params)
        {
            unique_ptr<Animal> animal;
            animal.reset(new T(forward<Ts>(params)...));
            return animal;
        }
    
        template<typename T>
        void Log(T&& data)
        {
            this->Log_Implement(
                data,
                is_integral<remove_reference_t<T>>()
            );
        }
    
    private:
    
        template<typename T>
        void Log_Implement(T&& data, true_type)
        {
            double row = data;
            cout << row << endl;
        }
    
        template<typename T>
        void Log_Implement(T&& data, false_type)
        {
            static_assert(
                is_constructible<string, T>::value,
                "Parameter has to be string type or similary!"
            );
            
            string row = forward<T>(data);
            cout << row << endl;
        }
    
};

void func(Fish)
{}

int main()
{
    Factory factory;
    auto fish = factory.Make<Fish>(123);
    auto bird = factory.Make<Bird>("oh..", 321);
    
    factory.Log("");
    factory.Log("First");
    factory.Log(123);
    //factory.Log(fish);
 
    //func(3);
    func({"", 5});
    return 0;
}
