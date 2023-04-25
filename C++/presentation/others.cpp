#include <iostream>
#include <vector>
#include <map>

using namespace std;

using myMap = map<int, int>;
using smallInt = uint8_t;

template <typename N>
using myVector = vector<N>;


constexpr int mySum(int a, int b)
{
    return a + b;
}


enum COLOR 
{
    RED,
    GREEN,
    BLUE
};

enum class SIZE : uint8_t
{
    SMALL,
    MEDIUM,
    BIG
};


int main(void)
{
    COLOR color = RED;
    switch (color)
    {
        case RED: break;
        case GREEN: break;
        case BLUE: break;
    }
    
    SIZE size = SIZE::SMALL;
    switch (size)
    {
        case SIZE::SMALL: break;
        case SIZE::MEDIUM: break;
        case SIZE::BIG: break;
    }
    
    
    myMap example1;
    smallInt example2;
    myVector<int> example3;


    int a;
    cin >> a;
    cout << mySum(1, 2) << endl;
    cout << mySum(a, 4) << endl;

    return 0;
}
