/* PDF 158
Example 2 #

std::unique_ptr has a specialization for arrays. The access is transparent,
meaning that if the std::unique_ptr manages the lifetime of an object, the
operators for the object access are overloaded ( operator* and operator-> ). If
std::unique_ptr manages the lifetime of an array, the index operator [] is
overloaded. The invocations of the operators are, therefore, transparently
forwarded to the underlying resource.


We dereference (line 22) an std::unique_ptr and get the value of its
resource.

In lines 7 - 15, MyStruct acts as the base of an array of std::unique_ptr 's.
If we instantiate a MyStruct object, we will get its address. The destructor
gives the output. Now it is easy to observe the life cycle of the objects.

In lines 26 - 28, we create and destroy five instances of MyStruct .

The lines 32 - 36 are more interesting. We create a MyStruct instance on
the heap (line 33) and on the stack (line 34). Therefore, both objects have
addresses from different ranges.

Afterward, we assign the local object to the std::unique_pr (line 35). The
lines 40 - 44 follows a similar strategy. Now we assign the local object, the
first element of myUniqueArray . The index access to the std::unique_ptr
in the lines 35 and 43 feels like familiar to index access to an array.
*/

#include<iomanip>
#include<iostream>
#include<memory>

class MyStruct{
    public:
        MyStruct(){
            std::cout<< std::setw(15)<<std::left << (void*) this <<" Hello "<<"\n";
        }
        ~MyStruct(){
            std::cout<< std::setw(15) <<std::left << (void*) this <<" goodbye " << "\n";
        }
};

int main()
{
    std::unique_ptr<int> uniqInt(new int(2011));
    std::cout<<"*uniqInt" <<*uniqInt<<"\n";

    {
        std::unique_ptr<MyStruct[]> myUniqueArray{new MyStruct[5]};
    }

    {
        std::unique_ptr<MyStruct[]> myUniqueArray{new MyStruct[1]};
        MyStruct myStruct;
        myUniqueArray[0] = myStruct;
    }

    {
        std::unique_ptr<MyStruct[]> myUniqueArray{new MyStruct[1]};
        MyStruct myStruct;
        myStruct = myUniqueArray[0];
    }



}
