///Literals
#include<string>
std::string nat = "C:\temp\newFile.txt";
std::string raw1 = std::string(R"(C:\temp\newFile.txt)"); // not processing \t \n
std::string raw2 = std::string(R"TRENNER(C:\temp\newFile.txt)TRENNER"); // including delimeter

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///user-defined literals-->    <built_in-Literal like numbers or strings or time units like std::chrono etc> + _ + <a unit>  ---> 123.45_km  or '1'_character --->'hi'_c compiler would try to run the operator ""_c('s',2) 2 is the length of the string
///use namespaces for user-defined literals because name collisions are very likely
/// 0101001000_b ----compiler map----> operator"" _b(long long int bin)
/// _km --> why the underscore? to distinguish them from built-in literals
/// GOAL: type-safe arithmetic. The compiler ensures that it is impossible to add apples and pears.
/// int --map---> unsigned long long int or cstring like char,wchar_t,char16_t,char32_t
/// float--map---> long double or cstring like  char,wchar_t,char16_t,char32_t
/// 1.0_km + 100.0_m + 15.0_cm ---> if you didn't put .0 then compiler would give you an error because we need long double
namespace Distance
{
    class MyDistance
    {
        public:
            MyDistance(double i) :m(i){}

        friend MyDistance operator +(const MyDistance& dist1 , const MyDistance& dist2)
        {
            return MyDistance(dist1.m + dist2.m);
        }
        
        //overloaded the output operator:
        //operator<< only need two function args but when you use it as a member function therefore the first parameter is implicitly
        //the calling object so it gives an error unless you overload it as friend function or as a free function
        //https://stackoverflow.com/questions/16291623/operator-overloading-c-too-many-parameters-for-operation
        friend std::ostream& operator<< (std::ostream &out , const MyDistance& myDist)
        {
            out<< myDist.m <<" m";
            return out;
        }
        private:
            double m;
    };

    namespace Unit
    {
        MyDistance operator "" _km(long double d) // notice the space which is essential in c++11 but not in c++14
        {
            return MyDistance(1000*d);
        }
        MyDistance operator "" _cm(long double d)
        {
            return MyDistance(d/100); //conversion of cm to meters
        }
    }
}

using namespace Distance::Unit;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// build-in literals ---> like std::chrono --> Making the correct additions or substraction or division or etc is the job of the compiler
/// chrono----> tick is number of seconds per tick --> tick's period --->for example in the first line hour(20) means 20 ticks and if the ratio is <20,1> it means 20/1 which means every tick is 20 seconds so 400 seconds
/// std::ratio<1,25>   means 1/25  --> so every tick has the value of 1/25   ---> so if you have 100 ticks then 100*1/25 =40 
/// convert to std::ratio<25,1> --> every tick has the value of 25 so:
/// one tick has the value 25 then how many ticks has the value of 40 ---> the answer is 1.6
/// don't try to think of the std::ratio as a multiplication because the compiler does the conversion think of it as a value of each tick
///I'm not sure but I think std::ratio<1,1> is in seconds ---> 1 tic ktakes 1 second
/// std::ratio<3600,1> --> 1 tick takes 3600secods = 1hour
///std::ratio <60,1> ---> 1 tick takes 60 secs = 1 min
/// std::ratio <1,1000> ---> 1 tick takes 1 miliseconds = 0.001 secs
#include<chrono>
#include<iostream>
using namespace std::literals::chrono_literals; // 20min , 900s , etc

typedef std::chrono::duration<long long,std::ratio<3600,1>> hour; //auto in_sec = hour(2)  ---> two ticks and each tick has the unit of 3600/1 so two ticks take 7200 units
auto school_hour = hour(2);
auto long_break = 1800s; //or type 30min
auto school_day_in_seconds = school_hour + long_break; //because  lowest unit is seconds in long_break varaible
//converting units
std::chrono::duration<double, std::ratio<60,1>> school_day_in_mins = school_day_in_seconds;
std::chrono::duration<double,std::ratio<3600,1>> school_day_in_hours = school_day_in_seconds; //har 3600 ta tick(sec) ye unit bere jolo
std::chrono::duration<double,std::ratio<1,1000>> school_day_in_milliseconds = school_day_in_seconds;
std::cout<<"School day in hour: "<<school_day_in_hours.count()<<"\n";
std::cout<<"School day in minutes: " <<school_day_in_mins.count()<<"\n";
std::cout<<"School day in milliseconds: " <<school_day_in_milliseconds.count()<<"\n";




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///unscoped and scoped enumerations
///Drawbacks of enumerations in classical C++ :  1. Enumerators implicitly convert to int  , 2. Enumerators in the enclosing scope.
/// 3. The type of the enumeration cannot be specified-->Enumerations cannot be forward declared because their
///    type is unknown. There is only one guarantee for enumerations in classical
///    C++: the type must be integral and big enough to hold the enumerator values.

///The strongly-typed enumerations have to follow stronger rules: 1. The enumerators can only be accessed in the scope of the enumeration.
///2. The enumerators don’t implicitly convert to int .
///3. The enumerators aren’t imported into the enclosing scope.
///4. The type of the enumerators is by default int . Therefore, we can forward declare the enumeration. --> yadet bashe type int be in mana nist ke implicit conversion dashte bashe balke bayad hatman static_Cast kuni
///forward declartion means --> enum class myEnumProcessState: unsigned int;     THEN:
/// Full declaration in another header
enum class myEnumProcessState: unsigned int {
    eNotRunning,
    eRunning
};

///enum means 'enumerated type' and it's not supposed to be changed and should be fixed. For example, a studnet is either a male or female, there is no third possibility. It's a good idea to use enum in this case:

enum StudentType {
    STUDENT_TYPE_MALE,
    STUDENT_TYPE_FEMALE,
};

