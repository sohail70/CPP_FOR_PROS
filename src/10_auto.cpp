/**
Automatic Type Deduction: auto
One of the best features shipped in C++11 was automatic type deduction.
The auto keyword can be used to let the compiler decide the data type itself.
We no longer need to explicitly define data types, 
*! which is a big help,especially when we’re dealing with complex template expressions.

#include <iostream>
int main() {
    auto myStr = "Educative";
    auto myDoub = 3.14;
    auto myInt = 3;
    std::cout << myStr << std::endl;
    std::cout << myDoub << std::endl;
    std::cout << myInt << std::endl;
}

*! It enables us to work with unknown types
auto func=[]{ return 5; }; //its a lambda
It has to be used with care in combination with initializer lists:
auto myInt{2011};
auto myInt2= {2011};

*! Good website for insight---> https://cppinsights.io/ and about auto https://www.modernescpp.com/index.php/c-insights-type-deduction

auto -matically initialized #
*! auto determines its type from an initializer. That simply means that; without
*! an initializer, there is no type and therefore, no variable. In simpler terms, the
*! compiler ensures that each type is initialized. This is a nice side effect of auto
*! which is rarely mentioned.

It makes no difference whether we forget to initialize a variable or didn’t
initialize it because of a misunderstanding of the language. The result is the
same: undefined behaviour. With auto , we can overcome these nasty errors.


*! read https://en.cppreference.com/w/cpp/language/default_initialization and all the reference articles

The article contains the following statement: “objects with automatic storage
duration (and their sub-objects) are initialized to indeterminate values”. This
optimization causes more harm than good. Local variables that are not user-
defined will not be default initialized.
I modified the second program to default initialization to make the undefined
behavior more obvious.
see the undefined beahviour program in below.


Using auto #
Now, we will rewrite the program with the help of auto .
see below-->3rd program
Firstly, in line 9, the
current standard forbids us to initialize non-constant members of a class with
auto . Therefore, we have to use an explicit type. This perspective is
counterintuitive. Here is a discussion by the C++ standardization committee
about this issue: https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3897.html

Second, as we can see in line 23, C++14 gets C++ string literals. We build them
by using a C string literal, "" , and add the suffix s, ""s . For convenience, we
imported that in line 20: using namespace std::string_literals .

*/

/*
#include<vector>

int myAdd(int a, int b) {return a+b;}

int main()
{
    //define an int-value
    int i = 5; //explicit
    auto i1 = i; //auto

    //define a reference to an int
    int& b = i; //explicit
    auto& b1 = i; //auto

    //define a pointer to a function
    int (*add)(int, int) = myAdd; //explicit
    auto add1 = myAdd; //auto

    //iterate through a vector
    std::vector<int> vec;
    for (std::vector<int>::iterator it = vec.begin();it!=vec.end();++it){} 
    for (auto it1 = vec.begin(); it1!=vec.end();++it1 ) {}
}

*/


/////////////////////////////////////////////////

/*
Undefined behavior #
First, let’s talk about the scope resolution operator, :: , in line 25. ::
addresses the global scope. In our case, it is the variable n in line 14.
Curiously enough, the automatic variable, n , in line 20 has the value 0 . n has
an undefined value and therefore the program has undefined behavior. This
will also hold for the variable mem of the class T2 as T2.mem returns an
undefined value.
*/

/*
#include<iostream>
#include<string>

struct T1{};

struct T2{
    int mem; //Not ok: indeterminate value
    
    public:
        T2(){}
};

int n; //Ok: initialized to 0


int main()
{
    int n; //Not ok : indeterminate value
    std::string s; //Ok: invocation of the default constructor, initialized to ""
    T1 t1; //Ok: Invocation of the default constructor
    T2 t2; //Ok: Invocation of the default constructor

    std::cout<<::n<<" "<<n<<" "<<s<<" "<<T2().mem;
    
}

*/



////////////////////////////////////////////////////////////

/* using auto



*/


#include<iostream>
#include<string>

struct T1{};

struct T2{
    int mem; //! auto mem= 0 is an error --> the current standard forbids us to initialize non-constant members of a class with auto Therefore, we have to use an explicit type
    
    public:
        T2(){}
};

auto n = 0; 


int main()
{
    using namespace std::string_literals;
    auto n = 0; 
    auto s = ""s; 
    auto t1 = T1(); 
    auto t2 = T2();


    std::cout<<::n<<" "<<n<<" "<<s<<" "<<T2().mem;
    
}
