//Replacing basic data types

#include<iostream>
#include<vector>


int func(int) 
{
    return 2011;
}

int main()
{
    auto i = 5;
    auto& intRef = i; //int& ---> this is the auto type deduction, deduced by the compiler by seeing whats the value stored in it.
    auto* intPoint = &i; //int*
    const auto constInt = i; //const int
    static auto staticInt = 10; //static int

    //Copying a vector and the reference to it using the assignement operator =
    std::vector<int> myVec;
    auto vec = myVec; //std::vector<int>
    auto& vecRef = vec; //std::vector<int>&

    
    int myData[10];
    auto v1 = myData; //int*  
    auto& v2 = myData; //int (&)[10]  //*! What the hell is this?

    auto myFunc = func; //(int)(*)(int)   ---> function pointer
    auto& myFuncRef = func; //(int)(&)(int) --->reference to the function
    
    //Define a function pointer
    int (*myAdd1)(int,int) = [](int a ,int b){return a+b;};

    //Use type inference of the c++11 compiler
    auto myAdd2 = [](int a , int b){return a+b;}; //lambda expression whose return type is inferred by the c++ compiler since we have used the auto keyword

    std::cout<<"\n";

    //use the function pointer
    std::cout<<myAdd1(1,2)<<"\n";
    
    //use the auto variable
    std::cout<<myAdd2(1,2)<<"\n";

}

