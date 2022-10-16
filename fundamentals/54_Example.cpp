/* PDF 58
Default arguments #

Explanation #
This is a perfect example of how default arguments work in C++.

Since the arguments are read from left to right, the function calls in lines11 to 13 will apply the argument to the temp parameter.

The other two parameters receive their default arguments.

In line 17, a second argument is provided, which will replace the default
value of low .

In the function call in line 18, all the arguments are provided. Hence,
none of the default arguments are used.
*/



#include<iostream>

bool isTempOK(const int temp , const int low = 20 , const int high = 50)
{
    return (low<temp) && (temp<high);
}

int main()
{
    std::cout<<std::boolalpha<<std::endl;

    std::cout<<isTempOK(20)<<"\n";
    std::cout<<isTempOK(30)<<"\n";
    std::cout<<isTempOK(50)<<"\n";

    std::cout<<isTempOK(30,30)<<"\n";
    std::cout<<isTempOK(50,30,100)<<"\n";
}