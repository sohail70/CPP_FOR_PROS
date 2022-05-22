/* PDF 61
Examples

this binding #

Explanation #
! This is an example of how the this binding works with lambdas.
! this binds all the members of a class to the lambda. It is very similar to
! the = binding.

*/

#include <iostream>

class ClassMember
{
    const static int a = 1;
    int get10()
    {
        return 10;
    }

    public:
        void showAll()
        {
            //define and invoke (trailing() ) the lambda functions
            [this]{std::cout<<"by this = "<<get10()+a<<std::endl;}();
            [&]{std::cout<<"by reference = "<<get10()+a <<std::endl;}();
            [=]{std::cout<<"by copy = "<<get10() + a <<std::endl;}();
        }
};

int main()
{
    ClassMember cM;
    cM.showAll();
    
}