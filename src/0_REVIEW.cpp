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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////