class StudentInfo {
    string name;
    string fathername;
    string surname;
    StudentType type; // Now I know that this variable must be one of the types available in 'StudentType'
    // ...
};
/*
Size of Enum : Enumeration "values" aren't stored at all, as they are compile-time named constants
The size is four bytes because the enum is stored as an int. With only 12 values, you really only need 4 bits, but 32 bit machines process 32 bit quantities more efficiently than smaller quantities.

0 0 0 0  January
0 0 0 1  February
0 0 1 0  March
0 0 1 1  April
0 1 0 0  May
0 1 0 1  June
0 1 1 0  July
0 1 1 1  August
1 0 0 0  September
1 0 0 1  October
1 0 1 0  November
1 0 1 1  December
1 1 0 0  ** unused **
1 1 0 1  ** unused **
1 1 1 0  ** unused **
1 1 1 1  ** unused **

Without enums, you might be tempted to use raw integers to represent the months. That would work and be efficient, but it would make your code hard to read. With enums, you get efficient storage and readability.

*/
enum Color{red=0,green=2,blue}; //so blue is 3

enum oldEnum{
        one=1,
        ten=10,
        hundred=100,
        thousand=1000
};
std::cout << 2*thousand + 0 *hundred + 1*ten +1*one<<"\n";

//size is 4 bytes (as int32) for the following enum
enum struct newEnum{
    one=1,
    ten=10,
    hundred=100,
    thousand=1000
};
std::cout << 2*static_cast<int>(newEnum::thousand) +  //If we want to use an enumerator as an int , we must explicitly convert it with static_cast .
             0*static_cast<int>(newEnum::hundred) +
             1*static_cast<int>(newEnum::ten) +
             1*static_cast<int> (newEnum::one) <<"\n";

//size is 1 byte for the following enum
enum struct color2:char{ //We can explicitly specify the type of enumerators. By default, it’s int . We can use integral types like bool , char , short int , long int , or, long long int. Depending on the base types, the enumerations can have different sizes.
    red=100,
    blue, //101
    green //102
};

color2 myColor{color2::red}; //myColor is red



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///pointers
/*
int i {2011};
int* iptr = &i;


The variable holding the
array is actually a pointer pointing to the array. arr itself holds the address for the zeroth index of the array
arr[i] is equivalent to *(arr+i) --> arr + i gives us the pointer to the i-th index

Dynamic memory : new
Pointers don’t always have to point to an existing value. They can be used to
create values and arrays in dynamic memory, which is really helpful during
runtime.

float* fltPtr = new float(50.505); // A float has been created in dynamic memory
int* intArray = new int[10]; // A dynamic array of size 10 has been created

Null Pointer:
Before C++11, 0 was often used --> khoob nist chun ba number 0 eshtebah mishe
NULL macro ham moshkel dare chun implicit conversion dare to int
dotaye bala dar template argument deduction ham moshkel daran
if we use the values 0 and NULL as arguments of the function template, the
compiler will loudly complain.
solution ---> nullptr
! The compiler deduces 0 in the function template to type int ; it deduces NULL
! to the type long int . But these observations will not hold true for nullptr .
! The nullptr in lines 12 and 16 is of the type std::nullptr_t .
*/
#include<typeinfo>
//int main()
{
    auto c = 0;
    std::cout<<typeid(c).name()<<"\n";
}


/*
? We cannot compare or convert a nullptr to an integral type.
There is one
exception to this rule. We can implicitly compare and convert a bool value
with a nullptr . 
! Therefore, we can use a nullptr in a logical expression.
*/

