#include<iostream>

constexpr int addOne(int i)
{
    return i+1;
}


int main()
{
    constexpr int j = addOne(1);

    constexpr int k =10;
    std::cout<<addOne(k)<<"\n";
    std::cout<<"\n";
}