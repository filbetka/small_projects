#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int x()
{
    vector<int> data { 0, 5, -3, 11, -3, 7, 0, 2, 7, -6, 11, 0, 21, 12, -5};

    auto found = find_if (data.begin(), data.end(),
        [](int n) { return 0 < n && n < 10; });
        
    cout << "First found value is: " << *found;        
    cout << endl;

    for_each (data.begin(), data.end(),
        [](int n) { cout << n % 3 << " "; });

    int abc = 123;

    auto myLambda = [abc](int n) { return abc < n && n < 10; }
    auto value = myLambda(12);

    return myLambda;
}

int main()
{
    auto lam = x();
    lam(555);
    return 0;
}
