/*
Initialize the following containers:
    std::array
    std::vector
    std::set
    std::unordered_multiset
with the {-10, 5, 1, 4, 5} initializer list.

*/

#include<iostream>
#include<array>
#include<set>
#include<vector>
#include<unordered_set>

int main()
{
    std::array<int,5> MyArray = {-10,5,1,4,5};
    for(auto i : MyArray) std::cout<<i<<"\n";
    std::cout<<std::endl;

    std::vector<int> myVector = {-10,5,1,4,5};
    for(auto i : myVector) std::cout<<i<<"\n";
    std::cout<<std::endl;

    //! an std::set of type int is created using the given data.
    //! Integers are inserted in numerical order and duplicate elements, such as
    //! 5 , are not inserted in the set.
    std::set<int> mySet{-10,5,1,4,5} ;
    for(auto i : mySet) std::cout<<i<<"\n";
    std::cout<<std::endl;

    //!The keys are not sorted. Duplicate keys are allowed in a std::unordered_multiset .
    std::unordered_multiset<int> myUnorderedMultiSet = {-10,5,1,4,5};
    for(auto i : myUnorderedMultiSet) std::cout<<i<<"\n";

    
}