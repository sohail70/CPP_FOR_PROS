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
///FUNCTION OBJECTS - CALL OPERATOR
/*

! By overloading the function call operator, () , we can call objects like
! ordinary function objects that may or may not have arguments. These special
! objects are known as function objects or, wrongly, as functors.
! The best feature of function objects is that they can have a state. Since they
! are objects, data is stored inside them, but they can also be used as functions
! to return data.

Functors #
! Functors are very similar to lambda functions. We can say that lambdas
! actually create anonymous functors.

! Because of this, functors are used frequently in STL algorithms as arguments.
! These functors can then be applied to the data being passed to the STL
! functions.

! std::add , std::transform , and std::reduce are just a few of the functions that
! can use functors and apply them to data.

! A functor that takes a single argument is a unary functor.
! A functor that takes two arguments is a binary functor.
Note: Lambda functions can also have a state. ---> dar mesale dovomi mibini ke int sum mishe state e lambda
*/

#include<algorithm>
#include<iostream>
#include<vector>


class SumMe{
    public:
        SumMe():sum(0){};
        void operator()(int x)
        {
            sum+=x;
        }

        int getSum()
        {
            return sum;
        }
    private:
        int sum;
};

int main()
{
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};
    SumMe sumMe = std::for_each(vec.begin(),vec.end(),SumMe()); //elemets of vec go to SumMe as an int and sum member variable gets updated one by one --> sum is the state of the function object
    std::cout<<sumMe.getSum();
}
/*
The std::for_each call in line 27 is a special algorithm of the Standard
Template Library.

It can return its callable. We invoke std::for_each with the function
object SumMe and can, therefore, store the result of the function call
directly in the function object.
*/

///Example above without function object and just by using lambda:
#include <algorithm>
#include <iostream>
#include <vector>

