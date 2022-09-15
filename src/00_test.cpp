#include<iostream>
#include<typeinfo>

template<typename T1 , typename T2>
auto add(T1 first , T2 second) 
{
    return first+second;
}


int main()
{
    std::cout<<typeid(add(false,false)).name()<<"\n";
}