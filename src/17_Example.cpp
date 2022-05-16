/* PDF 22

example of how decltype can be used to automatically deduce the return type of a function



*/
#include<iostream>
#include<typeinfo>

template<typename T1 , typename T2>
auto add(T1 first , T2 second) ->decltype(first+second)
{
    return first+second;
}

/* For c++14
template<typename T1 , typename T2>
auto add(T1 first , T2 second) 
{
    return first+second;
}
*/
int main()
{

    std::cout<<add(1,1)<<"\n";
    std::cout<<typeid(add(1,1)).name()<<"\n"; //returns a string representation of the return type.

    std::cout<<add(1,2.1)<<"\n";
    std::cout<<typeid(add(1,2.1)).name()<<"\n";


    std::cout<<add(1000LL,5)<<"\n";
    std::cout<<typeid(add(1000LL,5)).name()<<"\n";


}