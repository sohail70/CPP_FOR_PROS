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
///DESTRUCTOR
/*
! The purpose of a destructor is to destroy a class object after it goes out of
! scope. This frees up the memory previously occupied by the object.

!Unlike the constructor, a destructor is called automatically.
! Apart from being automatically triggered, an explicit call to delete or
! delete [] triggers the destructor.


! We can define a destructor inside or outside the class. In its body, special
! actions, such as freeing up memory or releasing locks, can be performed.

! A destructor can be declared by the ~ operator followed by the name of
! the class: ~Account()


! We can define a destructor if a class needs an explicit action at object
! destruction. To be more precise, the destructor of the object is invoked when

! the object goes out of scope. Because of this totally deterministic behavior, we
! can release highly critical resources in the destructor.

! Locks or smart pointers in C++ use this characteristic. Both will automatically
! release their underlying resources if they go out of scope.
*/
void func(){
    std::unique_ptr<int> uniqPtr = std::make_unique<int>(2011);
    std::lock_guard<std::mutex> lock(mutex);
    ...
} // automatically released

/*
We can also read this rule the other way around. If all the members of our
class have a default destructor, we should not define our own.
! All resources acquired by a class must be released by the class’s
! destructor. This rule sounds quite obvious and helps us to prevent resource
! leaks. Right? But we have to consider which of our class members have a full
! set of default operations. Now we are once more back to the rule of zero or
! five.
*/
//Maybe the File class has no destructor in contrast to std::ifstream and,
//therefore, we may get a memory leak if instances of MyClass go out of scope.

class MyClass{
    std::ifstream fstream; // may own a file //IN KHODESH DESTRUCTOR DARE
    File* file_;            // may own a file //IN DESTRUCTORESH RO TO BAYAD BENVISI
    ...
};


/*

! If a class has a raw pointer ( T* ) or reference ( T& ), consider whether it
! might be owned. This is a question we have to answer if our class has raw
! pointers or references.

! Who is the owner? If our class is the owner, we have to delete the resource. In
! other words, if a class owns a pointer or reference member, define a
! destructor. In such a case, it’s a good choice to use a smart pointer like
! std::unique_ptr .


! std::unique_ptr is by design as efficient as a raw pointer can be. So we have
! no overhead in time or memory, only added value.



! A base class destructor should be either public and virtual or protected
! and non virtual. This is quite easy to get. If the destructor of the base class is
! protected, we cannot destroy derived objects using a base class pointer;
! therefore, the destructor must not be virtual.

To specifically clarify types (not pointers or references):
! If the destructor of a class, Base , is private, we cannot use the type. If the
! destructor of a class, Base , is protected, we can only derive Derived from Base
! and use Derived.
*/


struct Base{
    protected:
    ~Base() = default;
};

struct Derived: Base{};
int main(){
    Base b;
    // Error: Base::~Base is protected within this context
    Derived d;
}

//Calling Base b will cause an error.

/*
From the internet:
Quite often. If a class is not designed to be inherited, then it doesn't need a virtual destructor and would only end up paying a possibly large overhead for
something it doesn't need. Likewise, even if a class is designed to be inherited but you never delete subtype instances through a base pointer, then it 
also does not require a virtual destructor. In that case, a safe practice is to define a protected nonvirtual destructor
*/
#include<iostream>
struct Base{
    protected:
    ~Base() 
    {
        std::cout<<"base dest"<<"\n";
    }
};

struct Derived: Base
{
    ~Derived()
    {
        std::cout<<"der des"<<"\n";
    }
};
int main(){
    //Base b; // Error: Base::~Base is protected within this context
    
    Base* b = new Base();
    std::cout<<"asdsad"<<"\n";
    //delete b ; //Error 
    
    
    Derived d;
}


//Example
/*
! helloGoodByePtr presents a case where we need to call delete to avoid a
! memory leak from the pointer. As soon as delete is called on line 41, the
! destructor is invoked.
*/

