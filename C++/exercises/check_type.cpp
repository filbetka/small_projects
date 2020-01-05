#include <vector>
using std::vector;

template<typename T>
class DT;

template<typename T>
auto f(const T& param)
{
    DT<T> T_type;
    DT<decltype(param)> param_type;
}

auto make_vector()
{
    return vector<int>{4, 2, 5, 6, 8};
}

int main()
{
    const auto vec = make_vector();
    DT<decltype(vec)> vec_type;
    f(&vec[0]);
    f(vec[0]);
    
    return 0;
}
