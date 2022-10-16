//calculating the sum of number in the range [start,end) --> we calculate with two threads --> first one from begin to mid and the second one from mid to end simultaneously
//everything will pass by value in std::thread unless you wrap it by std::ref --> & is not enough 
// std::thread create and start each thread
//join ---> waiting for the two threads to end ---> execution of main will be locked for this time period until they are done calculating 

//vase build kardan ---> g++ -g 01.cpp -o 01 -lpthread
#include<iostream>
#include<thread>
#include<vector>
#include<numeric>

void AccumulateRange(uint64_t& partial_sum ,uint64_t begin ,uint64_t end)
{
    partial_sum = 0;
    for(int i=begin ; i <end ; i++)
    {
        partial_sum+=i;
    }
}


template<class T>
void PrintVector(std::vector<T> input)
{
    for(auto n : input)
    {
        std::cout<<n<<" ";
    }
}


int main()
{
    const int number_of_threads =1000;
    const int number_of_elements = 1000*1000*1000;
    const int step = number_of_elements / number_of_threads;
    std::vector<std::thread> threads; //vector of threads
    std::vector<uint64_t> partial_sums(number_of_threads); //so we have partial_sums[0] and partial_sums[1] to store each thread calculation

    for(uint64_t i = 0 ; i<number_of_threads ; i++) //we create threads one by one
    {
        //The first param is the pointer to the function and the rest are the params that are passsed to the function 
        //All the params passed to this func Accumlate range are passed by value so use std::ref for pass by reference --> there is no return value so use std::ref
        threads.push_back(std::thread(AccumulateRange,std::ref(partial_sums[i]),i*step,(i+1)*step)); //partial_sums[i] is the thread i's output value the then i*step and (i+1)*step are begin and the end of the range
    }

    for(std::thread &t: threads)
    {
        if(t.joinable())
        {
            t.join(); //wait for all of them to joint
        }
    }

    uint64_t total = std::accumulate(partial_sums.begin(),partial_sums.end(),uint64_t(0)); //sum of the calculated numbers done by each thread
    
    PrintVector(partial_sums);

    std::cout<<total<<"\n";

}