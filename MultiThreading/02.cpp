//creating threads using function objects
#include<iostream>
#include<thread>
#include<vector>
#include<numeric>

class AccumulateRange{
    public:
        void operator()(uint64_t begin , uint64_t end)
        {
            partial_sum = 0;
            for(int i = begin ; i<end ; i++)
            {
                partial_sum+=i;
            }
            std::cout<<partial_sum<<"\n";
        }
    
    uint64_t partial_sum;
};



int main()
{
    const int number_of_threads =5;
    const int number_of_elements = 1000*1000*1000;
    const int step = number_of_elements / number_of_threads;
    std::vector<std::thread> threads; 
    std::vector<AccumulateRange *> functors; //instead of vector of partial sums we are goona put those partial sums inside the function object so we need the function objects to access the partial sum of each thread
    for(uint64_t i = 0 ; i<number_of_threads ; i++) //we create threads one by one
    {
        AccumulateRange* functor = new AccumulateRange();
        threads.push_back(std::thread(std::ref(*functor),i*step,(i+1)*step));
        functors.push_back(functor);
    }

    for(std::thread &t: threads)
    {
        if(t.joinable())
        {
            t.join(); 
        }
    }

    int64_t total = 0;
    for(auto pf : functors)
    {
        total += pf->partial_sum;
    }

    std::cout<<total<<"\n";

}