#include <iostream>
#include <memory>
#include <vector>

using namespace std;


class Factory
{
    
    public:
        
        unique_ptr<int> createSome() { return make_unique<int>(123); /* available in c++14 */ }
        
};


int main(void)
{

    vector<int> data { 1, 4, 56, 675, 675, 8789 };
    for (auto el : data)
        cout << el << endl;


    weak_ptr<int> weak;
    
    {
        Factory factory;
        auto uniq = factory.createSome();
        shared_ptr<int> shar = factory.createSome();
        
        weak = shar;
    }
        
    auto myShar = weak.lock(); // weak.expired();
    if (myShar == nullptr) cout << "weak_ptr is expired";
    else cout << *myShar;
    
    return 0;
}

