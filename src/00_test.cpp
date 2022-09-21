/* PDF 45
Exercise 2
Extend BigArray with the move semantic and measure the performance once
more. How big is the performance gain?

In lines 37 – 41, we have defined the move constructor for BigArray . Note
that in line 40, we are explicitly setting other.data_ to nullptr after the
elements have been moved into the new object

In lines 43 – 55, we have defined the move assignment operator, = , for
BigArray . Note that in line 51, we are explicitly setting other.data_ to
nullptr after the elements have been moved.

As we can see, move semantic is significantly faster than the copy
semantic since we are only redirecting the pointer to another vector and
assigning the correct size . To be more precise, the costs of move
semantics are independent of the size of the data structure. This does not
hold true for the copy semantic. The bigger the user-defined data
structure, the more expensive the memory allocation.


good explanation for move : https://stackoverflow.com/questions/27497830/move-constructor-and-stdmove-confusion
*/

#include<iostream>
#include<chrono>
#include<vector>
#include<ostream>




class BigArray
{   
    public:
        BigArray(size_t len):len_(len) , data_(new int[len]){}
        
    explicit BigArray(const BigArray& other): len_(other.len_), data_(new int[other.len_]){
        std::cout << "Copy construction of " << other.len_ << " elements "<< std::endl;
        std::copy(other.data_, other.data_ + len_, data_);
    }
    BigArray& operator=(const BigArray& other){
        std::cout << "Copy assignment of " << other.len_ << " elements "<< std::endl;
        if (this != &other){
            delete[] data_;
            len_ = other.len_;
            data_ = new int[len_];
            std::copy(other.data_, other.data_ + len_, data_);
        }
        return *this;
    }


        //Move constructor
        BigArray(BigArray&& other): len_(other.len_),data_(other.data_)
        {
            std::cout<<"Move Constructor of "<<other.len_<<" elements"<<"\n";
            other.len_ = 0;
            other.data_ = nullptr;
        }
        BigArray& operator = (BigArray&& other)
        {
            std::cout<<"Move assignment of"<< other.len_ <<" elements"<<"\n";
            if(this != &other)
            {
                delete [] data_;

                len_ = other.len_;
                data_ = other.data_;

                other.data_ = nullptr;
                other.len_ = 0;
            }
            return *this;
        }


        friend std::ostream& operator<<(std::ostream& out, const BigArray& other)
        {

            out << other.data_<<"\n";
            return out;
        }

        ~BigArray()
        {
            if (data_ != nullptr) delete[] data_;
        }

    private:
        size_t len_;
        int* data_;

};


int main()
{
    std::vector<BigArray> myVec;
    myVec.push_back(BigArray(10));
    myVec.push_back(BigArray(4));

    std::vector<BigArray> myVec2 = std::move(myVec);
    //myVec2 = ;
    
    for(std::vector<BigArray>::iterator i = myVec.begin() ; i != myVec.end() ; i++)
    {
        std::cout<<*i<<"\n";
    }
   std::cout<<"\n";
}

