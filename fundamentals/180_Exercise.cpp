/* PDF 177
Exercise

Problem statement #
Try to access the index of the array that is greater than the size.
Implement it with the index operator and the at function.

Explanation #
! On line 13, we are trying to access arr[5] which is out of the bounds of the
! array. However, this line will not throw an exception and we would never know if we have accessed an index that is not in the range. On line 20, we
! tried to access the same index using the at function. This function checks if
! the index being accessed is out of bounds or not. Since 5 is greater than the
! size of the array, it throws an exception and terminates the program.


*/



#include<array>
#include<iostream>


int main()
{
    
    std::array<int ,4> arr = {1,2,3,4};

    for (auto a: arr){std::cout<<a<<" ";}

    arr[1] = 1000;
    arr[5] = 5;

    for(auto a:arr){std::cout<<a<<" ";}

    arr.at(0) = 10000;
    arr.at(5) = 5;
}