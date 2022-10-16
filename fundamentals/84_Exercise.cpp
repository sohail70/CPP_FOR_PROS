/* PDF 85
Exercise #
Implement the functionality in the example we saw in the previous lesson
with the help of a lambda function.

Explanation #
First of all, the variable sum represents the state of the lambda function.

With C++14, the so-called initialization capture of lambdas is supported.
sum{0} declares and initializes a variable of type int which is only valid
in the scope of the lambda function.

! The lambda function is used in line 12. Note that they are constant by
! default.

&sum Stores the address of last updated value of sum .

*/

#include <algorithm>
#include <iostream>
#include <vector>


int main(){
    std::cout << std::endl;
    std::vector<int> intVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // Use a lambda function here and class sumMe is no longer needed
    int sum {0};
    std::for_each(intVec.begin(), intVec.end(), [&sum](int x) {sum+=x;}); //! ME: if you use sum instead of &sum you must use mutable keyword before lambda body--> reason: First, the type of a lambda expression, which has capture, is a class type (5.1.2 Lambda expressions [expr.prim.lambda] #3) That type has an operator() which is by default const, unless mutable is used in the lambda expression ([expr.prim.lambda] #5) -->source:https://stackoverflow.com/questions/13699515/copied-const-object-in-lambda-closure-not-mutable -->note that the result is not right if you don't use &sum because for_each function ignores the return value of the lambda body as its stated in the for_each function
    //! use this too: https://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11  -->  The generated operator() is const by default, with the implication that captures will be const when you access them by default. This has the effect that each call with the same input would produce the same result, however you can mark the lambda as mutable to request that the operator() that is produced is not const.
    //! check this site for reasons: https://www.cplusplus.com/forum/general/279685/
    std::cout << "sum: " << sum << std::endl;
    std::cout << std::endl;

}