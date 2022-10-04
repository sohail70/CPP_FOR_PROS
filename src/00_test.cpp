#include<iostream>
#include<set>
#include<array>


int main()
{
        std::multiset<int> mySet{3,1,5,3,4,5,1,4,4,3,2,2,7,6,4,3,6};
        auto a = mySet.lower_bound(5);
}