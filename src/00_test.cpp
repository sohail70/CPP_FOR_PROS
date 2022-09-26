#include<functional>
#include<iostream>
std::function<int(int)> makeLambda(int a)
{
    return [a](int b){return a+b;};
}

int main()
{
    auto lam = makeLambda(2); //makeLmabda(2) creates a lambda expression that captures a which is, in this case, is 2
    std::cout<<lam(4);
}