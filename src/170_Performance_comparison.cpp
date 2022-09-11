/*  PDF 167
In this lesson, we will try a simple performance comparison test for various smart pointers.

A simple performance test should give an idea of the overall performance.
Run the code in the tabs below to see the performance of each pointer.

*/

#include<chrono>
#include<iostream>
#include<memory>
static const long long numInt = 100000000;

int main()
{
    auto start = std::chrono::system_clock::now();

    for (long long i = 0; i <numInt ; ++i)
    {
        //int* tmp(new int(i));
        //delete tmp;
        //std::shared_ptr<int> tmp(new int(i));
       //std::shared_ptr<int> tmp(std::make_shared<int>(i));
        //std::unique_ptr<int> tmp(new int(i));
        std::unique_ptr<int> tmp(std::make_unique<int>(i));
    }

    std::chrono::duration<double> dur = std::chrono::system_clock::now()-start;
    std::cout<<"time native: "<< dur.count()<<" seconds"<<"\n";


}