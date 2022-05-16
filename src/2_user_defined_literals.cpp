/*
User-defined literals are a unique feature in all mainstream programming
languages. They empower us to combine values with units.
User-defined literals must obey the following syntax:
<built_in-Literal> + _ + <Suffix>
Usually, we use the suffix for a unit: 
123.45_km // Floating point numbers
'1'_character // Character literals
The C++ runtime maps the user-defined literal onto the corresponding literal
operator
The compiler maps the user-defined literal 0101001000_b to the
literal operator operator"" _b(long long int bin)
c++11: There has to be a space between the quotation marks ( "" ) and the underscore
with suffix ( _b ). We have the binary value ( 0101001000 ) in the variable bin .

c++14: no need for space . it is possible to use reserved keywords like _C as a suffix
The simple rule in
C++14 is that we can use suffixes starting with an uppercase letter

Thanks to the automatic mapping of user-
defined literals to literal operators we can implement type-safe arithmetic.
The compiler ensures that it is impossible to add apples and pears.
*/
///////////////////////////////
/*
built in literals: 
for binary
numbers, C++ strings, complex numbers, and time units
std::chrono

built-in literals have no underscore
For the first time, in C++14, string literals are supported. In the
past C++ only supported C-string literals, meaning that we had to always use aC-string literal to initialize a C++ string.
*/
////////////////////////////////
/*
The literal operator:
1.45_km => operator "" _km(1.45)

One thing to keep in mind is that there has to be a space between "" and
_km . Also, user-defined literals should start with an underscore ( _km ) to
distinguish them from the built-in literals.


The data type character has the form
character_suffix . An example is 's'_c . The compiler tries to invoke the
literal operator operator"" _c('s') . The character in this case is of the type
char .
In addition to the char data type, C++ supports the data types wchar_t ,
char16_t , and char32_t . We can use these types as the base for our C string. I
used a char in the table. The table shows that the compiler maps the C string
"hi"_i18n to the literal operator operator"" _i18n("hi",2) . 2 is the length of
the C string.

The compiler can map integers or floating point numbers to integers
( unsigned long long int ) or floating point numbers ( long double ), but the
compiler can also map them both to C strings. The first variant is the cooked
form, whereas the second variant is the raw form. The compiler will use the
raw form if the literal operator wants its arguments as a C string. If not, it uses
the cooked form. If we implement both versions, the compiler will choose the
cooked form since it has a higher priority.


*/
////////////////////////////////////////////////////
//////////////user defined literals/////////////////
////////////////////////////////////////////////////
#include<iostream>
#include<ostream>


/*
We should use namespaces for user-defined literals because name
collisions are very likely, for two reasons. First, the suffixes are usually
very short; second, the suffixes usually stand for units which are already
established abbreviations. In the program, we used the suffixes km , m ,
dm and cm .
*/
namespace Distance
{
    class MyDistance
    {
        public:
            MyDistance(double i):m(i){}

        //overloaded the basic arithmetic operators
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
            double m; //distance in meters
    };


    namespace Unit
    {
        MyDistance operator "" _km(long double d) //note the space between "" and _km
        {
            return MyDistance(1000*d); //conversion of km to meters
        }
        MyDistance operator "" _m(long double m)
        {
            return MyDistance(m);
        }
        MyDistance operator "" _cm(long double d)
        {
            return MyDistance(d/100); //conversion of cm to meters
        }
    }
}

using namespace Distance::Unit;
int main()
{
    std::cout<<"1 kilometer is :"<<1.0_km <<"\n";
    std::cout<<"3 kilometer is :"<<1.0_km + 2.0_km<<"\n"; 
    std::cout<<"1.2 kilometer and 100 meter and 15 cm is "<<1.2_km+100.0_m+15.0_cm<<"\n"; //The compiler takes care of the calculations for all units.
}
