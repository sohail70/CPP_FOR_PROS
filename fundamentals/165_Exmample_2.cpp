/*  PDF 160
Example 2 #
We can quite easily push std::shared_ptr onto an
std::vector<std::shared_ptr<int>> with different deleters. The special deleter
will be stored in the control block.

In this example, we create a special std::shared_ptr that logs how muchmemory has already been released.

Explanation #
In lines 8 - 24, Deleter is the special deleter. The deleter is parametrized
by the type T . It counts, alongside the static variable count (line 23), how
often the call operator (lines 11 - 14) was used.

Deleter returns all the information with getInfo (lines 15-21).

The function createRandomNumbers (lines 32-42) creates between 1 to 1000
std::shared_ptr (line 40) parametrized by the special deleter
intDeleter() .

The first usage of intDeleter->getInfo() shows that no resource has been
released. This changes with the call sharedPtr2.reset() in line 53.

An int variable with 4 bytes has been released. The call
createRandomNumbers() , in line 57, creates 74 std::shared_ptr<int> .

Of course, we can use the deleter for an std::unique_ptr (line 60 - 68).

The memory for the double objects will be released after the end of the
block, in line 68.



from the internet --> watch https://www.youtube.com/watch?v=bVhNu7h-3wM
------------------

The classic issue of smart pointers using a reference count is to have cyclic
references. Therefore, std::weak_ptr solves our problems. In the next lesson,
we will take a closer look at std::weak_ptr and show how to break cyclic
references.
*/

#include<iostream>
#include<memory>
#include<random>
#include<typeinfo>


template<typename T>
class Deleter{
    public:
        void operator()(T* ptr)
        {
            ++Deleter::count;
            delete ptr;
        }

        void getInfo()
        {
            std::string typeId{typeid(T).name()};
            size_t sz = Deleter::count * sizeof(T);
            std::cout<<" Deleted "<<Deleter::count<<" objects of type: "<<typeId<<"\n";
            std::cout<<"Freed size in bytes "<<sz <<"\n";
            std::cout<<"\n";
        }
    private:
        static int count;
};

template<typename T>
int Deleter<T>::count=0;

typedef Deleter<int> IntDeleter;
typedef Deleter<double> DoubleDeleter;

void createRandomNumbers(){
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> thousand(1,1000);
    int ranNumber = thousand(engine);
    for(int i = 0 ;i<=ranNumber;++i) std::shared_ptr<int>(new int(i),IntDeleter());
}

int main()
{
    {
        std::shared_ptr<int> sharedPtr1(new int , IntDeleter()); // IntDeleter() -->  the () is overloaded in the functor
        std::shared_ptr<int> sharedPtr2(new int,IntDeleter());
        auto intDeleter = std::get_deleter<IntDeleter>(sharedPtr1);
        intDeleter->getInfo();
        sharedPtr2.reset();
        intDeleter->getInfo();
    }

    createRandomNumbers();
    IntDeleter().getInfo();

    {
        std::unique_ptr<double,DoubleDeleter> uniquePtr(new double , DoubleDeleter());

        std::unique_ptr<double,DoubleDeleter> uniquePtr1(new double,DoubleDeleter());
        std::shared_ptr<double> sharedPtr(new double , DoubleDeleter());

        std::shared_ptr<double> sharedPtr4(std::move(uniquePtr));
        std::shared_ptr<double> sharedPtr5 = std::move(uniquePtr1);
        DoubleDeleter().getInfo();
    }

    DoubleDeleter().getInfo();
}