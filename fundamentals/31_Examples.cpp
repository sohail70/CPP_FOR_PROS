/* PDF 37
Assertions
*/
#include<iostream>

constexpr int square(int x){return x*x;}
constexpr int squareToSquare(int x){return square(square(x));}

int main()
{
    //! The assertions in lines 10 and 11 will hold because they can be evaluated
    //! at compile-time. Making it a constexpr variable will allow the code
    //! compilation to pass the assertions.
    static_assert(square(10)==100 , "You calculated it wrong");
    static_assert(squareToSquare(10) == 10000 , "You calculated it wrong");

    std::cout<<square(10)<<"\n";
    std::cout<<squareToSquare(10)<<"\n";
    
    constexpr int constExpr = square(10);

    int arrayClassic[100];
    int arrayWithConstExpression[constExpr];
    int arrayWithConstExpressionFunction[square(10)]; //Notice that the input argument for this function call is constant.

}