/* PDF 32
initializer list

! Special Rule: If we use automatic type deduction with auto in
! combination with an {}-initialization, we will get a
! std::initializer_list in C++14.
! so In C++14, auto with std::initializer_list always gives an initializer_list .
auto a = {42};      //std::initializer_list<int>
auto b{42};      //std::initializer_list<int>
auto c = {1,2};    //std::initializer_list<int>
auto d{1,2};    //std::initializer_list<int>

!With C++17, the rules are more complicated yet intuitive:
auto a = {42};      //std::initializer_list<int>
auto b{42};      //int
auto c = {1,2};    //std::initializer_list<int>
auto d{1,2};    //error, too many


*/

#include<initializer_list>
#include<iostream>
#include<string>


class MyData{
    public:
        MyData(std::string , int){ //classical constructor
            std::cout << "MyData(std::string, int)" << std::endl;
        }

        MyData(int , int) { //classical constructor
            std::cout << "MyData(int, int)" << std::endl;
        }

        MyData(std::initializer_list<int>) // sequence constructor: The sequence constructor is a constructor that takes an std::initalizer_list .
        {
            std::cout << "MyData(std::initializer_list<int>)" << std::endl;
        }
};

template<typename T>
void printInitializerList(std::initializer_list<T> inList)
{
    for (auto& e:inList) std::cout<<e<<" ";
    std::cout<<"\n";
}


int main()
{
    //! sequence constructor has a higher probability
    MyData{1,2};//When we invoke the constructor with curly braces such as in line 31, the sequence constructor from line 16 is used first.

    //invoke the classical constructor explicitly
    MyData(1,2);

    //use the classical constructor
    MyData{"dummy",2};

    printInitializerList({1,2,3,4,5,6,7,8,9});

    printInitializerList({"only","for","testing","purpose."});

}