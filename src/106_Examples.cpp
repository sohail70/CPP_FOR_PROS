/*   PDF 106
A good question that I came accros: https://www.daniweb.com/programming/software-development/threads/450593/class-members-on-stack-or-heap
https://stackoverflow.com/questions/11477523/when-and-why-to-declare-member-variables-on-the-heap-c


Example 1: Override final #

Explanation #
! We have implemented two classes named Sort and QuickSort .

! We have created three private virtual methods and a public virtual
! method processData in the Sort class which calls the three private
! methods.

! The QuickSort class publicly inherits from the Sort class.

! We have overridden the methods of the Sort class in QuickSort .

! By using a pointer to the Base class, we can access the overridden
! methods of the derived class.


*/




#include<iostream>

class Sort{
    public:
        virtual void processData()
        {
            readData();
            sortData();
            writeData();
        }
    private:
        virtual void readData(){}
        virtual void sortData() = 0;
        virtual void writeData(){}
};


class QuickSort: public Sort{
    private:
        void readData()
        {
            std::cout<<"readData"<<"\n";
        }
        void sortData()
        {
            std::cout<<"sortData"<<"\n";
        }
        void writeData()
        {
            std::cout<<"writeData"<<"\n";
        }
};


int main()
{
    Sort* sort = new QuickSort;
    sort->processData();
    
}