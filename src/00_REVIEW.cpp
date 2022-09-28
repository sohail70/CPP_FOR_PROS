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
/*

from the internet:
Do we have to explicitly define a default constructor when we define a copy constructor for a class?? 

! Yes. Once you explicitly declare absolutely any constructor for a class, the compiler stops providing the implicit default constructor. 
! If you still need the default constructor, you have to explicitly declare and define it yourself.

P.S. It is possible to write a copy constructor (or conversion constructor, or any other constructor) that is also default constructor.
If your new constructor falls into that category, there's no need to provide an additional default constructor anymore :)

*/




/*

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

*/


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


///Example --> static methods
#include<iostream>


class Account{
    public:
        Account(){deposits++;} //Whenever the constructor is called, the static value deposits is incremented by 1 .

        static int getDeposits() //static method
        {
            return Account::deposits;
        }
    
    private:
        static int deposits; //static attribute
};
int Account::deposits = 0;

int main()
{
    std::cout<<Account::getDeposits()<<"\n"; //bedone obj ham mishe static attribute ro call kard

    Account acc1;
    Account acc2;

    std::cout<<acc1.getDeposits()<<"\n";
    std::cout<<acc2.getDeposits()<<"\n";
    std::cout<<Account::getDeposits()<<"\n";
}


///Example --> this pointer
#include<iostream>

class Base{
    public:
        Base& operator= (const Base& other){
            if(this==&other) //check kunim bebinim ke self-assignment nadashte bashim 
            {
                std::cout<<"self-assignment"<<std::endl;
                return *this; // dereferenced value of the this reference to our object. --> this ke pointer hast va vaghti dereference mishe mishe khode object
            }
            else
            {
                a = other.a;
                b = other.b;
                return *this;
            }
        }

        void newA()
        {
            int a{2011};
            std::cout<<"this->a: "<<this->a<<std::endl; //1998 
            std::cout<<"a: " <<a<<std::endl; //2011 ---> in ba this->a fargh dare --> //! a is variable but this->a is an attribute
            std::cout<<"b: "<<b<<std::endl; //2014 --> Since there isn’t a b variable in the method, this->b and b mean the same thing //! This is because every member already has an implicit this pointer.
            std::cout<<"this->b: "<<this->b <<std::endl; //2014 
        }

    private:
        int a{1998};
        int b{2014};

};  

int main()
{
    Base base;
    base.newA();


    Base& base2 = base;
    base = base2;

}

///constant methods
#include<iostream>

class Account{
    public:
        double getBalance() const{return balance;} //faghat value ro return mikune
        void addAmount(double amount){balance+=amount;}
    private:
        double balance{0.0};
};

int main()
{
    Account readWriteAccount;
    readWriteAccount.addAmount(50.0);
    std::cout<<readWriteAccount.getBalance()<<"\n";

    const Account readAccount; //! const object can only call const methods ---> age addAmount ro bahash seda bezani error mide
    std::cout<<readAccount.getBalance()<<"\n";
}


///constexpr methods
#include<iostream>

class Account{
    public:
        constexpr Account(int amou): amount(amou){}
/*
The constexpr constructor, and the methods getAccountFees and
getAmount will be evaluated at compile time.
*/
        constexpr double getAmount() const{ //! Since constexpr methods are implicitly const , we mention the const keyword in the definitions as well.
            return amount;
        }
        constexpr double getAccountFees() const
        {
            return 0.5*getAmount();
        }

    private:
        double amount;
};

