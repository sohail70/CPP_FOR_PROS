// using std::async to create threads --> executed asynchronosly now --> now we can have return value but std::thread didn't have return value
//use get() function for the return value ---> t.get()
//std async return value is std::future --> don't get intimidated it just means the value of this type comes in the future namely after calling t.get()
//you can use functor and lambdas as an exercise

#include<iostream>
#include<thread>
#include<vector>
#include<numeric>
#include<future>


uint64_t GetRangeSum(uint64_t  start , uint64_t end)
{
    uint64_t sum = 0;
    for(uint64_t i = start ; i <end ; i++)
    {
        sum+=i;
    }
    return sum;
}

int main()
{
    const int number_of_threads =50;
    const int number_of_elements = 1000*1000*1000;
    const int step = number_of_elements / number_of_threads;
    std::vector<std::future<uint64_t>> tasks; //vector of tasks //each future type is the return type of the function GetRangeSum
    
    for(uint64_t i = 0 ; i<number_of_threads ; i++) //create, start, and push each tasks into a vector
    {
        tasks.push_back(std::async(GetRangeSum , i*step , (i+1)*step));
    }


    uint64_t total = 0;
    for(auto &t : tasks)
    {
        auto p = t.get();
        total += p; //wait for tasks to end and read return values. so it locks the main
        std::cout<<p<<"\n";
    }

    std::cout<<total<<"\n";

}


/*
Take away:
tasks are created using std async
future--> the returned value from std async-->we get futures value by calling get()
if the future values are not ready the main thread block until the future value becomes ready (similar to join())

promise --> return value of the function passed to std::async--> for the most part you don't need to know details of std::promise or define any varibale of type std::promise. The c++ library does that behind the scenes
each task by default starts as soon as it is created (check std::async docs)

*/


/*
Thread ---> create using std::thread --> doesn't return a value
Tasks --> create using std::async ---> return a value 
Both can use --> pointer to function - functor - lambda functions

*/

/*
end of lesson 1
*/