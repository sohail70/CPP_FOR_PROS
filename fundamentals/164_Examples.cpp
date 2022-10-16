/* PDF 160

Example 1 #
To get a visual idea of the life cycle of the resource, there is a short message in
the constructor and destructor of MyInt (lines 8 - 16).


Explanation #

In line 22, we create MyInt(1998) , which is the resource that the smart
pointer should address. By using sharPtr->val , we have direct access to
the resource (line 23).

The output of the program shows the number of references counted. It
starts in line 24 with 1. It then has a local copy shartPtr in line 28 and
goes to 2. The program then returns to 1 after the block (lines 27-30).

! The copy assignment call in line 33 modifies the reference counter. The
! expression sharPtr= shared_ptr<MyInt>(new MyInt(2011) in line 38 is more
! interesting.

! First, the resource MyInt(2011) is created in line 38 and assigned to
! sharPtr . Consequently, the destructor of sharPtr is invoked. sharedPtr
! was the exclusive owner of the resource new MyInt(1998) (line 22).

The last new resource MyInt(2011) will be destroyed at the end of main.


*/


#include<iostream>
#include<memory>

using std::shared_ptr;

struct MyInt
{
    MyInt(int v): val(v){
        std::cout<<" Hello "<<val<<"\n";
    }
    ~MyInt(){
        std::cout<<" Goodbye "<< val<<"\n";
    }
    int val;
};

int main()
{
    shared_ptr<MyInt> sharPtr(new MyInt(1998));
    std::cout<< " My value "<< sharPtr->val <<"\n";
    std::cout<<" sharPtr.use_count() "<<sharPtr.use_count()<<"\n";


    {
        shared_ptr<MyInt> locSharPtr(sharPtr);
        std::cout<<"locSharePtr.use_count(): "<< locSharPtr.use_count()<<"\n";
    }
    std::cout << "sharPtr.use_count(): "<< sharPtr.use_count() << std::endl;
    
    shared_ptr<MyInt> globSharPtr =  sharPtr;
    std::cout<<"sharPtr.use_count(): "<<sharPtr.use_count()<<"\n";
    globSharPtr.reset();
    std::cout<<"sharPtr.use_count() "<<sharPtr.use_count()<<"\n";

    sharPtr = shared_ptr<MyInt>(new MyInt(2011));




}
