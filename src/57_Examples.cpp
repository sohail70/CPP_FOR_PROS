/* PDF 61
Lambdas with a vector #

Explanation #
We have created a lessLength() function on line 7 that returns true if
the first string is smaller than the second one in length.

This function can be used as the sorting criteria for std::sort on line 25.
However, the lambda on line 35 performs the same task in a simpler way.

As we can see, the parameters of the lambda are the same as those of the
defined function.

In line 30, the operator() method of the GreaterLength() class is being
used to sort the vector in descending order. However, this could also
have been done using a lambda similar to the one on line 35.

*/



#include<algorithm>
#include<iostream>
#include<iterator>
#include<string>
#include<vector>

bool lessLength(const std::string& f , const std::string& s)
{
    return f.length() <s.length();
}

class GreaterLength
{
    public:
        bool operator()(const std::string& f, const std::string& s) const
        {
            return f.length() > s.length();
        }
};

int main()
{
    //initializing with a initializer lists
    std::vector<std::string> myStrVec {"12345" , "123456" , "1234" , "1" , "12", "123", "12345"};
    std::cout<<"\n";

    //sorting with the function
    std::sort(myStrVec.begin() , myStrVec.end() , lessLength);
    std::copy(myStrVec.begin(), myStrVec.end() , std::ostream_iterator<std::string>(std::cout,"\n"));
    std::cout << "\n";

    //sorting in reverse with the function object
    std::sort(myStrVec.begin() , myStrVec.end() , GreaterLength());
    std::copy(myStrVec.begin() , myStrVec.end() , std::ostream_iterator<std::string>(std::cout,"\n"));  
    std::cout << "\n";

    //sorting with the lambda function
    std::sort(myStrVec.begin() , myStrVec.end() , [](const std::string& f , const std::string& s){return f.length() > s.length();});
    std::copy(myStrVec.begin() , myStrVec.end() , std::ostream_iterator<std::string>(std::cout,"\n"));
    std::cout << "\n";

    // using the lambda function for output
    std::for_each(myStrVec.begin() , myStrVec.end() , [](const std::string& s){std::cout<<s<<"\n";});
}