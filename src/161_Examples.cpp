/* PDF 158
Examples

The key question of the std::unique_ptr is when to delete the underlying resource. This occurs when the
std::unique_ptr goes out of scope or receives a new resource. Let’s look at two use cases to better understand this
concept.

Example 1 #
Explanation #

The class MyInt (lines 7 -17) is a simple wrapper for a number. We have
adjusted the destructor in line 11 - 13 for observing the life cycle of
MyInt .

We create, in line 24, an std::unique_ptr and return, in line 26, the
address of its resource, new MyInt(1998) . Afterward, we move the
uniquePtr1 to uniquePtr2 (line 29). Therefore, uniquePtr2 is the owner of
the resource. That is shown in the output of the program in lines 30 and
31.

In line 37, the local std::unique_ptr reaches its valid range at the end of
the scope. Therefore, the destructor of the localPtr – meaning the
destructor of the resource new MyInt(2003) – will be executed.

! The most interesting lines are lines 42 to 44. First, we assign a new
! resource to the uniquePtr2 . Therefore, the destructor of MyInt(1998) will
! be executed. After the resource in line 43 is released, we can explicitly
! invoke the destructor.

The rest of the program is quite easy to understand. In lines 48 - 58, we
create two std::unique_ptr and swap their resources. std::swap uses
move semantics since std::unique_ptr doesn’t support copy semantics.
With the end of the main function, uniquePtr3 and uniquePtr4 go out of
scope, and their destructors will be automatically executed.
*/


#include<iostream>
#include<memory>
#include<utility>

struct MyInt{
    MyInt(int i ):i_(i){}

    ~MyInt(){
        std::cout<<"Good bye from"<< i_ <<"\n";
    }

    int i_;
};

int main()
{
    std::unique_ptr<MyInt> uniquePtr1 { new MyInt(1998)};

    std::cout<<"uniquePtr1.get "<< uniquePtr1.get()<<"\n";

    std::unique_ptr<MyInt> uniquePtr2;
    uniquePtr2=std::move(uniquePtr1);

    std::cout<<"uniquePtr1.get(): "<< uniquePtr1.get()<<"\n";
    std::cout<<"uniquePtr2.get(): "<<uniquePtr2.get()<<"\n";


    {
        std::unique_ptr<MyInt> localPtr{new MyInt(2003)};
    }

    uniquePtr2.reset(new MyInt(2011));
    MyInt* myInt = uniquePtr2.release();
    delete myInt;

    std::unique_ptr<MyInt> uniquePtr3{new MyInt(2017)};
    std::unique_ptr<MyInt> uniquePtr4{new MyInt{2022}};

    std::cout<<"uniquePtr3.get(): "<<uniquePtr3.get()<<"\n";
    std::cout<<"uniquePtr4.get(): "<<uniquePtr4.get()<<"\n";

    std::swap(uniquePtr3,uniquePtr4);

    std::cout<<"uniquePtr3.get(): "<<uniquePtr3.get()<<"\n";
    std::cout<<"uniquePtr4.get(): "<<uniquePtr4.get()<<"\n";

    




}