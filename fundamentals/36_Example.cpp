/* PDF 41
Rvalue/Lvalue references as arguments #


*/


#include<algorithm>
#include<iostream>
#include<string>

struct MyData{};

std::string function(const MyData &)
{
    return "lvalue reference";
}

std::string function(MyData&&)
{
    return "rvalue reference";
}

int main()
{
    MyData myData;
    std::cout<<function(myData)<<"\n";//myData is an lvalue reference since it has a name and address.
    std::cout<<function(MyData())<<"\n";//MyData() is an rvalue reference since it does not have a name or an address. It is just a call to the default constructor of the struct MyData .
    std::cout<<function(std::move(myData))<<"\n";//std::move(myData) creates an rvalue reference as well since we can neither determine the destination address of myData , nor the destination variable’s name.
}