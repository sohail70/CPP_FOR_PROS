/* PDF 38 - Exercises

Exercise 1 #
Use the structure, MyDouble , in our program. How can we check that instances
of MyDouble will be created at compile-time?
ME: USE static_assert to see if it's been calculated in compile time or not

Exercise 2 #
What will happen if we instantiate MyDouble with a non-constant expression?
static_assert gives error in that case
*/





#include<iostream>


struct MyDouble{
    double myVal;
    constexpr MyDouble(double v):myVal(v){}
    constexpr double getVal(){return myVal;}
};


int main()
{
    constexpr MyDouble dou(2);
    static_assert(dou.myVal==2);
}