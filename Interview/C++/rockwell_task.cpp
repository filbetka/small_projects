#include <iostream>
#include <vector>
#include <cassert>
#include <map>
#include <ordered_map>

using namespace std;
vector<int> foo(vector<int> numbers, unsigned k);


void test_foo_biggest_value()
{
    auto result = foo({1,1,1,2,3,4,5}, 1);
    assert(result.size() == 1);
    assert(result[0] == 1);
    
    result = foo({1,2,3,4,4,4,5}, 1);
    assert(result.size() == 1);
    assert(result[0] == 4);
    
    result = foo({1,2,3,4,5}, 1);
    assert(result.size() == 1);
    assert(result[0] == 1);
}
void test_foo_biggest_value_negative()
{
    auto result = foo({-1,-1,-1,-2,-3,-4,-5}, 1);
    assert(result.size() == 1);
    assert(result[0] == -1);
    
    result = foo({-1,-1,-1,-2,-3,-4,-5}, 1);
    assert(result.size() == 1);
    assert(result[0] == -4);
    
    result = foo({-1,-2,-3,-4,-5}, 1);
    assert(result.size() == 1);
    assert(result[0] == -1);
    
    result = foo({-1,2,-3,4,-5}, 1);
    assert(result.size() == 1);
    assert(result[0] == -1);
}
void test_foo_three_values()
{
    auto result = foo({1,1,1,2,3,4,5}, 3);
    assert(result.size() == 3);
    assert(result[0] == 1);
    assert(result[1] == 2);
    assert(result[2] == 3);
}
void test_foo_empty()
{
    auto result = foo({}, 1);
    assert(result.size() == 0);
    
    result = foo({}, 3);
    assert(result.size() == 0);
    
    result = foo({}, 0);
    assert(result.size() == 0);
}


// napisane rozwiązanie
vector<int> foo(vector<int> numbers, unsigned k)
{
    map<int, int> counter;
    vector<int> result;
    
    for (auto number : numbers) 
    {
        counter[number] += 1;
    }
    
    for (int i = 0; i < k; ++i)
    {
        int biggest = 0;
        int biggest_key = -1;
        for (const auto& [key, value] : counter)
        {
            if (biggest < value)
            {
                biggest = value;
                biggest_key = key;
            }
        }
        
        if (biggest_key == -1)
            break;
        
        counter.erase(biggest_key);
        result.push_back(biggest_key);
    }
    
    return result;
}

// poprawne rozwiązanie
vector<int> foo(vector<int> numbers, unsigned k)
{
    ordered_map<int, int> counter; // listy hashujące
    vector<pair<int, int>> data;
    vector<int> result;
    
    // count repetitions
    for (auto number : numbers)
        ++counter[number];
    
    // convert to vector
    for (auto value : counter)
        data.push_back(value);
    
    // sort data
    sort(data.begin(), data.end(), 
        [](const auto& p1, const auto& p2) {
            return p1.second > p2.second; 
        }
    );
    
    // copy biggest values to result
    for (int i = 0; i < k; ++i)
    {
        if (i < data.size())
            result.push_back(data[i].first)
            
        else break;
    }
    
    return result;
}


int main()
{
    test_foo_biggest_value();
    //test_foo_biggest_value_negative();
    test_foo_three_values();
    test_foo_empty();
    return 0;
}