//! &sum Stores the address of last updated value of sum .
int main(){
    std::cout << std::endl;
    std::vector<int> intVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Use a lambda function here and class sumMe is no longer needed
    /*
        With C++14, the so-called initialization capture of lambdas is supported.
        sum{0} declares and initializes a variable of type int which is only valid
        in the scope of the lambda function.
    */
    int sum {0}; //! the variable sum represents the state of the lambda function.
    std::for_each(intVec.begin(), intVec.end(), [&sum](int x) {sum+=x;}); //! ME: if you use sum instead of &sum you must use mutable keyword before lambda body--> reason: First, the type of a lambda expression, which has capture, is a class type (5.1.2 Lambda expressions [expr.prim.lambda] #3) That type has an operator() which is by default const, unless mutable is used in the lambda expression ([expr.prim.lambda] #5) -->source:https://stackoverflow.com/questions/13699515/copied-const-object-in-lambda-closure-not-mutable -->note that the result is not right if you don't use &sum because for_each function ignores the return value of the lambda body as its stated in the for_each function
    //! use this too: https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11  -->  The generated operator() is const by default, with the implication that captures will be const when you access them by default. This has the effect that each call with the same input would produce the same result, however you can mark the lambda as mutable to request that the operator() that is produced is not const.
    //! check this site for reasons: https://www.cplusplus.com/forum/general/279685/
    std::cout << "sum: " << sum << std::endl;
    std::cout << std::endl;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ACCESS RIGHTS FOR MEMBERS
/*
! The access rights of members determine how the members are accessible
! from outside of the class. Access rights give the author of the class the ability
! to decide which class members are accessible to the users of the class, i.e., the
! interface and which members are for internal use of the class (the
! implementation.) C++ has three different access rights:

! public : No restriction.
! protected : Access from inside the class and from all derived classes.
! private : Access only from within the class.

! The name of every class member has an associated member access. When
! the name of the member is used anywhere in a program, its access is checked,
! and if it does not satisfy the access rules, then the program does not compile.

Rules #
! 1. All members of a class are private by default.
! 2. All members of a struct or union are public by default.
! 3. Access rights are determined by the last used access specifier.
! 4. The access specifier can be used multiple times.

! The public and protected members are the interfaces of the class, the
! private members are the implementations of the class.


Embedded declarations #
! All entities of a class are visible inside the class. The scope operator( :: ) must
! be used from outside the class to access the elements of the class.
*/

struct Account{
    enum Status{Ok m Error};
    void setStatus(Status s);
...
};

Account* acc = new Account;
acc->setStatus(Account::Status::Ok);


///Example
#include<iostream>

class Account{
public:
    Account(double b): balance(b){
        ++Account::transactions; //vase access be member haye class mishe az :: estefade kard garche fek nakunam niazi bashe
    }

    void deposits(double amt)
    {
        balance = calcBalance(amt);
    }

    void withdraw(double amt)
    {
        balance = calcBalance(-amt);
    }

    double getBalance() const{
        return balance;
    }

    static int transactions;
private:
    double calcBalance(double amt) //az in fun faghat dar khode class dare use mishe pas private bashe behtare
    {
        ++Account::transactions;
        return balance +=amt;
    }
    double balance;
};
int Account::transactions = 0;



int main()
{
    Account acc(100.0);
    acc.deposits(50.0);
    acc.deposits(25.15);
    acc.withdraw(30);

    std::cout<<acc.getBalance()<<"\n";
    std::cout<<Account::transactions<<"\n"; //vase access be memeber static niazi be object nist va mishe ba :: access kuni
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FREIND DECLARATIONS
/*
! The friend declaration appears in a class body and grants a function or
! another class access to private and protected members of the class where the
! friend declaration appears. Friends have access to all members of a class.

! A class can declare friendship to a function, a method, or a class.

Rules: #
! 1. The declaration of a friendship can be anywhere.
! 2. The access specifier of the friendship declaration is not relevant.
! 3. Friendship cannot be inherited (your friend’s children are not your
! friends).
! 4. Friendship is not transitive (a friend of your friend is not your friend).


! Access specifiers have no effect on the meaning of friend declarations (they
! can appear in private: or in public: sections, with no differences).

! A friend has full control of the internals of a class.

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///STRUCTS AND UNIONS
/*
STRUCTS --> user-defined data type that allows us to combine data items of
different kinds.

! Structs are almost identical to classes. The default access specifier for a struct
! is public instead of private .

! The default inheritance specifier is public instead of private .

! Structs should be used instead of classes if the data type is a simple data
! holder.
*/
struct Person{
    int age;
    int size;
    int weight;
    std::string name;
};


/*
UNIONS --> special data type where all members start at the same address. A
union can only hold one type at a time, therefore, we can save memory. A
tagged union is a union that keeps track of its types. By using union, we are
actually pointing to the same memory for the different data types used.

Rules #
Unions are special class types.
! Only one member can exist at any one point in time.
! They only need as much space as the biggest member requires, which saves memory.
! The access specifier is public by default.
! They cannot have virtual methods like with Inheritance.
! They cannot have references.
! They cannot be inherited nor inherited from.
*/

#include<iostream>

union Value{
    int i ;
    double d;
};


int main()
{
    Value v = {123}; //now v holds an int
    std::cout<<v.i<<"\n"; //write 123
    v.d = 987.654; //now v holds a double
    std::cout<<v.d<<"\n"; //write 987.654
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ABSTRACT BASE CLASSES AND INHERITANCE

/*
INHERITANCE--> 
! When one class inherits from another class, it gets all its attributes and  members from the parent class.
! The inherited classes use the attributes and methods from the parent class and can add new ones.

! Polymorphism: when the characteristics of an object behave differently at run time.
*/

/*
Abstract base classes #

An abstract class is a class that has at least one pure virtual function. A pure virtual function (virtual void function() = 0 ) is a function that must be implemented by a derived class if that class should not be abstract.
Only for completeness reasons. An abstract class can provide implementations of pure virtual functions. A derived class can, therefore, use these implementations.

Interfaces should usually consist of public pure virtual functions and a default/empty virtual destructor (virtual ~My_interface() = default).  If you don't follow the rule, something bad may happen.

! These are classes that have at least one pure virtual method. By declaring a
! method virtual and adding = 0 to the method declaration, we can make a
! method pure virtual.

! Abstract Base Classes are typically used as interfaces for class hierarchies
! because they determine the implementation of the derived classes.



Rules #
! 1. A class that has a pure virtual method cannot be instantiated.
! 2. A derived class has to implement the pure virtual method in order to get instantiated.
! 3. A pure virtual method can be implemented in a class.
! 4. We must implement a pure virtual destructor. Idiom in C++ is used to declare an abstract base class.
*/
class Account{
    public:
        virtual double estimateReturn() = 0;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ACCESS RIGHTS OF INHERITANCE
/*
! A class can be derived public , protected , or private from its base class.
! For classes, the default access right is private ; for structs, it’s public . SO class BankAcc: Acc{...} is the same as class BankAcc: private Acc{...}


Is-a relations: public, protected, private
! The derived class and the base class have an is-a relationship. Public
inheritance is called an is-a relationship because the derived class has the
same interface as the base class. The derived class is a specialization of the
base class.


public #
class BankAccount: public Account{ ...

! public and protected members in the Account class are public and protected in the BankAccount class.


protected #
class BankAccount: protected Account{ ...

! public and protected members in the Account class are protected in the BankAccount class.


private #
class BankAccount: private Account{ ...

! public and protected members in the Account class are private in the BankAccount.
*/
//ye mesal az khodam
#include<iostream>

class A{
    public:
        int a;
    private:
        int b;
    protected:
        int c;
};


class B: protected A
{
    public:
        int d;
        void show()
        {
        }
    private:
        int e;
    protected:
        int f;
        //int c; //c va a mian to protected class B
        //int a;
};


class C: public B
{
    public:
        int g;
        //int d;
    private:
        int h;
    protected:
        int i;
        //int f
        //int c
        //int a;
};

int main()
{
    B b;
    b.a =10; //nemishe be a dastrasi dasht chun shode protected member class B
}

///Example --> inheritance
/*
The public member functions of the Account class are available to the
BankAccount class and we can access them using the . operator (line 46).
*/
#include<iostream>

class Account{
    public:
        Account(double b): balance(b){}

        void deposit(double amt){
            balance+=amt;
        }

        void withdraw(double amt){
            balance -= amt;
        }

        double getBalance() const{
            return balance;
        }

    private:
        double balance;
};

class BankAccount : public Account{
    public:
        BankAccount(double b): Account(b){}

        void addInterest()
        {
            deposit(getBalance()*0.05);
        }
};

int main()
{
    BankAccount bankAcc(100.0);
    bankAcc.deposit(50.0);
    bankAcc.deposit(25.15);
    bankAcc.withdraw(30);
    bankAcc.addInterest();

    std::cout<<bankAcc.getBalance()<<"\n";

}



///Abstract base class inheritance #
#include<iostream>

class Abstract{
    public:
        virtual ~Abstract() = 0; //! We have created a pure virtual class Abstract and we cannot make an instance of this class as it will give an error.
};

Abstract::~Abstract(){};

class Concrete: public Abstract{};


class HumanBeing{
    public:
        HumanBeing(const std::string n): name(n)
        {
            std::cout<<name<<" created. "<<"\n";
        }

        virtual std::string getSex() const = 0; //! getSex is pure virtual so we cannot make an instance of HumanBeing in main .
    private:
        std::string name;
};

class Man: public HumanBeing{
    public:
        Man(const std::string n): HumanBeing(n){};

        std::string getSex() const{ //! The instances of the Man and Woman classes can access the getSex function by using the . operator and they must be overridden in derived classes.
            return "Male";
        }
        
};  

class Woman: public HumanBeing{
    public:
        Woman(const std::string n): HumanBeing(n){};

        std::string getSex() const{
            return "Female";
        }
};

int main()
{
    //Abstract abstract;//ERROR chun abstract hast
    Concrete concrete;

    //HumanBeing humanBeing("soheil");//ERROR chun abstract hast

    Man soheil("soheil");
    Woman katy("katy");

    std::cout<<soheil.getSex()<<"\n";
    std::cout<<katy.getSex()<<"\n";
}


///access right in inheritance

class Account{
    public:
        int pub{0};
    protected:
        int prot{0};
    private:
        int pri{0};
};


class PubAccount : public Account{
    public:
        PubAccount(){
            pub + prot; // public + protected
        }

};

class ProtAccount: protected Account{
    public:
        ProtAccount(){
            pub + prot; // protected + protected
        }
};

class PriAccount: private Account{
    public:
        PriAccount(){
            pub + prot; //private + private
        }
};
int main()
{
    PubAccount pubAccount;
    ProtAccount proAccount;
    PriAccount priAccount;
}



/*
A class hierarchy is constructed to represent a set of hierarchically organized
concepts (only). Typically, base classes act as interfaces. There are two major
uses for hierarchies, often named implementation inheritance and interface
inheritance.

Read the class hierarchy rules in the given links:
! SOME VERY GOOD LINKS IN THE PDF. CHECK IT OUT.
! The explnation in core c++ guidlines may be hard so you can use this website : https://www.modernescpp.com/index.php/c-core-guidelines-class-hierarchies which explains the core guidlines better.

! Another good explanation: https://www.quantstart.com/articles/C-Virtual-Destructors-How-to-Avoid-Memory-Leaks/

! Best example is this: https://ladydebug.com/blog/2020/11/23/valgrind-testing-of-non-virtual-destructor/
*/

#include<iostream>
#include<string>
#include<memory>

class Goof{
    public:
        virtual void printName() const = 0;
        ~ Goof() //! delete the virtual word and see the leak- derived destructor won't be called so string s destructor can't be called //but valrgind can't catch that - maybe its just undefined beahvior--> check: https://stackoverflow.com/questions/56792856/why-absence-of-a-virtual-destructor-doesnt-cause-a-memory-leak BUT ITHINK THIS IS A BETTER EXAMPLE:https://ladydebug.com/blog/2020/11/23/valgrind-testing-of-non-virtual-destructor/
        {
            std::cout<<"Goof Destructor"<<"\n";
        }
};

class Derived: public Goof
{
    public:
        Derived(std::string name): s(name){};
        void printName() const override
        {
            std::cout<<s<<"\n";
        }

        ~Derived(){
            std::cout<<"Derived Destructor"<<"\n";
        }
    private:
        std::string s; //! khodam: class string khodesh destructor dare ke az tarigh destructor class derived trigger mishe fek kunam
};  

int main()
{
    Goof* p {new Derived{"Here we go"}};
    p->printName();
    delete p;

    std::cout<<"bsdf"<<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// CONSTRUCTOR INHERITANCE
/*
! When we call a constructor, a series of constructor calls may be triggered.
! This guarantees that each base object is properly initialized. The sequence of
! constructor calls starts with the base class and ends with the most derived
! class.

struct A{};
struct B: A{};
struct C: B{};
C c;    // A -> B -> C



Inheriting base class constructors:
! Only the default constructor is inherited, the copy and move constructor
! will not be inherited.

! The derived class inherits all the characteristics of the constructors:
!       public , protected , and private access specifiers.
!       explicit and constexpr declarations.
Default arguments for parameters of the constructor of a base class will not be
inherited.
! The derived class gets an additional constructor, having one parameter for the
! default argument. Constructors with the same parameters as constructors in
! the derived class will not be inherited.

! By inheriting constructors from the base class, there is the danger of
! forgetting to initialize the attributes of the derived class.
*/
class Account
{
    public:
        Account(double amount{});
};


class BankAccount: public Account{
    public:
        using Account::Account;
};
BankAccount bankAccount(100.0);




///Example Constructor inheriting
/*
! For integers and strings, it called the Base class constructors and for doubles, it calls the Derived class constructor.
*/
#include<iostream>
#include<string>

class Base{
    public:
        Base() = default; //! ME: comment this and see what happens --> I think when you don't have feault constructor and when you instantiate the derived class constructor can't create base class constructor implicitly (because you have another constructor in base class). the point is you have to instantiate base c oconstructor in dervied constructor or else you have to have default constructor or you don't have anything at all so that compiler do that for you impliicitly
        Base(int i ){
            std::cout << "Base::Base("<< i << ")" << std::endl;
        }
        Base(std::string s){
            std::cout << "Base::Base("<< s << ")" << std::endl;
        }
};


class Derived: public Base
{
    public:
        using Base::Base;
        Derived(double d)//! inja besorate implicit default constructor Base ro seda mizane
        {
            std::cout << "Derived::Derived("<< d << ")" << std::endl;
        }
};

int main()
{
    // inheriting Base
    Derived(2011); // Base::Base(2011)

    // inheriting Base 
    Derived("C++0x"); //Base::Base(C++0x)

    // using Derived
    Derived(0.33); //Derived::Derived(0.33)
}

///Example
/*
Inherit public , protected , and private identifiers from a class using
constructor inheritance. The constructors inherited from the base class keep
their access level. The inherited class restricts them.
What does that mean for the inherited constructors?
*/
class Base{
    public:
        Base(int){};
};
class DerivePublic: public Base{
    using Base::Base;
};
class DeriveProtected: protected Base{
    using Base::Base;
};
class DerivePrivate: private Base{
    using Base::Base;
};
int main(){
    Base(1);
    DerivePublic(1);
    DeriveProtected(1);
    DerivePrivate(1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///BASE CLASS INITIALIZER
/*
! When a base class has no default constructor, the derived class must explicitly
! call a constructor. The base class initializer is typically used with class
! initializers.
*/
class Account{
    public:
        Account(double amount, std::string cur){};
};

class BankAccount: public Account{
    public:
        BankAccount(double r , std::string cur): Account(r, cur){}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///DESTRUCTOR CALLS
/*
! When we (directly or indirectly) call a destructor, a series of destructor calls may be triggered.

! This guarantees that each base object is properly destructed.

! The sequence of destructor calls starts with the most derived class and
! ends with the base class.

! We might have noticed that constructor calls follow the exact opposite
! behavior of destructor calls.
*/
struct A{};
struct B: A{};
struct C: B{};
C* c = new C; // A -> B -> C
delete c;     // ~c -> ~A -> ~A

/*
Exercise #
Which initialization order of the attributes of a class is guaranteed?
The order of their declaration or the invocation order in the constructor.
Discuss the consequences of each possibility.
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///VIRTUAL METHODS
/*
! Virtual methods are used to adjust the behavior of an object while
! keeping its interface stable.

! In order to override a method, it must be declared virtual .

! For documentation purposes, the overriding method will also be declared as
! virtual .
*/

struct Account{
    virtual void withdraw(double amt){balance -= amt;}
}
...

struct BankAccount: Account{
    virtual void withdraw(double amt){
        if((balance - amt) > 0.0 ) balance -= amt;
...



/*
! The dynamic type of the object determines which version of a virtual method
! will be called. To apply virtuality, a pointer or a reference is needed.
*/


BankAccount bankAccount(100.0);
Account* aPtr = &bankAccount;
aPtr -> withdraw(50.0);
Account& aRef = bankAccount;
aRef.withdraw(50.0);



/* 
Polymorphic: #
! The method is selected at run-time.
! This is often called dynamic or late binding.


Rules: #
! Constructor must not be virtual.
! Virtual methods do not have to be overridden.
! Methods declared as virtual stay virtual in the hierarchy.
! The parameters in the overridden method must be identical to the parameters in the virtual method.
! The specifier virtual is required to obtain polymorphic behavior.
! Private methods can be overridden in the base class.

! There’s a difference between overriding and overloading.

Virtual destructors #
! When destructing an object via a pointer or a reference to a base class, the
! destructors must be virtual.
*/
Account* aptr;
Account* aptr = new BankAccount(100.0);
delete aptr;
Account& aRef = BankAccount(200.0);



///Example:
#include<iostream>


class Account{
    public:
        Account(double amt):balance(amt){}

        virtual void withdraw(double amt){
            balance-=amt;
        }

        double getBalance() const
        {
            return balance;
        }
    protected:
        double balance;
};


class BankAccount: public Account{
    public:
        BankAccount(double amt):Account(amt){}

        virtual void withdraw(double amt) override
        {   
            if(balance>amt)    balance-=amt;
        }
};  

/*
! We can access the withdraw function of the BankAccount class using three
! approaches

Reference to the derived class from the base class
Assigning a pointer of the base class to the newly created object using new keyword of the derived class
Using the reference of the base class, we can point to the derived class object. 

*/
//Kolan method haye bank account call mishe chun dynamic object male bank account hast harchand ke  be type Account assign esh karde bashim
int main()
{
    BankAccount bankAccount(100.0);
    Account* aPtr = &bankAccount; //pointer to stack (which is useless I suppose and its for demonstration purpose )
    
    aPtr->withdraw(50);
    std::cout<<aPtr->getBalance()<<"\n";

    BankAccount* bankAccount2 = new BankAccount(100.0);
    Account* aPtr2 = bankAccount2;
    aPtr2->withdraw(50);
    std::cout<<aPtr2->getBalance()<<"\n";

    BankAccount bankAccount3(100.0);
    Account& aRef = bankAccount3;
    aRef.withdraw(50);
    std::cout<<aRef.getBalance()<<"\n";
}



/*

When a virtual method is invoked through a pointer or a reference to an
object, late binding occurs.

Answer the following questions.

Which phenomena happens with early binding? khodam: static binding happens at compile time  in contrary to the late binding which happens at runtime  ---> static binding is faster than late binding
What’s the name of the phenomena?
Why do we have early binding in C++?



! dar kol late binding ba virtual func ha faghat ba pointer va reference mitone anjam beshe na ba dot operator
! ba early binding (compile time binding )  polymorphic beahviour nadarim
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///OVERRIDE AND FINAL
/*
override:

reason ---> a common bug present in object hierarchies:  methods that should override methods of base classes but do not.
! The compiler verifies if the override annotated method actually overrides a
! virtual method of a base class.

! The compiler checks for
    ! The parameters and the return type.
    ! The constness of the method.
    ! The virtuality of the method.



final #
! final is the right tool for the job if a virtual method should not be
! overridden.

! final supports two use cases. First, we can declare a method that cannot be
! overridden; second, we can define a class that cannot be derived from. The
! compiler uses the same rules to determine if a method of child class overrides
! a method of a base class. Of course, the strategy is inverted because the final
! specifier should disallow the overriding of a method. Therefore, the compiler
! checks the parameters of the method, its return type, and any const/volatile
! qualifiers.


! A virtual method declared final must not be overridden.

The compiler checks for:
! The parameter.
! The return type.
! The constness of the method.
! Methods and classes declared as final are an optimization
! opportunity for the compiler.
! Both variants are equivalent:
void func() final;
virtual void func() final override;
*/



/*
A good question that I came accros:
https://stackoverflow.com/questions/11477523/when-and-why-to-declare-member-variables-on-the-heap-c
*/

///! EXAMPLE ---> This example is important because it's confusing! --> albate oonghadrha ham confusing nist chun be method haye private fagaht az tarig methode 
///! public mitonim dastrasi peyda kunimvali khob on baksh ke mishe private virtual func haro override kard ye khorde confusing hast.
/*
C++ has access control, but not visibility control. This means that private functions are visible but not accessible. A private virtual function can be overridden by derived classes, but can only be called from within the base class. This is actually a useful construct when you want that effect.
https://root.cern/TaligentDocs/TaligentOnline/DocumentRoot/1.0/Docs/books/WM/WM_132.html#:~:text=C%2B%2B%20has%20access%20control%2C%20but,from%20within%20the%20base%20class.

*/
#include<iostream>

class Sort{
    public://!a public virtual method processData in the Sort class which calls the three private methods.
        virtual void processData()
        {
            readData();
            sortData();
            writeData();
        }
    
    private: //!three private virtual methods 
        virtual void readData(){}
        virtual void sortData() = 0;
        virtual void writeData(){}

};


class QuickSort: public Sort
{
    private: //! We have overridden the methods of the Sort class in QuickSort .
        void readData()
        {
            std::cout<<"readData"<<"\n";
        }

        void sortData()
        {
            std::cout<<"sortData"<<"\n";
        }

        void writeData()
        {
            std::cout<<"writeData";
        }
};


int main()
{
    Sort* sort = new QuickSort;
    sort->processData();

}




///Example ---> override  
class Base{
    void func1();
    virtual void func2(float);
    virtual void func3() const;
    virtual long func4(int);

    virtual void f();
};


class Derived: public Base{
    // ill-formed: no virtual method func1 exists
    virtual void func1() override; //!ERROR

    // ill-formed: bad type
    virtual void func2(double ) override;//!ERROR

    // ill-formed: const missing
    virtual void func3() override;//!ERROR

    // ill-formed: wrong return type
    virtual int func4(int) override;//!ERROR

    // well-formed: f override base::f
    virtual void f() override;
};

int main()
{
    Base base;
    Derived derived;
}


///EXAMPLE ---> final 
class Base{
    virtual void h(int) final;

    virtual void g(long int);
};


class Derived: public Base{

    // ill-formed: base method declared final
    virtual void h(int); //!ERROR

    // well-formed: a new virtual function
    virtual void h(double);

    virtual void g(long int ) final; //inja eshkali nadare ke override shode vali chun dg final kardim dg class paeentar dg nemitone overrideehs kune
};

class DerivedDerived: public Derived{
    virtual void g(long int); //!ERROR
};

struct FinalClass final{};
struct DerivedClass: FinalClass{}; //!ERROR

int main()
{
    Base base;
    Derived derived;
    DerivedDerived derivedDerived;

    FinalClass finalClass;
    DerivedClass derivedClass;
}

///Exercise ----> class hierarchy in template method design pattern --> reason : http://www.gotw.ca/publications/mill18.htm
/*

!ME: interesting question: https://stackoverflow.com/questions/2170688/private-virtual-method-in-c
! Herb Sutter has very nicely explained it here.

! Guideline #2: Prefer to make virtual functions private.

! This lets the derived classes override the function to customize the behavior as needed, without further exposing the virtual functions directly by making them callable by derived classes (as would be possible if the functions were just protected). The point is that virtual functions exist to allow customization; unless they also need to be invoked directly from within derived classes' code, there's no need to ever make them anything but private

! Another opposing answer!!!--> (Opposed to Herb Sutter quoted by Prasoon Saurav in his answer, the C++ FAQ Lite recommends against private virtuals, mostly because it often confuses people.)--> https://isocpp.org/wiki/faq/strange-inheritance#private-virtuals

*/
#include<iostream>


class Sort{

    public:
        Sort(){}

        virtual void processData()
        {
            readData();
            sortData();
            writeData();
        }
    private:
        virtual void readData() {}
        virtual void sortData() = 0;
        virtual void writeData(){};
    
};


class QuickSort: public Sort{
    private:
        void readData() override
        {
            std::cout<<"readData"<<"\n";
        }
        void sortData() override
        {
            std::cout<<"sortData"<<"\n";
        }

        void writeData()
        {
            std::cout<<"writeData"<<"\n";
        }
};

class BubbleSort: public Sort{
    private:
        void sortData() override
        {
            std::cout<<"sortData \n";
        }
};

int main()
{    
    Sort* sort = new QuickSort;
    sort->processData();
    delete sort;

    Sort* sort2 = new BubbleSort;
    sort2->processData();
    delete sort2;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MULTIPLE INHERITANCE
/*
Multiple inheritance is a feature of some object-oriented computer
programming languages in which an object or class can inherit characteristics
and features from more than one parent object or class. It is different from
single inheritance, where an object or class may only inherit from one
particular object or class.

General rules of multiple inheritance #

! By providing a list of base classes will result in multiple inheritance.

! Multiple inheritance is a generalization of single inheritance.
! The access rights for each base class can be specified individually.

! For classes, access rights are private by default; for structs, access rights
! are public by default .

! If a derived class has more than one instance of a base class, the invocation of
! its members is ambiguous.

Diamond-problem #
! The diamond problem is an ambiguity that arises when two classes B and C
! inherit from A , and class D inherits from both B and C . If there is a method
! in A that B and C have overridden, and D does not override it, then 
! whichversion of the method does D inherit: that of B , or that of C ?

It is called the “diamond problem” because of the shape of the class
inheritance diagram in this situation. Class A is at the top, both B and C are
separately beneath it, and D joins the two together at the bottom to form a
diamond shape.


! Ambiguous calls to members can be resolved by using the scope
! operator.

Virtual base class #
! A virtual base class solves the problem of multiple inheritance because the
! derived class gets only one base class. When a class is derived virtually from a
! base class it becomes a virtual base class.

!ME: A single copy of its data members is shared by all the base classes that use virtual base.
*/

///Example 1
#include<iostream>

class Account{
    public:
        Account(double amt): amount(amt){}

        double getBalance() const{
            return amount;
        }

        private:
            double amount;
};


class BankAccount: public Account{
    public:
        BankAccount(double amt): Account(amt) {}
};  

class WireAccount: public Account{
    public:
        WireAccount(double amt): Account(amt) {}
};

class CheckingAccount: public BankAccount, public WireAccount //This class has access to the getBalance methods of both classes.
{
    public:
        CheckingAccount(double amt): BankAccount(amt), WireAccount(amt){} //! Khodam: alan har kodum az az ina ke initilize beshe , har kodom ye bar Account(amt) ro ejra mikunan ke in baes mishe do bar in kar anjam begire
};

int main()
{
    CheckingAccount checkingAccount(100.0);
    checkingAccount.getBalance(); //!ERROR---> ambiguous function
    /*
    If we try to call the getBalance method using the instance of
    CheckingAccount class, it will give us an error, but if we call it with the
    name of the base class along with the scope operator :: then it works
    fine.
    */
    std::cout<<checkingAccount.BankAccount::getBalance()<<"\n";
    std::cout<<checkingAccount.WireAccount::getBalance()<<"\n";
}


///Example 2: Virtual multiple inheritance
/*
we have created all the classes in the same way as
in example 1.

The only thing that we have changed is virtually inheriting the Account
class in the BankAccount and WireAccount classes.

By inheriting these classes virtually, we can now access the
checkAccount.getBalance() method of the Account class.
*/
#include<iostream>

class Account{
    public:
        Account(double amt): amount(amt){}

        double getBalance() const{
            return amount;
        }

        private:
            double amount;
};


class BankAccount: virtual public Account{ //!vaghti virtual mizari yani ye done double amount ijad beshe kafie dar heyn process of inheritance
    public:
        BankAccount(double amt): Account(amt) {}
};  

class WireAccount: virtual public Account{
    public:
        WireAccount(double amt): Account(amt) {}
};

class CheckingAccount: public BankAccount, public WireAccount
{
    public:
        CheckingAccount(double amt): BankAccount(amt), WireAccount(amt),Account(amt){} //! Account(amt) is added also --> c++ rule ---> initialization of the base virtual class is the responsibility of the most derived class so it needs to initialize amount --> data vaghe do ta class balan initailization eshon ignore mishe!
};

int main()
{
    CheckingAccount checkingAccount(100.0);
    checkingAccount.getBalance(); 

    std::cout<<checkingAccount.BankAccount::getBalance()<<"\n";
    std::cout<<checkingAccount.WireAccount::getBalance()<<"\n";
}

/* tozihate khoob:
https://www.youtube.com/watch?v=7APovvvftQs&ab_channel=BoQian
Tl;dr entehaye video---> alan age class Account,BankAccount,WireAccount pure abstract class bodand va implementation nadashtan onvaght  dg moshkele duplication o in chizhayee ke dar multiple inheritance hast dg nabood va niazi be virtual inheritance nist
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////