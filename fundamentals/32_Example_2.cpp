/*PDF 37
Auto

The difference between ordinary functions and constexpr functions in
C++14 is minimal. Therefore, it’s quite easy to implement the gcd
algorithm in C++14 as a constexpr function.

We have defined res as a constexpr variable and its type is
automatically determined by auto . However, res2 is not constexpr .
*/

#include<iostream>

constexpr int gcd(int a , int b)
{
    while(b != 0 )
    {
        auto t = b;
        b = a % b;
        a = t;
    }
    return a;
}


int main()
{
    constexpr auto res = gcd(100,10);
    std::cout<<res<<"\n";

    auto val = 100;
    auto res2 = gcd(val,10);
    std::cout<<res2<<"\n";
}


