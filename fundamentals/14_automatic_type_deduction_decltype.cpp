/*
decltype vs auto

The decltype keyword was also introduced in C++11, though its functionality
differs from auto . 
! decltype is used to determine the type of an expression or entity.
decltype(expression)
! We can use auto to create variables, but decltype returns the type of an expression containing variables.


Rules #
! If the expression is an lvalue, decltype will return a reference to the data type to the expression
! If the expression is an rvalue, decltype will return the data type of the value


decltype is not used as often as auto . It is useful with templates that can
deduce the type of a function.



*/

#include<iostream>

int main()
{
    int i = 1998; //Rvalue
    decltype(i) i2 = 2011; //Same as int i2 = 2011

    //! the parentheses around i indicate that this is an expression instead of a variable. Hence, decltype computes int& instead of int .
    decltype((i)) iRef = i2; // (i) is an lvalue, reference returned

    std::cout<<iRef<<"\n";
    std::cout<<i2<<"\n";

    iRef = 2012;
    std::cout<<iRef<<"\n";
    std::cout<<i2<<"\n"; //iRef is a reference after all
}