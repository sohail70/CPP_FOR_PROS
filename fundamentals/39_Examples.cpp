/*PDF 44
Copying and moving strings #

In the example above, we are demonstrating how the value of str1 can
be transferred to strings using the copy semantic and the move semantic.

In line 17, we have used the copy semantic and the string "ABCDEF" is
present in both str1 and str2 . We can say the value has been copied
from str1 to str3 .

In line 31, we have used the move semantic and now the string "ABCDEF"
is present only in str3 and not in str1 . We can say the value has moved
from str1 to str3 .


*/

#include<iostream>
#include<string>
#include<utility>


int main()
{
    std::string str1{"ABCDEF"};
    std::string str2;

    //initial value
    std::cout<<"1: "<<str1<<"\n";
    std::cout<<"2: "<<str2<<"\n";

    //copy semantic
    str2 = str1;
    std::cout<<"1': "<<str1<<"\n";
    std::cout<<"2': "<<str2<<"\n";


    std::string str3;

    //initial value
    std::cout<<"1: "<<str1<<"\n";
    std::cout<<"3: "<<str3<<"\n";

    //move sematic
    str3 = std::move(str1);
    std::cout<<"1': "<<str1<<"\n";
    std::cout<<"3': "<<str3<<"\n";
}