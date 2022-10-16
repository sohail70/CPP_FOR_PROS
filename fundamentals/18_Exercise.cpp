/* PDF 23
! compiler performs implicit casts during operations
Let’s get used to the rules of implicit type casts by arithmetic operations. Call
the add function that we studied earlier with different arguments and ask for
the return type of each operation with typeid .
*/


#include <iostream>
#include <typeinfo>

template<typename T1, typename T2>
auto add(T1 first, T2 second) -> decltype(first + second){
    return first + second;
}

int main(){
    //various arithmetic operations that get implicitly cast to the int data type.
    //When booleans and integers are operated together, the result is a cast to int .
    std::cout<<typeid(add(1,false)).name() <<std::endl;
    std::cout<<typeid(add('a',1)).name() <<"\n";
    std::cout<<typeid(add(false,false)).name()<<"\n";
    //From lines 19 to 20, we can see arithmetic operations that get implicitly cast to the double data type. The result of arithmetic operations between integers and doubles is a double.
    std::cout<<typeid(add(true,3.14)).name()<<"\n";
    std::cout<<typeid(add(1,4.0)).name()<<"\n";
}