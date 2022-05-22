/* PDF 61 
Examples:

Closure with lambdas #

Explanation #
This is a great example of how variables from the environment can be
accessed in a lambda.

! The copy variable is captured as a copy. Hence, its value is simply copied
! and bound to the lambda.

! In line 11, when the value of copy is altered to "changed" , the change
! isn’t reflected in the lambda() call. This is because lambda() is bound to
! the original value of copy .

! For ref , there is the opposite effect, since it is captured as a reference. A
! change in its value on line 12 is reflected in lambda() as well.




*/


#include<iostream>
#include<string>


int main()
{
    std::string copy = "original";
    std::string ref = "original";

    auto lambda = [copy , &ref]{std::cout<<copy<<" "<<ref<<"\n";};
    lambda();
    copy = "changed";
    ref = "changed";

    lambda();
    std::cout<<"\n";


}