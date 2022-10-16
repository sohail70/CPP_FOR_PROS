/* PDF 74
this pointer #

Explanation #
The this pointer is being used in the copy operation on lines 8, 10, and
15.

To check whether the assignee and assigned are the same object, we can
use this . In such a case, we can simply return the dereferenced value of
the this reference to our object.

The class contains two attributes, a and b .

In the newA() method, there is a variable named a . We can differentiate
between the variable and the attribute by using this to access the
attribute, as done on line 21.

Since there isn’t a b variable in the method, this->b and b mean the
same thing (line 24). This is because every member already has an
implicit this pointer.


from the internet:
Do we have to explicitly define a default constructor when we define a copy constructor for a class?? 

! Yes. Once you explicitly declare absolutely any constructor for a class, the compiler stops providing the implicit default constructor. If you still need the default constructor, you have to explicitly declare and define it yourself.

P.S. It is possible to write a copy constructor (or conversion constructor, or any other constructor) that is also default constructor. If your new constructor falls into that category, there's no need to provide an additional default constructor anymore :)



copy assignment operator vs copy constructor
https://www.geeksforgeeks.org/copy-constructor-vs-assignment-operator-in-c/

ME: one of them is constructor and creates the object but the other one doesn't create one but uses an existing object.
! While the copy assignment operator does copy data to another object, the copy constructor initializes a new object with the copied data. 

Base b = base; //calls copy constructor

base b;
b = base; //calls copy-assignment

!BUT
    Base* base4 = new Base();
    Base* base5;
    base5 = base4; //IT dones't call copy-assignment !!!!!! WHY? Ithink !Heap objects don’t naturally support copy semantics in C++ : In this case, data is not copied but both the pointers point to same address.

! Heap objects don’t naturally support copy semantics in C++

Another comment:
Second thing is, that your assignment operator takes argument by value instead of by reference, which causes default copy constructor to create a copy of your MyArray1 before it's passed to assignment operator. This is where the direct source of your problem lays.

good video:
https://www.youtube.com/watch?v=JEImJ7wclMY
*/


#include<iostream>

class Base{
public:
    Base () = default;
    Base(const Base& other)
    {
        std::cout<<"copyassigment"<<"\n";
    }
    Base& operator=(const Base& other)
    {
        if(this == &other)
        {
            std::cout<<"Self assignment"<<"\n";
            return *this;
        }
        else
        {
            std::cout<<"Copy Assignment else"<<"\n";
            a = other.a;
            b = other.b;
            return *this;
        }
    }

    void newA()
    {
        int a {2011};
        std::cout<<this->a<<"\n";
        std::cout<<a<<"\n";
        std::cout<<b<<"\n";
        std::cout<<this->b<<"\n";
    }




    int a{1998};
    int b{2014};
};

int main()
{
    Base base;
    base.newA();

    Base& base2 = base;
    base = base2;
    ////////////////////////////////
    base2.a = 20;
    std::cout<<base.a<<"\n";
    std::cout<<base2.a<<"\n";

    Base base3;
    base3 = base;

    base3.a = 10;
    std::cout<<base.a<<"\n";
    std::cout<<base3.a<<"\n";


    Base* base4 = &base;
    Base* base5{base4};


    base4->a = 100;
    std::cout<<base5->a<<"\n";


    delete base4;
}