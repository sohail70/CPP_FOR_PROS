/*PDF 44
BigArray

Explanation #
BigArray only supports copy semantic. This is a performance issue in line
53. The containers of the standard template library have copy-semantic.This means, that they want to copy all elements. If BigArray would have

this means, that they want to copy all elements. If BigArray would have
move-semantic implemented, move-semantic would have been used

automatically in line 53, because the constructor call,
BigArray(1000000000) , creates an rvalue.

*/

#include<algorithm>
#include<chrono>
#include<iostream>
#include<vector>


class BigArray
{
    public:
        BigArray(size_t len):len_(len),data_(new int[len]){}

        BigArray(const BigArray& other): len_(other.len_) , data_(new int[other.len_])
        {
            std::cout<<"Copy Constructor of" << other.len_ <<" elements "<<"\n";
            std::copy(other.data_ , other.data_ + len_ , data_);
        }

        BigArray& operator = (const BigArray& other)
        {
            std::cout<<"Copy Assignment " <<other.len_ <<" elements "<<"\n";

            if(this != &other)
            {
                delete[] data_;

                len_ = other.len_;
                data_ = new int [len_];
                std::copy(other.data_ , other.data_ + len_ , data_);
            }
            return *this;
        }

        ~BigArray()
        {
            if (data_ !=nullptr) delete[] data_;
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

    auto end = std::chrono::system_clock::now();
    //auto timeInSecond = std::chrono::duration<double>(end).count();
    auto timeInSecond = std::chrono::duration<double>(end-begin).count();
    std::cout<<timeInSecond<<"\n";

}