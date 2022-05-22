/* PDF 66
More kinds of constructors

Copy constructors #
! The copy constructor allows a class to create an object by copying an
! existing object.

! They expect a constant reference to another instance of the class as their
! argument.

class Account{
    public:
        Account(const Account& other);
};

! All the values of other can be copied into the new object. Both objects will
! have the same values afterward.

Move constructors #
! The move constructor allows the data of one object to be transferred
! completely to another object.

! They are a more efficient alternative to the copy constructor since everything
! is being moved instead of copied.

! They expect a non-constant rvalue-reference to an instance of the class as
! their argument.

class Account{
    public:
        Account(Account&& other);
};

! After the move operation, other is in a moved-from state. Accessing it will
! result in undefined behavior. To use it again, we would have to re-initialize it.


Explicit constructors #

! The explicit constructor is used to avoid implicit calls to a class’s
! constructor.

Consider the following Account constructor:

class Account{
    public:
        Account(double a): balance(b){}
    private:
        double balance;
        std::string cur;
};  

! An instance can be created like this:
Account acc = 100.0;



A double is being assigned to an Account object, but the compiler implicitly
calls the constructor that takes a double as an argument. Hence, the operation
works without any errors.
! If the constructor had been made explicit, this statement would not have
! worked. For this, we would have to use the explicit keyword.



class Account{
    public:
        explicit Account(double b): balance(b){}
        Account (double b, std::string c): balance(b), cur(c){}
    private:
        double balance;
        std::string cur;
};
Account account = 100.0; // ERROR: implicit conversion
Account account(100.0); // OK: explicit invocation
Account account = {100.0,"EUR"}; // OK: implicit conversion

! Now, the assignment operator won’t work as it did before, though it still works
! for Account(double b, std::string c) since it has not been made explicit.


Example #
Here’s a complete example showing the use of the explicit keyword:
!implicit:
#include <iostream>
#include <string>
class Account{
public:
Account(double b): balance(b){}
Account(double b, std::string c):balance(b), cur(c){}
private:
double balance;
std::string cur;
};
void strange(Account a){
std::cout << "It works!" << std::endl;
}
int main(){
Account account = 100.0; // No ERROR
Account account1(100.0);
Account account2 = {100.0, "EUR"};
strange(100.0);
// No ERROR
strange(false);
}
!Explicit:
check the website see if you can find the source code


In the implicit approach, the assignment operations in lines 20 and 22 do
not cause an error.

In the implicit approach, the function strange has an Account parameter,
but passing it a double or bool implicitly calls the Account constructor,
as done in lines 23 and 24.

! When the explicit keyword is introduced in the code, implicit
! constructor calls are restricted.

Uncomment the lines to observe the error shown by the compiler in the
explicit code tab.




-----------------------
from the internet:
X x;
Y y(x); //explicit conversion

X x;
Y y = x; //implicit conversion//this case is not an assignment, its an initialization, the assignment operator (operator=) is never called; instead a non-explicit one parameter constructor that accepts the type X as a parameter is called.

! The difference between initialization and  assignment is important: in the first case a mew pnkect os neomg created and it starts its life with the value 
! that it is being initializd with(hence why a constructor is called) while assignment happens when an object is assigned (~ coppied) to an object that already exists and already is in a defined state.
! The two forms of initialization that you wrote differe in the fact that in the first case you are explicitly calling a constructor and thus any constructor is acceptable; in the second acase, you're calling a constructor implicitly, since you're not using the classical constructor syntax, but the initialization syntax.
! in this case, only one-parameter constructors not marked with explicit are acceptable.
! such constructors are called by some people"converting" constructor, because the are involved in implicit conversions.
! any constructor not marked as explicit can take part in an implicit conversion for e.g. converting an object passed to a function to the type expected by such function.
! Actually, you may say that its waht happens in your second example: you want to initialize (=create with a value copied from elsewhere) y with x, but x first hat to be converted to type Y, which is done wit an implicit constructor.
! This kind of implicit conversion is often desirable: think for example to a string class that has converting(i.e. non-explicit)
! constructor from a const char*: any function that receives a string parameter can aslo be called with a "normal" C-string: because of te converging constructor the called will use C-strings. the callee will receive its string object.
!... see implicit VS explicit conversion stackoverflow


*/



#include<iostream>
#include<string>

class Account{
public:
    explicit Account(double b):balance(b){std::cout<<"default"<<"\n";}
    explicit Account(double b, std::string c): balance(b), cur(c){}
private:
    double balance;
    std::string cur;
};


void strange(Account a)
{
    std::cout<<"It works! "<<"\n";
}

int main()
{
    //Account account = 100.0; // Error
    Account account1{100.0};
    //Account accounr2 = {100.0,"EUR"}; // Error

    //strange(100.0); // Error
    //strange(false);  // Error
}