/* PDF 81
Exercise #
! Adjust the following program so that all implicit conversions are possible.
! Does the program behave as expected?

Explanation #
! Recall that the explicit keyword is solely responsible for preventing
! implicit conversions.

! Hence, the trick is to simply remove explicit from the conversion
! constructor and operator. This will enable implicit conversions again.



from the internet:
good video to watch
https://www.youtube.com/watch?v=M2D11HXlgnE

*/

class A{};

class B{};


class MyClass{
    public:
        MyClass(){}
        MyClass (A){}
        operator B(){return B();}

};

void needMyClass(MyClass){};
void needB(B){};

struct MyBool{
    operator bool(){return true;}
};


int main()
{
    // A -> MyClass
    A a;

    // explicit invocation

    MyClass myClass1(a);

    // implicit conversion from A to MyClass
    MyClass myClass2 = a;
    needMyClass(a);


    // MyClass -> B

    MyClass myC1;

    //explicit invocation

    B b1(myC1); //! ME: This is weird a little bit because it seems that its calling the B class constructor but its not(I think!) but if you think about it this way --> B b1 = myC1 --> now its not weird but note that the latter is implicit conversion

    //implicit conversion from MyClass to B
    B b2 = myC1;
    needB(myC1);

    // MyBool -> bool conversion
    MyBool myBool;
    if (myBool){};
    int myNumber = (myBool)? 1998 : 2011;

    //implicit conversion
    int myNewNumber = myBool + myNumber ; 
    auto myten = (20 * myBool - 10 * myBool) / myBool;
}