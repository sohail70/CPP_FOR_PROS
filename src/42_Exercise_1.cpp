/* PDF 45
Exercise 1 #
In the program below, a BigArray with 10 billion entries will be pushed to a
std::vector .
Compile the program and measure its performance.

*/


#include<algorithm>
#include<chrono>
#include<iostream>
#include<vector>




class BigArray
{
    public:
        BigArray(size_t len): len_(len) , data_(new int[len]){}

        BigArray(const BigArray& other): len_(other.len_) , data_(new int[other.len_])
        {
            std::cout<<"Copy constructor of "<<other.len_ <<" elements"<<"\n";
            std::copy(other.data_ , other.data_ + len_ , data_);
        }

        BigArray& operator = (const BigArray& other)
        {
            std::cout<<"Copy assignment of "<< other.len_ << " elements" <<"\n";
            if (this !=  &other)
            {
                delete[] data_;
                len_ = other.len_;
                data_ = new int[len_];
                std::copy(other.data_ , other.data_ + len_ , data_);
            }
            return *this;
        }


    private:
        size_t len_;
        int* data_;
};


int main()
{
    std::vector<BigArray> myVec;
    auto begin = std::chrono::system_clock::now();

    myVec.push_back(BigArray(1000000000));

    auto end = std::chrono::system_clock::now() - begin;
    auto timeInSeconds = std::chrono::duration<double>(end).count();

    std::cout<<timeInSeconds<<"\n";
}