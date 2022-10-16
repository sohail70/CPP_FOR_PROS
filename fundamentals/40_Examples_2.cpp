/*PDF 44
Swap
The example shows a simple swap function that uses the move semantic
internally. MyData doesn’t support move semantics.

Line 7 invokes the copy constructor in line 18.

Lines 8 and 9 invoke the copy assignment operator defined in line 22.

When we invoke move on an only copyable type, copy-semantic will kick
in as fallback to move-semantic. The reason is that an rvalue is first
bound to an rvalue reference and second to a const lvalue reference. The
copy constructor and the copy assignment operator take constant lvalue
references.

*/

#include<algorithm>
#include<iostream>
#include<vector>

template<typename T>
void swap (T& a , T& b)
{
    T tmp(a);
    a = std::move(b);
    b = std::move(tmp);
}

struct MyData{
    std::vector<int> myData;
    MyData():myData({1,2,3,4,5}){}

    //copy semantic
    MyData(const MyData& m):myData(m.myData)
    {
        std::cout<<"Copy Constructor"<<"\n";
    }

    MyData& operator = (const MyData& m)
    {
        myData = m.myData;
        std::cout<<"Copy assignment operator" <<"\n";
        return *this;
    }
};



int main()
{
    MyData a,b;
    swap(a,b);
}