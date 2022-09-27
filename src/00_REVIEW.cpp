///CLASS TYPES
/*
! Classes are data types encapsulating attributes and methods

! A static, or class attribute, is an attribute shared by all instances of a
! class.



! Usually, each object generates its own copy of the class’s attributes, i.e., the
! attributes of one object are independent of the attributes of another.
! This is not true for a static attribute. Only one instance of the attribute is present and shared among all the objects.
! Think of it as a global class variable.

! A static attribute can also be accessed without a class instance because it is
! part of the class, not the individual object. To access it, we can use the scope
! resolution operator, :: .

! Static class attributes can only be initialized outside the class.
*/

class Account{
....
static int deposits;
};
int Account::deposits = 0;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CONSTRUCTORS -->
/*
It can be used to create an instance of the class in the following two ways:

Account acc;
Account *acc = new Account;

! This is very similar to how we declare basic type variables. Well, it turns out
! that all the basic types also call their class constructors!

! the default constructor--> no parameters
...
public:
Account(){
balance = 5000; //! If a default value is not specified, the compiler will assign a value itself.
}
...

! Calling the default constructor invokes the constructors of the base classes
! being used in this class as well.

! Note: The compiler needs the default constructor to automatically create
! instances.


class Account{
public:
Account(); // Constructor
Account(double bal); // Parameterized constructor
...

What would be inside the parameterized constructor?
Let’s have a look:

...
public:
Account(double bal){
balance = bal;
}
...

Account acc(100.0); //creating Account objects on the stack
Account* acc = new Account(100.0); //on heap
Account* accountArray = new Account[10]; // This statement calls the default constructor 10 times because the size of the array is 10 .



empty class takes 1 byte. why? Simply a class without an object requires no space allocated to it. The space is allocated when the class is instantiated, so 1 byte is allocated by the compiler to an object of an empty class for its unique address identification.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MORE CONSTRUCTORS
class Account{
    public:
        Account(const Account& other);//copy constructor: allows a class to create an object by copying an existing object. They expect a constant reference to another instance of the class as their argument.
};



class Account{
    public:
        Account(Account&& other); //move constructor: allows the data of one object to be transferred completely to another object. They expect a non-constant rvalue-reference to an instance of the class as their argument.
        /*
        ! After the move operation, other is in a moved-from state. Accessing it will
        ! result in undefined behavior. To use it again, we would have to re-initialize it.
        */
};




class Account{
    public:
        explicit Account(double b): balance(b){} //! The explicit constructor is used to avoid implicit calls to a class’s constructor.
        Account (double b, std::string c): balance(b), cur(c){}
    private:
        double balance;
        std::string cur;
};

void strange(Account a)
{
    std::cout<<"It works! "<<"\n";
}

Account account = 100.0; // ERROR: implicit conversion --> ye joraee hes mikunam donbale ye rahe ke 100.0 ro tabdil kune be Account age mitune --> in mishe implicit
Account account(100.0); // OK: explicit invocation
Account account = {100.0,"EUR"}; // OK: implicit conversion --> the compiler implicitly calls the constructor that takes a double and a string as an argument
strange(100.0); // Error


//from the internet:
X x;
Y y(x); //explicit conversion

X x;
Y y = x; //implicit conversion//this case is not an assignment, its an initialization, the assignment operator (operator=) is never called; instead a non-explicit one parameter constructor that accepts the type X as a parameter is called.
// ! The difference between initialization and  assignment is important: in the first case a new object is created and it starts its life with the value 
// ! that it is being initializd with(hence why a constructor is called) while assignment happens when an object is assigned (~ coppied) to an object that already exists and already is in a defined state.

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///INITIALIZER LIST FOR INSTANCES
class Account{
public:
    Account (double b): balance(b), minBalance(25.0){} //! One may wonder why this is useful. Well, consider that our class has a const attribute. Naturally, it would have to be initialized. Assigning it values in the constructor’s body will cause an error.
private:
    double balance;
    const double minBalance; //ino faghat besorate bala mitoni init kuni
};

/*
Rules #

! 1. As discussed, non-static attributes that are declared const or as a
! reference must be initialized in the initializer list.
! 2. The sequence of initialization corresponds to the sequence in which the
! attributes were declared.
! 3. static attributes cannot be initialized in the initializer of the
! constructor.
*/
#include <iostream>
#include <string>
class Account{
public:
    Account(double b, std::string& rev):balance(b), reviser(rev), minBalance(25.0){}


//! The commented constructor won’t work since minBalance is a const variable.
//    Account(double b, std::string& rev){
//        balance = b;
//        reviser = rev;
//        minBalance = 25.0;
//    }
private:
    double balance;
    const double minBalance;
    std::string& reviser;
};

//Class members can be directly initialized outside the constructor.
/*
! If class attributes are initialized in both the class body and the initializer list of
! the constructor, the latter has a higher priority.


! Initializing const static attributes, as in line 11, has been a feature since
! C++98.
! C++11 adds support for several other types such as int , string , and
! vector .
*/
class MyClass{
    const static int oldX = 5; // C++98
    int newX = 5; // C++11
    vector<int> myVec{1, 2, 3, 4, 5}; // C++11
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CONSTRUCTOR DELEGATION
/*
! Constructor delegation occurs when a constructor calls another
! constructor of the same class in its initializer list
*/
struct Account{
    Account(): Account(0.0){}
    Account (double b): balance(b){}
};
/*
Rules #
! When the constructor call in the initializer list is completed, the object is
! created. This object can then be altered in the calling constructor’s body.

! It is important to perform constructor delegation in the initializer list. If it
! is called in the body, a new class object will be created and we will end up with two objects, which is not the behavior we want.

! Recursively invoking constructors will result in undefined behavior.

! The aim of delegation is to let one constructor handle initialization. That
! object can be used or modified by all other constructors. In other words,
! constructors can delegate the task of object creation to other constructors.



! A great advantage of constructor delegation is that the initialization code is
! localized. Once that code has been tested, the rest of the code can be built
! upon it robustly. Also, bugs, if there are any, will be localized to the specific
! constructor(s) instead of being spread around all over the place.
*/
#include<cmath>
#include<iostream>

class MyHour
{
    public:
        MyHour(int hour)
        {
            if( 0 <= hour && hour <=23) myHour=hour;
            else myHour = 0;
            std::cout<<myHour<<"\n";
        }
        
        MyHour():MyHour(0){}

        MyHour(double hour):MyHour(static_cast<int>(ceil(hour))){}

    private:
        int myHour;

};
int main()
{
    MyHour(10);
    MyHour(100);
    MyHour();
    MyHour(22.45);
}


/*
Recursion 
Let’s implement a struct in which constructors call themselves recursively.
What will happen?
*/

struct C {
    C( int ) { }                //1: non-delegating constructor
    C(): C(42) { }              //2: delegates to 1
    C( char c ) : C(42.0) { }   //3: ill-formed due to recursion with 4
    C( double d ) : C('a') { }  //4: ill-formed due to recursion with 3
};
int main(){
    C(1);
    C();
    C('a'); //miofte to loop binahayat
    C(3.5);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////