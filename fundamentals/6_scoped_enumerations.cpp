//classical versus strongly-typed enumerations. Commonly, these are known as unscoped and scoped enumerations, respectively.

/*
Drawbacks of enumerations in classical C++ 
1. Enumerators implicitly convert to int .
2. Enumerators in the enclosing scope.
3. The type of the enumeration cannot be specified-->Enumerations cannot be forward declared because their
    type is unknown. There is only one guarantee for enumerations in classical
    C++: the type must be integral and big enough to hold the enumerator values.
*/



/*
Strongly-typed enumerations :
Scoped enumerations are often called strongly-typed enumerations. The
strongly-typed enumerations have to follow stronger rules:
1. The enumerators can only be accessed in the scope of the enumeration.
2. The enumerators don’t implicitly convert to int .
3. The enumerators aren’t imported into the enclosing scope.
4. The type of the enumerators is by default int . Therefore, we can forward
declare the enumeration.
The syntactical difference between classic enumerations and strongly-typed
enumerations is minimal. Strongly-typed enumerations additionally use the
keywords class or struct .
If we want to use an enumerator as an int , we must explicitly convert it with
static_cast .

We can explicitly specify the type of enumerators. By default, it’s int .
But that does not have to be. We can use integral types like bool , char , short
int , long int , or, long long int . Read msdn.microsoft.com for the details.
See the post Check types for information on how to check if a type is integral
at compile time.
We can use the scoped property and the explicit type specification of an
enumeration independently. Depending on the base types, the enumerations
can have different sizes.
*/

#include<iostream>
enum class Color1{ //The size is 4 because default type of the eunm is int. but isn't it supposed to be 4*3=12 ?
    red,
    blue,
    green,
};


enum struct Color2: char{
    red=100,
    blue, //101
    green //102
};



void useMe(Color2 _color2)
{
    switch (_color2)
    {
        case Color2::red:
            std::cout<<"Color2::red"<<"\n";
            break;
        case Color2::blue:
            std::cout<<"Color2::blue"<<"\n";
            break;
        case Color2::green:
            std::cout<<"Color2::green"<<"\n";
            break;
    }
}


int main()
{

    enum Color{red=0,green=2,blue}; //so blue is 3
    std::cout<<red<<" "<<green<<" "<<blue<<"\n";
    
    int red2 = red;
    std::cout<<red2<<"\n";
    //int red = 5; //ERROR
    std::cout<<"////////////////////////////////////////////////"<<"\n";


    enum oldEnum{
        one=1,
        ten=10,
        hundred=100,
        thousand=1000
    };

    enum struct newEnum{
        one=1,
        ten=10,
        hundred=100,
        thousand=1000
    };

    std::cout<<2*thousand + 0*hundred + 1*ten + 1*one<<"\n";
    std::cout<<2*static_cast<int>(newEnum::thousand) +
                0*static_cast<int>(newEnum::hundred) +
                1*static_cast<int>(newEnum::ten) +
                1*static_cast<int> (newEnum::one) <<"\n";

    std::cout<<"////////////////////////////////////////////////"<<"\n";

    std::cout<<static_cast<double>(Color1::red)<<"\n";
    std::cout<<static_cast<double>(Color2::red)<<"\n";

    std::cout<<sizeof(Color1)<<"\n";
    std::cout<<sizeof(Color2)<<"\n";

    Color2 color2red{Color2::red};
    useMe(color2red);



}