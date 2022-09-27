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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////