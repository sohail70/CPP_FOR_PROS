/* PDF 27
static_cast is the simplest casting operator and is used for simple
conversions.

!It can only perform all the conversions that are well-defined by the compiler. For example, a string to integer cast won’t work.

! It allows bidirectional conversion between related data types such as:
! pointer types in class hierarchies
! integrals and floating-point numbers
! integrals and enumerations

!static_cast cannot be used with polymorphic types.

!Unlike dynamic_cast , a static_cast is performed during compile time.






*/




#include<iostream>


class Account{};
class BankAccount: public Account{};


enum Color{
    red,
    blue,
    green
};



int main()
{
    //we can see how static_cast supports up and down casting between pointers of the same class hierarchy.
    Account* a  = nullptr;
    BankAccount* b = nullptr;
    a = static_cast<Account*>(b); //upcast
    a = b ; //upcast

    b = static_cast<BankAccount*>(a); //downcast
    
    //An integer can be cast into an enum state using static_cast
    int i(2);
    Color col = static_cast<Color>(i);
    std::cout<<i<<"\n";
    std::cout<<col<<"\n";
    //A simple conversion from float to integer
    int i2 = static_cast<int>(3.14);
    std::cout<<i<<"\n";

}