#include<iostream>

class HelloGoodbye{
    public:
        HelloGoodbye(int i): numb(i)
        {
            std::cout<<"Hello from " << numb <<" :"<<"\n";
        }

        ~HelloGoodbye();
    private:
        int numb;
};


HelloGoodbye::~HelloGoodbye()
{
    std::cout<<"Good Bye from: "<<numb<<"\n";
}

void func()
{
    HelloGoodbye helloGoodbye(5); //ijad mishe
}//inja az beyn mire

HelloGoodbye helloGoodbye(1); //in aval az hame ijad mishe va akhar az hame nabod mishe!

int main()
{
    HelloGoodbye helloGoodbye(2);
    std::cout<<"\n";
    HelloGoodbye* helloGoodbyePtr = new HelloGoodbye(3);

    std::cout<<"\n";
    {
        HelloGoodbye helloGoodbye(4); //ijad mishe
    }//haminja az beyn mire

    delete helloGoodbyePtr;
    
    func();

}

/* output

Hello from 1 :
Hello from 2 :

Hello from 3 :

Hello from 4 :
Good Bye from: 4
Good Bye from: 3
Hello from 5 :
Good Bye from: 5
Good Bye from: 2
Good Bye from: 1

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///METHODS
/*
! static methods can be called without an instance as well.

! A class method has to be declared inside the class, but can be defined outside
! using the scope resolution operator, :: .

*/


struct Account
{
    double getBalance() const;
    void withdraw(double amt);
    void deposit (double amt) {balance += amt;}

    private:
        double balance;
}

double Account::getBalance() const{return balance;}
inline void Account::withdraw(double amt){balance -= amt;}
/*
this pointer #
! The this pointer can be used to access the attributes of a class within a
! method. Every attribute has an implicit this pointer. Because of this, we can
! directly access the attribute inside a function. But what would happen if the
! method contains a variable that has the same name as an attribute of the
! class?

! We can easily differentiate between the two by explicitly using this to access
! the attribute. Since this is a pointer, we must use the arrow syntax to access
! members.
*/
struct Base{
    int a{1998}; // Member
    void newA(){
        int a{2011}; // Local variable in the method
        std::cout << this->a; // 1998
        std::cout << a; // 2011
    }
};



/*
static methods #

! Like static attributes, static methods can be used with or without an instance
! of the class. We can define static methods using the static keyword and call
! them using the scope resolution operator, :: .

! Note: Static methods do not have this pointers. They can only access static attributes and methods.
*/
class Account{
    public:
        static int getDeposit(){return deposits;}
    private:
        static int deposits;

};
...
int total = Account::getDeposits();


/*
const methods #

! A constant method cannot modify the object that calls it.

! A method can be declared constant by using the const keyword.

! Constant objects can only call const or constexpr methods.

! Constant methods can only change an instance variable if the instance
! variable is declared mutable .

! Changing the value of balance in getBalance() would cause an error since it
! is a const method. The acc instance has been declared const , but an instance
! does not have to be const to use constant methods.
*/

class Account{
public:
    double getBalance() const {return balance;}
private:
    double balance;
};
...
const Account acc;
double account = acc.getBalance();



/*

constexpr methods # --> dar 0_REVIEW.cpp behtar tozih dadim

! The aim of defining constexpr methods is to improve the performance of our
! code. constexpr methods are executed at compile-time and can later be used
! at runtime without any redundant computations.

! It can also be evaluated at runtime if non- constexpr arguments are provided.
! One thing to remember is that constexpr methods are implicitly const


! Such methods can only call other constexpr functions, methods, and global
! variables.

! constexpr methods can only be called by constexpr objects.


const vs. constexpr #

! const methods are used to increase safety. They restrict modification access
! to the attributes of the class.

! On the other hand, constexpr methods are used to increase performance and
! optimize the program.

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