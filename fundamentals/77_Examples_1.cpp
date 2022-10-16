/* PDF 76
Restricting operations using delete #

Here, we are prohibiting certain operations by using delete .

In lines 10 to 15, we have restricted the copy operation for
NonCopyableClass objects and references. By assigning delete , we tell the
compiler that the operation will not be accepted. Hence, an error will be
thrown.

With delete , we can also prevent objects from being created on the heap
or stack.

In the TypeOnStack class, we assign delete to the operator new on line 21.This means that an object of this class cannot occupy space on the heap.

Conversely, the TypeOnHeap class is not allowed to make objects on the
stack. We simply define a destructor that calls delete in line 26.

Lastly, there is the onlyDouble() function. We have explicitly told the
compiler to accept only double arguments.

For any other arguments, onlyDouble() will generate an error.

Lines 45 to 51 show various examples of the operations that have been
restricted by delete . None of them will work.



*/

#include<iostream>

class NonCopyableClass
{
public:

    // state the compiler generated deafult constructor
    NonCopyableClass() = default;

    // disallow copying
    NonCopyableClass& operator= (const NonCopyableClass&) = delete;
    NonCopyableClass(const NonCopyableClass&) = delete;

    // disallow copying
    NonCopyableClass& operator =(NonCopyableClass&&) = default;
    NonCopyableClass(NonCopyableClass&&) = default;

};

class TypeOnStack{
public:
    void* operator new(std::size_t) = delete;
};

class TypeOnHeap{
public:
    ~TypeOnHeap() = delete; //Me: Interesting :)
};

void onlyDouble(double){}
template<typename T>
void onlyDouble(T) = delete;


int main()
{
    NonCopyableClass nonCopyableClass;
    
    TypeOnStack typeOnStack;

    TypeOnHeap* typeOnHeap = new TypeOnHeap;

    onlyDouble(3.14);

    // force the compiler error
    NonCopyableClass nonCopyableClass2(nonCopyableClass); // cannot copy

    TypeOnStack* typeOnHeap2 = new TypeOnStack; // cannot create on heap

    TypeOnHeap typeOnStack2; // cannot create on stack

    onlyDouble(2011); // int argument not accepted
}