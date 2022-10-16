


#include<iostream>

/* Basic pointers #
This example shows an instance of two pointers pointing to the same
object.
Since both iptr and jptr point to i , changing the dereferenced value of
jptr in line 18 changes the values of i and iptr as well.
*/

/*
int main()
{
    int i {2011};
    int* iptr = &i;

    std::cout<<i<<" "<<iptr<<" "<<*iptr<<"\n";

    int* jptr = iptr;
    *jptr = 2014;

    std::cout<<iptr<<" "<<*iptr<<"\n";
    std::cout<<jptr<<" "<<*jptr<<"\n";
}
*/
/////////////////////////////////////////////////////////////////////


/* Pointer arithmetic #
As we discussed earlier, arrays use pointer arithmetic.
This can be seen in line 6 where both syntaxes return the same value.

*/

/*
int main()
{
    int intArray[] = {1,2,3,4,5};
    if (intArray[3]== *(intArray+3))
        std::cout<<"Pointer arithmetic works"<<"\n";
}
*/
/////////////////////////////////////////////////////////////////////
/* nullptr
The nullptr can be assigned to any arbitrary pointer, as seen in line 5.
The nullptr cannot be assigned to any arbitrary variable except a bool .
This will only work when creating a bool through uniform initialization,
as seen in line 10.
*/

/*
int main()
{
    int* pi = nullptr;
    std::cout<<pi<<"\n";
    //int i = nullptr; //ERROR
    bool b{nullptr};
    std::cout<<b<<"\n";
}
*/
/////////////////////////////////////////////////////////////////////

/*Function pointers 
In addOne , an integer is passed by reference. Hence, calling the function
will change the actual value of the integer.
inc1 points to the addOne function. Hence, it will have the same
functionality.We do not need to explicitly define the type of the inc2 function pointer.
This is because we use the auto keyword. We’ll study this in more detail
in the near future.
*/

/*
void addOne(int& a)
{
    a+=1;
}

int main()
{
    void (*inc1)(int&) = addOne;
    auto inc2 = addOne;

    int a{10};
    addOne(a);
    std::cout<<a<<"\n";
    inc1(a);
    std::cout<<a<<"\n";
    inc2(a);
    std::cout<<a<<"\n";
}
*/

/////////////////////////////////////////////////////////////////////

/* Pointer to member (member var of a class or struct)
This code is an example of how we can make pointers to the members of
a struct or class.
The pointer for the data member is made in line 11 using the following
syntax:
pointerType structName :: pointerName = &structName :: dataMember
The pointerType must match the type of the dataMember .
The pointer is then dereferenced in lines 18 and 19.
*/

#include<iostream>

struct X{
    int data;
};

int main()
{
    int X::* p = &X::data; //P pointer point to the memeber variable, data.
    
    X object;
    object.data = 2011;
    X* objptr = new X;
    objptr->data = 2014;
    X object2;
    object2.data =3000;

    int k = object.*p; //*! It looks a bit weird: is it like that *p created for every instace of a class?! --> I think you cant use that pointer without an object
    int soso = object2.*p;//*! WEIRD!
    int l = objptr->*p; 
    std::cout<<k<<" "<<l<<" "<<soso<<"\n";
}