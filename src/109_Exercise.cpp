/* PDF 107

Problem statement #
The class hierarchy in the file was built as we have seen in the previous
example, following the famous template method design pattern. The typical
implementation of the template method pattern is to use NVI. NVI stands for
non-virtual interface, meaning the interface should not be virtual. NVI
requires non-virtual inheritance, which is not possible in Java or Python. Click
here for more details.
Refactor it with the help of override and final .

Explanation #
We have implemented three classes named Sort , QuickSort , and
BubbleSort .

We have created three private virtual methods and a public virtual
final method processData in the Sort class which calls the three private
methods.

The method SortData is pure virtual and defined in class Sort .

The classes QuickSort and BubbleSort publically inherit from the Sort
class.

We have overridden the methods of the Sort class in QuickSort .

We have overridden the method sortData of Sort class in BubbleSort .

By using a pointer to the Base class, we can access the overridden
methods of the derived class.



!ME: interesting question: https://stackoverflow.com/questions/2170688/private-virtual-method-in-c
! Herb Sutter has very nicely explained it here.

! Guideline #2: Prefer to make virtual functions private.

! This lets the derived classes override the function to customize the behavior as needed, without further exposing the virtual functions directly by making them callable by derived classes (as would be possible if the functions were just protected). The point is that virtual functions exist to allow customization; unless they also need to be invoked directly from within derived classes' code, there's no need to ever make them anything but private

! Another opposing answer!!!--> (Opposed to Herb Sutter quoted by Prasoon Saurav in his answer, the C++ FAQ Lite recommends against private virtuals, mostly because it often confuses people.)--> https://isocpp.org/wiki/faq/strange-inheritance#private-virtuals
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

// try using final and override

class QuickSort: public Sort{
    private:
        void readData() override 
        {
            std::cout<< "readData" << std::endl;
        }

        void sortData() override 
        {
            std::cout<< "sortData"<<std::endl;
        }

        void writeData() override 
        {
            std::cout<< "writeData"<<"\n";
        }
};


class BubbleSort: public Sort{
    private:
        void sortData() override{
            std::cout<<"sortData"<<"\n";
        }
};


int main()
{
    Sort* sort = new QuickSort;
    sort->processData();
    delete sort;
}