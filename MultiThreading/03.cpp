//threads using lambda function


#include<iostream>
#include<thread>
#include<vector>
#include<numeric>


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
    const int number_of_threads =5;
    const int number_of_elements = 1000*1000*1000;
    const int step = number_of_elements / number_of_threads;
    std::vector<std::thread> threads; 
    std::vector<uint64_t> partial_sums(number_of_threads); 

    for(uint64_t i = 0 ; i<number_of_threads ; i++) 
    {
       threads.push_back(std::thread([i,&partial_sums,step]
       {
           for(uint64_t j = i*step ; j <(i+1)*step ; j++)
           {
               partial_sums[i] +=j;
           }
       }
       ));
    }

    for(std::thread &t: threads)
    {
        if(t.joinable())
        {
            t.join(); 
        }
    }

    uint64_t total = std::accumulate(partial_sums.begin() , partial_sums.end() , uint64_t(0));
    PrintVector(partial_sums);
    std::cout<<total<<"\n";

}