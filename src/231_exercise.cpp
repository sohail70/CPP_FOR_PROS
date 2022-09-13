/* PDF 231
Use std::accumulate to add numbers, multiply numbers and concatenate
strings.


Explanation #We have created a vector that we initialized with integers ranging from 1
to 9.
In line 11, we have used std::accumulate to sum up all values from 1 to 9.
In line 14, we have used std::accumulate to multiply all the elements
using a lambda function.
In lines 19 and 20, we have used std::accumulate to print all the elements
of the vector containing strings.

*/


#include<iostream>
#include<numeric>
#include<vector>

int main()
{
    std::vector<int> vec {1,2,3,4,5};
    auto res = std::accumulate(vec.begin(),vec.end(),0,[](int a, int b){return a+b;});
    std::cout<<res<<"\n";

    auto res2 = std::accumulate(vec.begin(),vec.end(),1,[](int a, int b){return a*b;});
    std::cout<<res2<<"\n";

    std::vector<std::string> strVec2{"Only","for","testing","purpose"};
    std::string res3 = std::accumulate(strVec2.begin()+1,strVec2.end(),strVec2[0],[](auto fir , auto sec){return fir+":"+sec;});

    std::cout<<res3<<"\n";
    std::cout<<std::endl;
}