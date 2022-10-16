/* PDF 96
Example: Constructor inheriting #

Explanation #
! In this example, we have created two classes, i.e., Base and Derived . The
! Derived class inherits the Base class publicly. When we call the Derived class
! object with the keyword using , it calls the relative constructors. This can be
! clearly seen in the objects created in the main section. For integers and
! strings, it called the Base class constructors and for doubles, it calls the
! Derived class constructor.

*/

#include<iostream>
#include<string>

class Base{
    public:
        Base() = default; //! ME: comment this and see what happens --> I think when you don't have feault constructor and when you instantiate the derived class constructor can't create base class constructor implicitly (because you have another constructor in base class). the point is you have to instantiate base c oconstructor in dervied constructor or else you have to have default constructor or you don't have anything at all so that compiler do that for you impliicitly
        Base(int i ){
            std::cout << "Base::Base("<< i << ")" << std::endl;
        }
        Base(std::string s){
            std::cout << "Base::Base("<< s << ")" << std::endl;
        }
};


class Derived: public Base
{
    public:
        using Base::Base;
        Derived(double d)
        {
            std::cout << "Derived::Derived("<< d << ")" << std::endl;
        }
};

int main()
{
    // inheriting Base
    Derived(2011); // Base::Base(2011)

    // inheriting Base 
    Derived("C++0x"); //Base::Base(C++0x)

    // using Derived
    Derived(0.33); //Derived::Derived(0.33)
}