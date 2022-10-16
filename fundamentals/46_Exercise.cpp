/*
Exercise #
Use the perfect factory method in the code below and make a variadic
template to use it with different types.


The three dots in line 9 ( std::forward<Args>(args)... ) cause each
constructor call to perform perfect forwarding. The result is impressive.

Now, we can invoke the perfect factory method with the number of
arguments we want, as seen in lines 15, 22, and 27.
*/


#include<iostream>
#include<string>
#include<utility>
#include<vector>
#include<initializer_list>

template<typename T , typename ... Arg>
T create(Arg&& ... arg)
{
    return T(std::forward<Arg>(arg) ...);
}

int main()
{
    int lValue = create<int>(1);
    int i = create<int>(lValue);
    std::cout<<lValue<<"\n";
    
    std::cout<<i<<"\n";

    std::string s = create<std::string>("Testing");
    std::cout<<s<<"\n";

    typedef std::vector<int> IntVec;
    IntVec intVec = create<IntVec>(std::initializer_list<int>({1,2,3,4,5}));
    for (auto i = intVec.begin() ; i != intVec.end() ; ++i)
        std::cout<<*i<<"\n";
}