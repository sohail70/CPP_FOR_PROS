/* PDF 180
Problem statement #
Create an std::vector and determine its size and capacity before and after a
call to shrink_to_fit .

! The explanation is pretty straight-forward, as we have initialized an intVec1
! with a size of 5 values. The capacity of the vector is 10. After calling the
! shrink_to_fit function on this vector in line 12, the capacity of the vector
! reduces to 5.
! By using () parenthesis, we declared the size of a vector and by using {}
! curly braces, we inserted a value in the vector.

*/


#include<iostream>
#include<vector>

int main()
{
    std::vector<int> intVec1(5,2011); //2011 2011 2011 2011 2011
    intVec1.reserve(10);
    std::cout<<intVec1.size()<<"\n";
    std::cout<<intVec1.capacity()<<"\n";
    intVec1.shrink_to_fit();
    std::cout<<intVec1.capacity()<<"\n";


    std::vector<int> intVec2(10); // 0 0 0 0 0 0 0 0 0 0
    std::cout<<intVec2.size()<<"\n";
    std::vector<int> intVec3{10};
    std::cout<<intVec3.size()<<"\n";
    std::vector<int> intVec4{5,2011};
    std::cout<<intVec4.size()<<"\n";

}