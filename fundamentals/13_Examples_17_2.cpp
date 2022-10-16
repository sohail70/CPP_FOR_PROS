//Advanced types
/*
This makes auto a very useful feature since determining or declaring the
types for different libraries can be a cumbersome task.
After this exercise, it is clear how helpful auto is in making our program
clean and safe.
There is a high potential for error if we keep defining types explicitly. Hence,
it’s better to leave it to the compiler. It’ll save us time as well.

*/
#include <chrono>
#include<future>
#include<map>
#include<string>
#include<tuple>



int main()
{
    auto myInts = {1,2,3}; //---> use #include<initializer_list> if you don't want to use auto
    auto myIntBegin = myInts.begin(); //std::initializer_list<int>::iterator  

    std::map<int , std::string> myMap = { {1,std::string("one")} , {2,std::string("two")} };
    auto myMapBegin = myMap.begin(); //std::map<int, std::string>::iterator

    auto func = [](const std::string& a){return a;}; //std::function< std::string(const std::string&) > func= [](const std::string& a){ return a;}  ---> use #include<functinoal>
    //auto futureLambda   = std::async([](const std::string& s ) {return std::string("Hello ") + s;})  //std::future<std::string> futureLambda= std::async([](const std::string& s ) {return std::st
    auto begin = std::chrono::system_clock::now();// std::chrono::time_point<std::chrono::system_clock> begin = ...

    auto pa = std::make_pair(1,std::string("second")); //std::pair<int, std::string> pa = std::make_pair(1, std::string("second"));

    auto tup = std::make_tuple(std::string("first") , 4 ,1.1 , true , 'a'); //std::tuple<std::string, int, double, bool, char> tup = std::make_tuple(std::string("second"...


}