int main()
{
    constexpr Account accConst(15);
    constexpr double amouConst = accConst.getAmount(); //! shows how the returned value of getAmount() can be stored in a constexpr double .
    static_assert(amouConst==15,"not compile time calculation");

    Account accDyn(15);
    double amouDyn = accDyn.getAmount(); //! constexpr methods can also be called by non- constexpr objects.
    //static_assert(amouDyn==15)
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// REQUEST AND SUPPRESS METHODS
/*
Since C++11, there has been a list of special methods that the compiler can
generate implicitly if we have not defined them:
! Default constructors and destructors.
! Copy/move constructors and copy/move assignment operators.
! new and delete operators for objects and C arrays of objects.
! The default and delete keywords can be used to guide the creation or suppression of these special methods.
! default can only be assigned to special methods that do not have any default arguments. Hence, it wouldn’t work with something like an ordinary class method or a parameterized constructor.



! Let’s suppose we have a parameterized constructor for our Account class but
! no default constructor. The compiler can easily generate it for us. All we need
! to do is assign default to the default constructor.

*/

...
Account() = default; 
Account (double balance){this->balance = balance;} //chun in constructor ro neveshti dg compiler be sorate automatic default constructor ijad nemikune (bekhatere rule 0 3 and 5 which states that when you define any constructor you have to define them all or just 3 of them and compiler doesnt use its imlicit constructor anymore) -->ama age khate bala ro benvisi = default ijad mikune
...



/*

Request methods: default #
The compiler generates the request methods when it has the following
characteristics:
! public access rights and are not virtual.

! The copy constructor and copy assignment operator get constant lvalue
! references.

! The move constructor and move assignment operator get non-constant
! rvalue references.

! The methods are not declared explicit and possess no exception
! specifications.



Suppress methods: delete #

! By using delete , we can define purely declaratively that an automatically
! generated method from the compiler is not available.

! We can simply tell the compiler what to do without explaining how to do
! it.

! By using delete in combination with default , we can define whether or
! not a class’s objects:
    ! can be copied.
    ! can only be created on the stack.
    ! can only be created on the heap.

! Apart from objects and pointers, delete is also applicable to functions.

*/

/* nokte hashieee:
 SomeType sometype() vs SomeType sometype; ---> avali function prototype hast va dovomi default constructor SomeType ro seda mizane baraye ijade object
 alabte deghat kun SomeType() mishe ijad object ---> SomeType sometype = SomeType();
*/


//Example
#include<iostream>

class SomeType{
    public:

    //state the compiler to generate default constructor
    SomeType() = default;

    //constructor for int
    SomeType(int value) //chun ino ijad kardi compiler dg constructor haye dg ro besorate implicit ijad nemikune pas to khodet ijad kun va default bezar ta compiler befahme ke bayad ijad kune
    {
        std::cout<<"SomeType(int)"<<"\n";
    }

    // Explicit copy constructor
    explicit SomeType(const SomeType&) = default;  //The explicit keyword is used in the copy constructor to avoid implicit conversions during copying.

    //virtual destructor
    virtual ~SomeType() = default; //We need the virtual destructor in case there is a derived class inheriting SomeType .
};


int main()
{
    SomeType someType;
    SomeType someType2(2);
    SomeType someType3(someType2); //ME: you can also use {} 
}


// Example: Restricting operations using delete 

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
void onlyDouble(T) = delete; // hame ro rad mikune ama chun do khat balatar double ro neveshtim faghat ono ghabool mikune


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


// Exercise Define a class template that can be invoked with an int value.

//My first solution was wrong which was like this:

/*
template<typename T>
class OnlyInt{
public:
    OnlyInt(int a){}
    OnlyInt(T) = delete;
};

int main()
{
    OnlyInt(5); // ok
    OnlyInt(5L); // ERROR
}

*/

//The solution:
#include<iostream>


class OnlyInt{
public:
    OnlyInt(int){}
    template<typename T>
    OnlyInt(T) = delete;
};

int main()
{
    OnlyInt(5); // ok
    OnlyInt(5L); // ERROR
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///OPERATOR OVERLOADING
struct Account{
    Account& operator += (double b)
    {
        balance += b;
        return *this;
    }

    double balance;
};
int main()
{
    Account a;
    a+=100;
    std::cout<<a.balance<<"\n";
}

/*
! We have already encountered function overloading. If the function is inside a
! class, it must be declared as a friend and all its arguments must be provided.

Rules #
We cannot change the precedence of an operator.
! Derived classes inherit all the operators of their base classes except the assignment operator. Each class needs to overload the = operator.
! All operators other than the function call operator cannot have default arguments.

! Operators can be called explicitly. A benefit of overloading an operator
! is that it can be used directly with its operands. However, the compiler
! may cause some implicit conversion in this process. We can make explicit
! calls to the overloaded operator in the following format: a.operator +=
! (b) .
*/


#include<iostream>

class Account{

public:
    explicit Account(double b):balance(b){}

    Account& operator += (double b)
    {
        balance += b;
        return *this; //Me: return the updated version of the object
    }

    friend Account& operator+=(Account& a , Account& b);
    friend std::ostream& operator <<(std::ostream& os , const Account& a);

private:
    double balance;
};


Account& operator += (Account& a , Account& b)
{
    a.balance += b.balance;
    return a;
}

std::ostream& operator<< (std::ostream& os , const Account& a)
{
    os<<a.balance;
    return os;
}

int main()
{
    Account acc1(100.0);
    Account acc2(100.0);
    Account acc3(100.0);

    acc1 += 50.0;
    acc1 += acc1;

    acc2 += 50.0;
    acc2 += acc2;

    acc3.operator+= (50.0); //the explicit operator call works when the argument is a double --> yani += e avali call mishe
    //acc3.operator+= (acc3); //Error --> chun in dare az += e avali estefade mikune ke double be onvan vorodi ghabool mikune

    std::cout<<acc1<<"\n";
    std::cout<<acc2<<"\n";
}


/*

The following operators cannot be overloaded:
!    .
!    ::
!    ?:
!    sizeof
!    .*
!    typeof

*/


/*

Assignment operators #

! We can overload the assignment operator by implementing it as a copy or
! move assignment operator. It has to be implemented in a class method. The
! implementation is very similar to a copy or move constructor.

! If the assignment operator is not overloaded, the compiler creates one
! implicitly. This operator performs a member-wise assignment of all the values
! from the object to be assigned. This is very similar to the behavior of the copy
! constructor, except that instead of a new object being created, the members of
! an existing object are updated.

*/
/*

In this example, the assignment operator for the Account class is
overloaded for both copy (line 16) and move (line 27) operations.

! If the argument is an lvalue, a copy is performed. A new array on the
! heap is created, called deposits , and the contents of other 's array is
! copied into it, as seen in lines 18 and 19.

! If the argument is an rvalue, a move is performed. In this case, a new
! array is not created. This makes the move operation much faster.

This is evident in the main program.

! The std::move call on line 53 returns an rvalue, hence the assignment
! operator will move the data from account2 to account .

This is significantly more efficient than the copy assignment on line 48.
*/

#include<algorithm>
#include<chrono>
#include<iomanip>
#include<iostream>


class Account{

public:
    Account() = default;
    Account(int numb): numberOf(numb), deposits(new double[numb]){}

    Account(const Account& other): numberOf(other.numberOf),deposits(new double [other.numberOf])
    {
        std::copy(other.deposits , other.deposits + other.numberOf , deposits);
    }

    Account& operator = (const Account& other)
    {
        numberOf = other.numberOf;
        deposits = new double [other.numberOf]; //ME: Now that you've allocated a memory you should copy the content by using the std::copy
        std::copy(other.deposits , other.deposits + other.numberOf , deposits);
        return *this;
    }

    Account(Account&& other): numberOf(other.numberOf) , deposits(other.deposits) //ME: when its && it means its ready to move
    {
        other.deposits = nullptr; //ME: After you moved you must make it null because this is move semantics
        other.numberOf = 0;
    }

    Account& operator = (Account&& other)
    {
        numberOf = other.numberOf;
        deposits = other.deposits;
        other.deposits = nullptr;
        other.numberOf = 0;
        return *this;
    }

private:
    int numberOf;
    double* deposits;

};

int main()
{
    std::cout<<std::fixed<<std::setprecision(10);

    Account account(200000000);
    Account account2(100000000);

    auto start = std::chrono::system_clock::now();
    
    account = account2;
    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout<<"Account& operator = (const Account& other): "<<dur.count()<<"\n";

    start = std::chrono::system_clock::now();
    account = std::move(account2);
    dur = std::chrono::system_clock::now() - start;
    std::cout<<"Account& operator=(Account&& other): "<<dur.count()<<"\n";
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///EXPLICIT CONVERSION OPERATORS
/*
In C++98, the explicit keyword was only supported for conversion
constructors. Conversion operators converted user-defined objects implicitly.

All this changed in C++11. Now, we can overload conversion operators to
explicitly prevent and permit conversions.

Let’s suppose that a class called MyClass can perform conversions from class
A to MyClass and from MyClass to class B .
see the picture in PDF 80

class MyClass{
public:
    explicit MyClass(A){}   // C++98
    explicit operator B(){} // C++11
};

MyClass(A) : Converting constructor
operatorB() : Converting operator


! As we can see, the explicit keyword can now be used when overloading the
! conversion operator, B() .


! One thing to keep in mind is that implicit conversions to bool are still
! possible, so be careful.

*/

class MyBool{

public:
    explicit operator bool(){return true;}

};
...
MyBool myB;
if(myB){};
int a = (myB)? 3:4;
int b = myB + a; //Error
/*
! We have defined that a MyBool object can be converted to bool but not to
! anything else.

! Because of this, int b = myB + a; causes an error, since it is trying to
! implicitly convert myB to int .
*/


//Example

#include<iostream>

class A{};

class B{};

class MyClass{
public:
    MyClass(){}
    explicit MyClass(A){}       // since C++98
    explicit operator B(){return B();} //new with c++11 //return nadarae conversion operator --> az tarafi bade operator bayad esme on class e ke mikhay behesh convert kuni yani B() ro benvisi

};

void needMyClass(MyClass){}; //aya type A ro mishe biarim too? no chun tabdil type A be MyClass nadarim ---> age explicit ro az oon constructor bala bardarim mishe implicit in etefagh biofte //! dar kol ta oon jaee ke man fahmidam implicit yani bezor khodesho shabih on samte tasavi bokone hala inkaro ba constructor mitone anjam bede
void needB(B){};

struct MyBool{
    explicit operator bool(){return true;}
};

int main()
{
    // A -> MyClass
    A a;

    // Explicit invocation
    MyClass myClass1(a);
    
    // imlicit conversion from A to MyClass --> chun oon bala neveshti explicit in javab nemide 
    MyClass myClass2 = a; //inja bayad bezoor a ro convert kune be MyClass (yani implicit) ke nemitoone chun constructor explicit hast
    needMyClass(a); //inja ham mikhad implicitly a ro tabdil kune be MyClass ke constructor explicit hast va ejaze nemide

    //MyClass -> B
    MyClass myC1;

    //Explicit  invocation --> //! in nemidonam chera javab nemide?!!!
    B b1(myC1); //dar vaghe tabdil type MyClass be B hast ke operator oveloadesh ro dar class gozashtim
    //implicit conversion from MyClass to B ---> explicit hast conversion operator  dar class va nemizare
    B b2 = myC1;
    needB(myC1);

    // MyBool -> bool conversion
    MyBool myBool;
    if(myBool){};
    int myNumber = (myBool)? 1998 :2011; //! IMPORTANT--> implicit conversion dar vaghe dare inja rokh mide ke myBool ke az jense class MyBool hast ro mikhaym be bool tabdil kunim ke ba tavajoh be overload ee ke kardim dar oon struct khoroji mishe true.
    //implicit conversion
    int myNewNumber = myBool + myNumber; //!javab nemide chun dar struct bala explicit kardim conversion operator ro
    auto myTen = (20*myBool - 10 *myBool) / myBool;
}
/*
! We have defined an explicit conversion constructor from A to MyClass in
! line 10.

! The constructor call works fine in line 27, but the implicit conversions in
! lines 29 and 30 are rejected by the compiler.

! needMyClass(a) will not be able to implicitly convert a to MyClass . This
! functionality has been available since C++98.

! We have defined an explicit conversion operator from MyClass to B in
! line 11.

! Lines 38 and 39 use an implicit conversion. Due to the explicit conversion
! operator B in line 11, this is not valid.

! Because of this explicit definition, implicit conversions through the
! operator are rejected by the compiler, as seen in lines 46 and 47.The explicit conversion feature was introduced in C++11.
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