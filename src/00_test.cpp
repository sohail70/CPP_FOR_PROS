/*
When we invoke move on an only copyable type, copy-semantic will kick
in as fallback to move-semantic. The reason is that an rvalue is first
bound to an rvalue reference and second to a const lvalue reference. The
copy constructor and the copy assignment operator take constant lvalue
references.
*/
#include<iostream>
#include<algorithm>
#include<vector>

template<typename T>
void swap (T& a , T&b)
{
    T tmp(a); //invokes the copy constructor
    a = std::move(b); //invokes the copy assignment operator .so When we invoke move on an only copyable type, copy-semantic will kick in as fallback to move-semantic
    b = std::move(tmp);//invokes the copy assignment operator. so When we invoke move on an only copyable type, copy-semantic will kick in as fallback to move-semantic
}

struct MyData{ //MyData doesn’t support move semantics. so When we invoke move on an only copyable type, copy-semantic will kick in as fallback to move-semantic
    std::vector<int> myData;
    MyData():myData({1,2,3,4,5}){}

    //copy semantic
    MyData(const MyData& m):myData(m.myData)
    {
        std::cout<<"copy constructor"<<"\n";
    }
    MyData& operator = (const MyData& m)
    {
        myData = m.myData;
        std::cout<<"Copy assignment operator"<<"\n";
        return *this;
    }
};

int main()
{
    MyData a,b;
    swap(a,b);
}