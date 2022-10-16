/* PDF 189
The properties of keys and values are listed below.

There are special rules for the key and the value of an ordered associative
container.

The key has to be
! sortable (by default, they are sorted in ascending order)
! copyable and moveable

The value has to be
! default constructible
! copyable and moveable

The key associated with the value builds a pair p so that we get a member
with p.first and the value with p.second .


*/

#include<iostream>
#include<map>

int main()
{
    std::multimap<char, int> multiMap = {{'a',10},{'a',20},{'b',30}};
    for(auto p: multiMap) std::cout<< "{" << p.first << "," <<p.second<<"} ";   // {a,10},{a,20},{b,30}
    std::cout<<"\n";
    return 0;
}