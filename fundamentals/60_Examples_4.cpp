/*  PDF 61
A generic lambda #


Explanation #

The add lambda on line 7 works solely with int arguments.

We can make it generic by using the auto type, as done on line 8.

Now, any two types that support the + operation with each other will
automatically work in add14 .

Lines 17 and 18 show this generic lambda in action. Floats, integers and
long integers can all be added together. The compiler will decide the
return type of the function.

A generic function is also being used to calculate the cumulative product
of myVec on line 28. There’s nothing tricky going on here.

*/


#include<algorithm>
#include<iostream>
#include<numeric>
#include<string>
#include<vector>

auto add = [](int i , int i2){return i+i2;};
auto add14 = [](auto i , auto i2){return i +i2 ; };

int main()
{
    
    std::cout<<add(2000,11)<<"\n";
    std::cout<<add14(2000,14)<<"\n";
    std::cout<<add14(2000L,14)<<"\n";
    std::cout<<add14(3,0.1415)<<"\n";
    std::cout<<add14(std::string("Hello ") , std::string("World"))<<"\n";

    std::vector<int> myVec {1,2,3,4,5,6,7,8,9};
    auto res = std::accumulate(myVec.begin(), myVec.end() , 1 , [](int i , int i2){return i*i2;});
    std::cout<<res<<"\n";

    auto res14 = std::accumulate(myVec.begin() , myVec.end() , 1 , [](auto i , auto i2){return i*i2;});
    std::cout<<res14<<"\n";

}