bool b(nullptr);
std::cout<<std::boolalpha<<"b: "<<b<<"\n";
long int* pi = nullptr;
auto val = 5;
if(nullptr<&val)
{
    std::cout<<"nullptr < &val" <<std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// function pointer
void addOne(int& a)
{
     a+=1;
}

int main()
{
    void (*fPointer) (int&) = addOne;
    auto fPointer2 = addOne;

    int a{10};
    addOne(a);
    fPointer(a);
    fPointer2(a);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// pointer to member var
struct X{
    int data;
};

int main{
    int X::* p = &X::data; //P pointer point to the member var, data

    X object;
    object.data = 2011;

    X* objPointer = new X;
    objPointer->data = 2014;

    X object2;
    object2.data = 3000;

    int k = object.*p; // I think you cant use that pointer without an object
    int soso = object2.*p;//*! WEIRD!
    int l = objptr->*p; 
    std::cout<<k<<" "<<l<<" "<<soso<<"\n";

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Reference
/*
References vs. pointers #
! A reference is never NULL . Therefore, it must always be initialized by having
! an existing variable assigned to it. The following lines would not work:
int& intRef;
int& intRef = NULL;

! References behave like constant pointers. A reference always refers to its
! initial variable. The value of the variable can change but the reference cannot
! be assigned to another variable.

References as parameters #
References allow functions to modify the value of a variable.
! This functionality is also very useful when dealing with a large argument.Passing it by value would mean that a copy has to be made in the function.
! This is memory-intensive.
! A reference to the argument would prevent unnecessary copying.
*/

int i = 20;
int& iRef = i; // iRef ro taghir bedi i ham taghir mikune

void xchg(int& x, int& y){ // Reference parameters
    int t = x;
    x = y;
    y = t;
}
xchg(a, b);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///auto automatic type deduction.
///There is a high potential for error if we keep defining types explicitly. Hence,
///it’s better to leave it to the compiler. It’ll save us time as well.
/*
! which is a big help,especially when we’re dealing with complex template expressions.
! It enables us to work with unknown types
auto func=[]{ return 5; }; //its a lambda

! auto determines its type from an initializer. That simply means that; without
! an initializer, there is no type and therefore, no variable. In simpler terms, the
! compiler ensures that each type is initialized. This is a nice side effect of auto
! which is rarely mentioned.
It makes no difference whether we forget to initialize a variable or didn’t
initialize it because of a misunderstanding of the language. The result is the
same: undefined behaviour. With auto , we can overcome these nasty errors.

*/
auto func=[]{ return 5; };

auto myInt{2011}; // auto=int bishtar az ye addad ham nemishe gozasht --> mage --> std::initializer_list a{1,2,3};
auto myInt2= {2011};// auto=std::initializer_list

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


//without auto --> Undefined behavior 
struct T1{};
struct T2{
    int mem; //indeterminate value so cout is undefined behavior
    public:
        T2(){}
};
int n; //in init mishe be 0 khod be khod
int main()
{
        int n; //init nashe cout undefined behavior mishe!
        std::string s; //initialize ham nashe eshkal nadare chun default constructor dare va init mikune be ""
        T1 t1; //Ok: Invocation of the default constructor
        T2 t2; //Ok: Invocation of the default constructor
        std::cout<<::n<<" "<<n<<" "<<s<<" "<<T2().mem; //khoroji mishe --> 0 undefined "" undefined

}


//with auto
struct T1{};
struct T2{
    int mem = 0; //auto mem= 0 is an error .the current standard forbids us to initialize non-constant members of a class with auto Therefore, we have to use an explicit type
    public:
        T2(){}
};
auto n =0;
int main()
{
    using namespace std::string_literals;
    auto n = 0;
    auto s = ""s;
    auto t1 = T1();
    auto t2 = T2();
    std::cout<<::n<<" "<<n<<" "<<s<<" "<<T2().mem; //khoroji--> 0 0 "" 0 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Problems with refactoring data types
/*
When we replace the variable b with type int by a double, 10.5 , we have to
adjust all the dependent types. That is laborious and dangerous. We have to
use the right types and take care of narrowing and other intelligent
phenomenons in C++

*/
int a2 = 5;
double b2 = 10.5
double sum2 = a2*b2*3;
double res2 = sum2*10.5;

/*
The danger seen above is not present when using auto --> type tavasot compiler detect mishe --> az typeid(var).name() use kun
*/
auto a3 = 5;
auto b3 = 10;
auto sum3 = a3*b3*3.1f;  //tabdil be float mishe
auto res3 = sum3*10;
std::cout<<typeid(res3).name()<<"\n";




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Replacing basic data types

auto i = 5;
auto& intRef = i; //int& ---> this is the auto type deduction, deduced by the compiler by seeing whats the value stored in it.
auto* intPoint = &i; //int*
const auto constInt = i; //const int
static auto staticInt = 10; //static int

//Copying a vector and the reference to it using the assignement operator =
std::vector<int> myVec;
auto vec = myVec; //std::vector<int>
auto& vecRef = vec; //std::vector<int>&

int myData[10];
auto v1 = myData; //int*  
auto& v2 = myData; //int (&)[10]  //*! What the hell is this? is it a reference to a pointer

auto myFunc = func; //(int)(*)(int)   ---> function pointer
auto& myFuncRef = func; //(int)(&)(int) --->reference to the function

//Define a function pointer
int (*myAdd1)(int,int) = [](int a ,int b){return a+b;};

//Use type inference of the c++11 compiler
auto myAdd2 = [](int a , int b){return a+b;}; //lambda expression whose return type is inferred by the c++ compiler since we have used the auto keyword



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
auto myInts = {1,2,3}; //---> use #include<initializer_list> if you don't want to use auto
auto myIntBegin = myInts.begin(); //std::initializer_list<int>::iterator  

std::map<int , std::string> myMap = { {1,std::string("one")} , {2,std::string("two")} };
auto myMapBegin = myMap.begin(); //std::map<int, std::string>::iterator

auto func = [](const std::string& a){return a;}; //std::function< std::string(const std::string&) > func= [](const std::string& a){ return a;}  ---> use #include<functinoal>
//auto futureLambda   = std::async([](const std::string& s ) {return std::string("Hello ") + s;})  //std::future<std::string> futureLambda= std::async([](const std::string& s ) {return std::st
auto begin = std::chrono::system_clock::now();// std::chrono::time_point<std::chrono::system_clock> begin = ...

auto pa = std::make_pair(1,std::string("second")); //std::pair<int, std::string> pa = std::make_pair(1, std::string("second"));

auto tup = std::make_tuple(std::string("first") , 4 ,1.1 , true , 'a'); //std::tuple<std::string, int, double, bool, char> tup = std::make_tuple(std::string("second"...
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// decltype vs auto
/// ! decltype is used to determine the type of an expression or entity.            decltype(expression)
/// ! We can use auto to create variables, but decltype returns the type of an expression containing variables.
/// ! If the expression is an lvalue, decltype will return a reference to the data type to the expression
/// ! If the expression is an rvalue, decltype will return the data type of the value
///decltype is not used as often as auto . It is useful with templates that can deduce the type of a function.
int i = 1998; //Rvalue
decltype(i) i2 = 2011; //Same as int i2 = 2011
//! the parentheses around i indicate that this is an expression instead of a variable. Hence, decltype computes int& instead of int .
decltype((i)) iRef = i2; // (i) is an lvalue, reference returned
std::cout<<iRef<<"\n";
std::cout<<i2<<"\n";
iRef = 2012;
std::cout<<iRef<<"\n";
std::cout<<i2<<"\n"; //iRef is a reference after all

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///decltype
decltype(5) i = 5 ; //int
int& intRef = i; //int&
decltype(intRef) intRefD = intRef; //int&
int* intPoint = &i; //int*
decltype(intPoint) intPointD = intPoint; //int*
const int constInt = i; //const int
decltype(constInt) constIntD = constInt; //const int
static int staticInt = 10; //static int
decltype(staticInt) staticIntD = staticInt; //static int
const std::vector<int> myVec;
decltype(myVec) vecD = myVec; //const std::vector<int>
auto myFunc = func; //(int) (*) (int , int )
decltype(myFunc) myFuncD = myFunc; //(int)(*)(int , int)
//define a function pointer
int (*myAdd1)(int ,int) = [](int a , int b){return a+b;};
//use type inference of the c++ compiler
decltype(myAdd1) myAdd2 = [](int a ,int b){return a+b;};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///automatically deduce the return type of a function --> decltype+auto
template<typename T1 , typename T2>
auto add(T1 fir , T2 sec) -> decltype(fir+sec)
{
    return fir+sec;
}
//! C++14 makes things even simpler. We don’t need to use decltype to deducethe function’s return type anymore. auto handles everything:
template <typename T1, typename T2>
auto add(T1 fir, T2 sec){
    return fir + sec;
}



/*
auto uses the same rules to determine
the type as decltype

Both declarations are identical:

decltype(expr) v= expr;
decltype(auto) v= expr;
*/

template <typename T1, typename T2>
decltype(auto) add(T1 fir, T2 sec){
    return fir + sec;
}
/*
Note: 
!When a function template multiple return statements, all of them must have the same type.
*/


#include<iostream>
#include<typeinfo>
#include<string>

template<typename T1 , typename T2>
auto add(T1 first , T2 second) ->decltype(first+second)
{
    return first+second;
}
int main()
{
    std::cout<<typeid(add(1,1)).name()<<"\n"; //returns a string representation of the return type.
}
///! compiler performs implicit casts during operations
//When booleans and integers are operated together, the result is a cast to int .
std::cout<<typeid(add(1,false)).name() <<std::endl;
std::cout<<typeid(add('a',1)).name() <<"\n";
std::cout<<typeid(add(false,false)).name()<<"\n";
//From lines 19 to 20, we can see arithmetic operations that get implicitly cast to the double data type. The result of arithmetic operations between integers and doubles is a double.
std::cout<<typeid(add(true,3.14)).name()<<"\n";
std::cout<<typeid(add(1,4.0)).name()<<"\n";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Explicit cast
/*
c cast ---> double myDouble{5.5};
            int i = (int)myDouble
We should avoid using C-casts since they present a number of problems.
/! What is bad about the C-cast? We don’t see which cast is actually used. If we perform a C-cast, a combination of casts will be applied, if necessary. Roughly speaking, a C-cast starts with a static_cast , continues with a const_cast , and finally performs a reinterpret_cast .
/! it is always better and safer to use named casts instead of C-casts.
/!explicit is better than implicit.

/! Let’s see what happens if we screw up the type system:
*/
double d = 2;
auto p = (long*)&d;
auto q = (long long*)&d;
std::cout<<d<<" "<<*p<<" "<<*q<<"\n"; //2 4611686018427387904 4611686018427387904

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Dynamic cast
//! dynamic_cast converts a pointer or reference of a class to a pointer or reference in the same inheritance hierarchy.
//! It can only be used with polymorphic classes. With dynamic_cast , we cast up, down, and across the inheritance hierarchy.
//! Type information at run time is used to determine if the cast is valid.
//! If the cast is not possible, we will get a nullptr in case of a pointer, and an std::bad_cast-exception in case of a reference.
//! dynamic_cast is mostly used when converting from a derived class to a base class, but can also work the opposite operation.
//! Do keep in mind that dynamic_cast only deals with pointers and references.
// virtual haro bardari error mide chun fek kunam bayad polymorphic bashe vase dynamic_cast 
class Account
{
    public:
        virtual ~Account() = default;
};
class BankAccount: virtual public Account(){};
class WireAccount: virtual public Account(){};

class SavingsAccount: public BankAccount,public WireAccount{};
class CheckingAccount: public BacnkAccount, public  WireAccount{};
int main()
{
    Account* a = nullptr;
    BankAccount* b = nullptr;
    WireAccount* w = nullptr;
    SavingsAccount* s = nullptr;
    CheckingAccount c;
    a = dynamic_cast<Account*>(&c); //upcast
    a = &c; //upcast
    b = dynamic_cast<BankAccount*>(a);//downcast
    w = dynamic_cast<WireAccount*>(b); //crosscast
    s = dynamic_cast<SavingsAccount*>(a);//downcast
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///static_cast
/*
!It can only perform all the conversions that are well-defined by the compiler. For example, a string to integer cast won’t work.

! It allows bidirectional conversion between related data types such as:
! pointer types in class hierarchies
! integrals and floating-point numbers
! integrals and enumerations

!static_cast cannot be used with polymorphic types.

!Unlike dynamic_cast , a static_cast is performed during compile time.
*/
//we can see how static_cast supports up and down casting between pointers of the same class hierarchy.
Account* a  = nullptr;
BankAccount* b = nullptr;
a = static_cast<Account*>(b); //upcast
a = b ; //upcast

b = static_cast<BankAccount*>(a); //downcast

//An integer can be cast into an enum state using static_cast
int i(2);
Color col = static_cast<Color>(i);
std::cout<<i<<"\n";
std::cout<<col<<"\n";
//A simple conversion from float to integer
int i2 = static_cast<int>(3.14);
std::cout<<i<<"\n";

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// const_cast
/*
!const_cast allows us to remove or add the const or volatile property from a variable.
!const_cast is perhaps the most rarely used cast operator because it is undefined behavior to remove const or volatile from a variable if the variable was declared const or volatile in the first place.
!This sort of behavior creates a discrepancy in the code since two pointers of different types are pointing to the same variable. Hence, it’s better to avoid such a practice.

*/
int i{2011};
const int* constI = const_cast<const int*>(&i); //A const int pointer for an int
int* nonConstI = const_cast<int*> (constI); //Casting to an int pointer
*nonConstI = 9000;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///reinterpret_cast
/*
reinterpret_cast allows us to convert a pointer of a particular type to a
pointer of any other type, regardless of whether the types are related or
not.
It also allows conversion between a pointer and an integral.
reinterpret_cast guarantees that if a pointer is cast into another type,
casting it back would return the original value.
The use of reinterpret_cast is not recommended as it does not take any
safety measures before converting between types. This can result in
faulty or accidental conversions that could harm the code.
*/
double* myDouble = new double(3.14);
void* myVoid = reinterpret_cast<void*>(myDouble);
double* myDouble1 = reinterpret_cast<double*>(myVoid); //original value (3.14) retrieved

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

/! FROM NOW ON BE MORE SPECIFIC AND MORE SUCCICNT 

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// TYPE INFORMATION 
#include<iostream>
#include<typeinfo> //type of the var or object at runtime

int main()
{

    const std::typeinfo& t = typeid(Circle);  //const? because each type has a single_type_info
    if(typeid(int) == typeid(long long))
    {
        std::cout<<"same"<<"\n";
    }

    int long long il{2011};
    std::cout<<typeid(il).name()<<"\n"; //name method gives the name of the type
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///UNIFIED INITIALIZATION WITH {}
std::string str{"my string"}; //direct initialization --> directly calls the constructor of the type
std::string str = {"my String"}; //copy initialization ---> the value is created and implicitly converted into the type
///Narrowing --> implicit conversion of arithmetic values from one type to another ---> dangerous --> data loss 
int i1(3.14);//narrowing-->because 3.14 doesn't fit into the int type
int i2(3.14);//narrowing
///use {} to avoid narrowing
int i1 {3.14}; //with gcc 6.1 and above you get an error and below that you get a warning.Compile the program in such a way that narrowing is an error
int i2 = {3.14};

char c1{97}; //no error because 97 fits into char type
char c2 = {97}


class MyClass{
    public:
        int x;
        double y;
};

MyClass alsoClass{5,3.2};


const float* pData = new const float[4]{1.5,4,3.5,4.5};

std::vector<int> v{1}; //or v={1};
std::unordered_map<std::string,int> um{{"dijkstra,1972"},{"scott",1976}};
v.insert(v.end(),{99,88,-1});

void getVector(const std::vector<int>& v)
{

}
getVector({v[0],5,12,20});

MyClass getT()
{
    return {1,1234};
}

auto a= {42}; //std::initializer_list<int>
auto b{42};  //int
auto c = {1,2}; //std::initializer_list<int>
auto d {1,2} ;//Error

#include<initializer_list>
class MyData{
    public:
        MyData(int , int) { //classical constructor
            std::cout << "MyData(int, int)" << std::endl;
        }
        MyData(std::initializer_list<int>) // sequence constructor: The sequence constructor is a constructor that takes an std::initalizer_list .
        {
            std::cout << "MyData(std::initializer_list<int>)" << std::endl;
        }
}

MyData{1,2}; //Which constructor? sequence constructor has a higher probability
MyData(1,2); //evoke the classical constructor explicitly


#include<set>
#include<unordered_set>
//! Integers are inserted in numerical order and duplicate elements, such as
//! 5 , are not inserted in the set.
std::set<int> mySet{-10,5,1,4,5} ;
//!The keys are not sorted. Duplicate keys are allowed in a std::unordered_multiset .
std::unordered_multiset<int> myUnorderedMultiSet = {-10,5,1,4,5};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CONST
//!Class methods can also be const but they can only be invoked by const instances of the class.
int const* ip = &i; // you can not change the content i //fek kunam farghi ba const int* ip nadare
int* const p =&i; //the pointer is const and you can not point to a different pointer
const int* const p = &i; //both are const

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CONSTEXPR --> expr to be evaluated at compile time -->Therefore, we can use the variable in contexts that require a constant expression, e.g., defining the size of an array. This has to be done at compile time.
//!If we evaluate a variable at compile-time, the variable can only depend on values that can be evaluated at compile time.

/// User-Defined types:

#include<iostream>
class me{
    public:
        constexpr me(){} //each used constructor (e.g of a base class) has to be a constexpr --> age constexpr nabashe error mide main vaghti My ro seda mizani
};

class My: public me{
    public:
        //each base object and each non-static member is initialized in the initialization list of the constructor, or directly in the class body--> so myVal has to be initialized in the constructor
        constexpr My(double d):i(d) {}; //constexpr constructor can only be invoked with constant expressions.,cannot use exception handling.,has to be declared as default or delete or the function body must be empty (C++11).
        constexpr double getVal(){return i;} //The user-defined type can have methods that may or may not be constant expressions.
    private:
        double i; //bayad dar constructor initlize beshe tavasote initializer list --> body of constructor must be empty
};
int main()
{
    constexpr My obj(2); //Instances of My can be instantiated at compile time.
    static_assert(obj.getVal()==2); //it will hold because instances of My class will be created at compile-time. ---> albate in error mide nemidonam chera va ba obj nemishe getVal ro call kard?????!!!!! dalilesh marbote be const boodan mishe chun age constexpr ro jash const ham bexari hamine dastan
}
//deghat: Streaming to std::cout is not allowed in a constexpr function context. In fact, only a limited set of things are.
/// constexpr Functions --> restrictions for c++11 ke dar c++14 behtar shodan va dar paeen migim: The function:  has to be non-virtual. can only have one return statement. must return a value. must have a constant return value. can only have a function body consisting of a return statement.
constexpr auto res = constexprFunction() //constexpr functions are funcs that can be evaluated at compile time---> result is available at runtime  and stored in the ROM(read-only memory)
constexpr int fac{int n}
    {return n> 0 ? n* fac(n-1):1;} 
constexpr int gcd(int a , int b)
    {return (b==0) ? a: gcd(b,a%b);}
//age constexprfunction ro ba non-constexpr value invoke kuni dar run-time run mishe na compile time -->use static_assert

//c++14 --> The difference between ordinary functions and constexpr functions in C++14 is minimal
/*
 constexpr functions in C++14:
   can have variables that have to be initialized by a constant expression.
   can have loops.
   cannot have static or thread_local data.
   can have conditional jump instructions or loop instructions.
   can have more than one instruction.
*/
constexpr auto gcd (int a, int b)
{
    while(b != 0 )
    {
        auto  t=b;
        b = a%b;
        a = t;
    }
    return a;
}
int main()
{
    constexpr auto i = gcd(11,121); //compile time calculation --> debugger bezari to gcd mibini ba F11 ham tosh nemire chun ghablan dar compile time mohasebe shode
    auto a = 11;
    auto b = 121;
    //!The compiler would complain when we declare j as constexpr : constexpr int j = gcd(a, b) . The problem is that int a , and int b are not constant expressions.
    int j =gcd(a,b); //run-time calculation because the int a,b are not constexpr 
}


//khodam???!!!
#include<iostream>

constexpr int addOne(int i)
{
    return i+1;
}
int main()
{
    constexpr int j = addOne(1); //in compile time mire

    constexpr int k =10;
    std::cout<<addOne(k)<<"\n"; // ama in run-time mire ? chera?
    std::cout<<"\n";
}

//!at compile time, executed functions have to be pure functions
///Pure functions at compile time, executed functions have to be pure functions. When we use this constexpr function at runtime the function stays pure.
/*
! Pure functions are functions that always return the same result when given    ---> like sin() sqrt() max() ---> impure funcs like rand() time() ...
! the same arguments. Pure functions are like infinitely large tables from which
! we get our value. The guarantee that an expression always returns the same
! result when given the same arguments is called referential transparency.
Pure functions have a lot of advantages:
!   The function call can be replaced by the result.
!   The execution of pure functions can automatically be distributed to other threads.
!   Function calls can be reordered.
!   They can easily be refactored.

*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ASSERTION
constexpr int square(int x){return x*x;}
constexpr int squareToSquare(int x){return square(square(x));}
int main()
{
    static_assert(square(10)==100,"You calculated it wrong"); //static assert will hold because they can be evaluated at compile-time
    static_assert(squareToSquare(10)==1000,"You calculated it wrong"); //it will hold
    
    constexpr int constExpr = square(10);
    int arrayClassic[100];
    int arrayWithConstExpression[constExpr];
    int arrayWithConstExpressionFunction[square(10)]; //Notice that the input argument for this function call is constant.
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// VOLATILE --->typically used in embedded programming ---> volatile vs std::atomic --->What do the volatile keywords in C# and Java have in common with the volatile keyword in C++? Nothing--->volatile keyword in C# and java is std::atomic in c++ -->i.e. --> volatile has no multithreading semantics in c++
/// volatile ---> for special objects on which optimized read or write operations are not allowed 
/// std::atomic ---> atomic variables --> thread safe reading and writing
/// you can change the variable withing your code but what if an external I/O event that tries to change the value of the variable --> so the obj can change independent of the program flow hence their values will be written directly in the main memory hence there is no optimized storing in cache


//! So what happens when we declare the int variables as volatile ? I guess we
//! know. The program has a data race on the variables, x and y . So, theprogram has undefined behavior and we cannot reason about x and y .
#include<iostream>
#include<thread>
volatile int x = 0;
volatile int y = 0;

void writing()
{
    x = 2000;
    y = 11;
}
void reading()
{
    std::cout<<y<<"\n";
    std::cout<<x<<"\n";
}

int main()
{
    std::thread thread1(writing);
    std::thread thread2(reading);
    thread1.join();
    thread2.join();
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///RVALUES AND LVALUES


int lValue = 1998; // 1998 is an rvalue --> rvalue---> temporary objects without a name ---> they are stored in register for a short time ---> not in a memory
lValue = 2011;

MyData myData;
MyData& lValueRef(myData); //lvalue ref
MyData&& rValueRef(MyData()); //rvalue ref
const MyData& constLvalueRef(MyData()); //const lvalue ref

/*
Lvalue ---can only be bound to ---> lvalue    
rvalue ---can only be bound to-----> rvalue reference / const lValue ref --->binding of rvalue to rvalue ref has higher priority
--->so --->int& a = 10 gives an error you can not bind rvalue to lvalue ref unless its const 

Rvalue references: applications
! Move semantics 
    ! Cheap moving of objects instead of expensive copying.
    ! No memory allocation and deallocation.
    ! Non-copyable but movable objects can be transferred by value.
! Perfect forwarding 
    ! Forward an object without changing its rvalue/lvalue nature. This helps
    ! in function templates.
*/

struct MyData{};

int main()
{
    MyData myData;
    MyData& lValueRef(myData);
    MyData&& rValueRef(MyData()); //binding rvalue (MyData()) to rvalue ref
    const MyData& constLvalueRef(MyData()); //binding an rvalue (MyData()) to const lvalue ref
}







#include<iostream>
#include<algorithm>
#include<string>

struct MyData{};
std::string function(const MyData &a)
{
    return "lvalue reference";
}
std::string function(MyData&&)
{
    return "rvalue reference";
}
int main()
{
    MyData myData;
    std::cout<<function(myData)<<"\n"; //myData ke bere to function mishe lvalue reference because it has a name and an address
    std::cout<<function(MyData())<<"\n";//MyData() is an rvalue reference since it does not have a name or an address. It is just a call to the default constructor of the struct MyData .
    std::cout<<function(std::move(myData))<<"\n";//std::move(myData) creates an rvalue reference as well since we can neither determine the destination address of myData , nor the destination variable’s name.
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///COPY VS MOVE SEMANTICS --> move---> transfer ownership -> giving the object to someone else
/*
! 1. With the copy semantic, it is possible that a std::bad_alloc will be thrown
! because our program is out of memory.
! 2. The resource of the move operation is in a “valid but unspecified state”
! afterward.

! A class supports copy semantics if the class has a copy constructor and a copy
! assignment operator.

! A class supports move semantics if the class has a move constructor and a
! move assignment operator.


! If a class has a copy constructor, it should also have a copy assignment
! operator. The same holds true for the move constructor and move assignment
! operator.
*/

//copy
string str1("ABCDEF");
string str2;
str2 = str1;

//move
string str1("ABCDEF");
string str3;
str3 = std::move(str1); //now string str1 is empty bu in copy semantics they both have the same content



//swapping with move instead of copy semantic

template<typename T>
void swap(T& a , T& b)
{
    T tmp(a); //allocates tmp and eahc element from tmp. copy each eleemtn from a to tmp
    a = b; //
    b = tmp;
}

template<typename T>
void swap(T& a , T& b)
{
    T tmp(std::move(a)); //redirects the pointer from tmp to to a
    a = std::move(b);
    b = std::move(tmp);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// MOVE SEMANTICS --> Containers of the STL can have non-copyable elements. The copy semantic is the fallback for the move semantic.
/*
! Copy semantic is a fallback for move semantic. This means if we
! invoke std::move with a non-moveable type, copy-semantic is used
! because an rvalue can be bound to an rvalue reference and a constant
! lvalue reference.
*/

/*
std::move() --> Converts the type of its argument into a rvalue reference. --> It is a static_cast to a rvalue reference under the hood.
std::move needs #include<utility> -->fek nakunam vali! kar mikune haminjoori


static_cast<std::remove_reference<decltype(arg)>::type&&>(arg); 
What is happening here?
decltype(arg) : deduces the type of the argument.
std::remove_reference<....> removes all references from the type ofthe argument.
static_cast<....>&& adds two references to the type.
*/


/*
STL #
!Each container of the STL and std::string gets two new methods:
!Move constructor
!Move assignment operator
!These new methods get their arguments as non-constant rvalue references.
The classical copy constructor and copy assignment operator get their
argument as a constant lvalue reference.

Strategy of the move constructor #
1. Set the attributes of the new object.
2. Move the content of the old object.
3. Set the old object in a valid state.

*/
//Example #
vector{
    vector(vector&& vec); //move constructor
    vector& operator = (vector&& vec); //move assignment
    vector(const vector& vec); //copy constructor
    vector& operator = (const vector& vec); //copy assignment
}



/*

User-defined data types #
User-defined data types can support move and copy semantics as well.

Example #
class MyData{
    MyData(MyData&& m) = default;
    MyData& operator = (MyData&& m) = default;
    MyData(const MyData& m) = default;
    MyData& operator = (const myData& m) = default;
};

! The move semantic has priority over the copy semantic.

The move constructor is created automatically if all attributes of the class
and all base classes also have one move constructor.

This rule holds for the big six:
Default constructor
Destructor
Move and copy constructor
Move and copy assignment operator
*/


//Copying and moving strings #
#include<iostream>
#include<string>
#include<utility>

int main()
{
    std::string str1{"ABCDEF"};
    std::string str2;

    str2 = str1; //copy semantic ---> copy assignment dar class string hast dg ke deep copy kune
    
    std::string str3;
    str3 = std::move(str1); //move semantic ham dar class string hast --->  str1 tabdil mishe be "" va mire to str3
}


/*
When we invoke move on an only copyable type, copy-semantic will kick
in as fallback to move-semantic. The reason is that an rvalue is first
bound to an rvalue reference and second to a const lvalue reference. The
copy constructor and the copy assignment operator take constant lvalue
references.
*/
#include<iostream>
#include<algorithm>
#include<vector>

template<typename T>
void swap (T& a , T&b)
{
    T tmp(a); //invokes the copy constructor
    a = std::move(b); //invokes the copy assignment operator .so When we invoke move on an only copyable type, copy-semantic will kick in as fallback to move-semantic
    b = std::move(tmp);//invokes the copy assignment operator. so When we invoke move on an only copyable type, copy-semantic will kick in as fallback to move-semantic
}

struct MyData{ //MyData doesn’t support move semantics. so When we invoke move on an only copyable type, copy-semantic will kick in as fallback to move-semantic
    std::vector<int> myData;
    MyData():myData({1,2,3,4,5}){}

    //copy semantic
    MyData(const MyData& m):myData(m.myData)
    {
        std::cout<<"copy constructor"<<"\n";
    }
    MyData& operator = (const MyData& m)
    {
        myData = m.myData;
        std::cout<<"Copy assignment operator"<<"\n";
        return *this;
    }
};

int main()
{
    MyData a,b;
    swap(a,b);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///BIG ARRAY WITH ONLY COPY-SEMANTIC SUPPORT
#include<algorithm>
#include<chrono>
#include<iostream>
#include<vector>

class BigArray{
    public:
        BigArray(size_t len):len_(len),data_(new int[len]){}

        BigArray(const BigArray& other): len_(other.len_) , data_(new int[other.len_])
        {
            std::cout<<"Copy constructor of"<< other.len_<<" elements"<<"\n";
            std::copy(other.data_,other.data_ + len_ , data_);
        }
        BigArray& operator= (const BigArray& other)
        {
            std::cout<<"Copy Assignment " <<other.len_ <<" elements "<<"\n";
            if(this != &other)
            {
                delete[] data_;

                len_ = other.len_;
                data_ = new int(len_);
                std::copy(other.data_ , other.data_ + len_ , data_);
            }
            return *this;
        }

        ~BigArray()
        {
            if (data_ != nullptr) delete[] data_;
        }
    private:
        size_t len_;
        int* data_;
};

int main()
{
    std::vector<BigArray> myVec;
    auto begin = std::chrono::system_clock::now();

    myVec.push_back(BigArray(1000000000));
    auto end = std::chrono::system_clock::now();
    auto timeInSecond = std::chrono::duration<double>(end-begin).count();
    std::cout<<timeInSecond<<"\n";
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///BIG ARRAY WITH THE MOVE SEMANTIC
#include<algorithm>
#include<chrono>
#include<iostream>
#include<vector>

class BigArray{
    public:
        BigArray(size_t len):len_(len),data_(new int[len]){}

        BigArray(const BigArray& other): len_(other.len_) , data_(new int[other.len_])
        {
            std::cout<<"Copy constructor of"<< other.len_<<" elements"<<"\n";
            std::copy(other.data_,other.data_ + len_ , data_);
        }
        BigArray& operator= (const BigArray& other) 
        {
            std::cout<<"Copy Assignment " <<other.len_ <<" elements "<<"\n";
            if(this != &other) 
            {
                delete[] data_; 
                len_ = other.len_;
                data_ = new int(len_);
                std::copy(other.data_ , other.data_ + len_ , data_);
            }
            return *this;
        }

        BigArray(BigArray&& other): len_(other.len_),data_(other.data_)
        {
            std::cout<<"Move Constructor of "<<other.len_<<" elements"<<"\n";
            other.len_ = 0;
            other.data_ = nullptr;
        }

        BigArray& operator=(BigArray&& other) //assignment operator vaghti seda zade mishe ke content ye obj ro bekhay dar ye EXISTING obj dg berizi vali move constructor ya copy constructor obj ro ijad mikunan (C c; c=c1  VS C c=c1) -->avali assignment seda mizane dovomi constructor
        {
            std::cout<<"Move assignment of"<< other.len_ <<" elements"<<"\n";
            if(this != &other) //vase inke agar dar main eshtebahan benvisi --> dest = std::move(dest) oon vaght dochare memory leak mishim --> the cherno ro bebin
            {
                delete[] data_; //darim content ye object ro mirizim to ye obj dg pas on obj dg shayad az ghabl ye content ee dashte bashe vase hamin delete mikunim

                len_ = other.len_;
                data_ = other.data_;
                other.len_ = 0;
                other.data_ = nullptr;
            }
            return *this; 
        }

        ~BigArray()
        {
            if (data_ != nullptr) delete[] data_;
        }
    private:
        size_t len_;
        int* data_;
};

int main()
{
    std::vector<BigArray> myVec;
    auto begin = std::chrono::system_clock::now();
    
    myVec.push_back(BigArray(1000000000));
    auto end = std::chrono::system_clock::now();
    auto timeInSecond = std::chrono::duration<double>(end-begin).count();
    std::cout<<timeInSecond<<"\n";
}



//MY EXAMPLE for move assignment
#include<iostream>
class Vector{
    public:
        Vector(int length):len_(length),data_(new int(length)) ,counter(0){};
        void pushback(int d)
        {
            data_[counter] = d;
            counter++;
        }

        //move constructor
        Vector(Vector&& other)
        {
            len_ = other.len_;
            counter = other.counter;
            data_ = other.data_;

            len_ = counter = 0;
            data_ = nullptr;
        }

        Vector& operator=(Vector&& other)
        {
            delete[] data_;
            if(this != &other)
            {
                len_ = other.len_;
                counter = other.counter;
                data_ = other.data_;

                other.len_ = 0;
                other.counter = 0;
                other.data_ = nullptr;
            }
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out , Vector& vec)
        {
            for(int i = 0 ; i<vec.len_ ; i++)
                std::cout<<vec.data_[i]<<"\n";
            return out;
        }
        ~Vector() = default;

    private:
        size_t len_;
        int counter;
        int* data_;
};

int main()
{
    Vector myVec(5);
    myVec.pushback(2);
    myVec.pushback(3);
    std::cout<<"myVec: \n"<<myVec<<"\n";
    std::cout<<"\n";

    Vector myVec2(5);
    myVec2 = std::move(myVec);
    std::cout<<"myVec: \n"<<myVec<<"\n";
    std::cout<<"myVec2: \n"<<myVec2<<"\n";    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PERFECT FORWARDING
//! If a function template forwards its arguments without changing their
//! lvalue or rvalue characteristics, we call it perfect forwarding.
/* A perfect factory method 
function which:
! takes an arbitrary number of arguments.
! accepts lvalues and rvalues as arguments.
! forwards its arguments in the same way as the underlying constructor.
*/

#include <iostream>
template <typename T,typename Arg>
T create(Arg& a){ //Aya in khoobe? No ---> chun rvalue nemitone tosh biad --> int myFive = create<int>(5); in error mide --> const esh kunim chi? bazam khoob nist chun onvaght argument haro nemitoonim taghir bedim? che kunim? overload kuni bara const va non-const ke be tedad arg ha 2*arg+1 ta overload mikhay? rah hal dg chie? std::forward
    return T(a);
}
/*

! The (Arg&& a) universal reference in line 4 is a powerful
! reference that can bind lvalues or rvalues. Sometimes the term perfect
! forwarding reference is used for this special reference.
! To achieve perfect forwarding, we have to combine a universal reference with std::forward
! std::forward<Arg>(a) returns the underlying type of a ,
! because a is a universal reference. We can think of std::forward as a
! conditional move operation.
! When the argument a is an rvalue, std::forward moves its argument. When
! the argument a is an lvalue, it copies the argument. Therefore, an rvalue
! remains an rvalue.
*/
#include<iostream>
template <typename T , typename Arg>
T create (Arg&& a)
{
    return T(std::forward<Arg>(a));
}



/*
! Variadic Templates are templates that can get an arbitrary number of
! arguments. That is exactly the feature missing from our current perfect
! factory method.
The three dots, in lines 5 – 7, are the so-called parameter pack. 
! If the three dots (also called ellipsis) are on the left of Args , the parameter pack will be
! packed; if they are on the right of arg , the parameter pack will be unpacked.
In particular, the three dots in line 7 ( std::forward<Args>(args)... ) initiate
each constructor call that performs perfect forwarding, and the result is
impressive. Now, we can invoke the perfect factory method without any
arguments (line 38) or with three arguments (line 41).
*/
#include<iostream>
#include<string>
#include<utility>


template<typename T , typename ... Args>
T create(Args&& ... args)
{
    return T(std::forward<Args>(args)...);
}

struct MyStruct{
    MyStruct(int i, double d , std::string s){}
};

int main()
{
    //lvalue
    int five = 5;
    int myFive = create<int>(five);
    std::cout<<myFive<<"\n";

    std::string str{"lValue"};
    std::string str2 = create<std::string>(str);
    std::cout<<str2<<"\n";

    //rValue
    int myFive2 = create<int>(5);
    std::cout<<myFive2<<"\n";

    std::string str3 = create<std::string>(std::string("Rvalue"));
    std::cout<<str3<<"\n";

    std::string str4 = create<std::string>(std::move(str3));
    std::cout<<str4<<"\n";

    //Arbitrary number of arguments
    double doub = create<double>();
    std::cout<<doub<<"\n";
    MyStruct myStr = create<MyStruct>(2011,3.14,str4);

    typedef std::vector<int> IntVec;
    IntVec intVec = create<IntVec>(std::initializer_list<int>({1,2,3,4,5}));
    for (auto i = intVec.begin() ; i != intVec.end() ; ++i)
        std::cout<<*i<<"\n";

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MEMORY ALLOCATION
/*
! We can use the operators new and new[] to allocate memory and the
! operators delete and delete[] to deallocate memory.
!The compiler manages its memory automatically on the stack.
! Smart pointers manage memory automatically.
! The STL Containers and the C++ String automatically manage their memory.

*/

int* i = new int; //new causes memory allocation and object initialization. new returns a pointer to the corresponding object.
double* d = new double(10.0); //The arguments in the brackets go directly to the constructor.
Point* p = new Point(1.0,2.0); //If the class of dynamically created objects is part of a type hierarchy, more constructors are invoked.
double* d = new double[5]; //new[] allows us to allocate memory to a C array. 
Point* p  = new Point[10]; //The class of the allocated object must have a default constructor. The default constructor will be invoked for each element of the C array.


//placement new --> ! The header, <new> , is necessary. Can be overloaded on a class basis or globally.
/*
from stackoverflow-->Nothing in C++ prevents standard headers from including other standard headers. So if you include any standard header you might conceivably indirectly include all of them. However, this behaviour is totally implementation dependent, and if you need the features of a specific header you should always explicitly include it yourself.
*/

/*
use cases:
    ! Explicit memory allocation
    ! Avoidance of exceptions
    ! Debugging
*/
class Account{
    public:
        Account() = default;
    private:
        double a;
        double b;
};

int main()
{
    char* memory = new(std::nothrow) char[sizeof(Account)]; // nothrow gives nullptr instead of std::bad_alloc exception if the memory allocation operation fails
    std::cout<<sizeof(Account)<<"\n"; //16 bytes
    Account* a = new(memory) Account; //instantiate an object or a C array in a specific area of memory.
}

/*
New handler #

In the case of a failed allocation, we can use std::set_new_handler with our
own handler. std::set_new_handler returns the older handler and needs a
callable unit. A callable unit is typically a function, a function object, or a
lambda-function. The callable unit should take no arguments and return
nothing. We can get the handler currently being used by invoking the function
std::get_new_handler .

Our own handler allows us to implement special strategies for failed
allocations:
request more memory
terminate the program with std::terminate
throw an exception of type std::bad_alloc
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////