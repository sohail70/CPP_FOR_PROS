///SMART POINTERS
/*
Smart pointers manage their resources according to the RAII idiom (Resource Acquisition Is Initialization).
Therefore, the resource is automatically released if the smart pointer goes out
of scope.This means that the memory for the smart pointer is allocated in the
constructor and deallocated in the destructor. We can use this technique
in C++ because the destructor is called when the object goes out of scope.


std::unique_ptr C++11
Owns exclusively the resource. Can’t be copied.

std::shared_ptr C++11
Has a reference counter for the shared variable. Manages the reference counter automatically. Deletes the resource, if the reference counter is 0.


std::weak_ptr C++11
Helps to break cycles of std::shared_ptr Doesn’t modify the reference counter.


*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///UNIQUE POINTER ---> It limits access to its resource, thereby maintaining smart pointer's privacy
/*
! An std::unique_ptr automatically and exclusively manages the lifetime of its
! resource according to the RAII idiom. std::unique_ptr should be our first
! choice since it functions without memory or performance overhead.
! std::unique_ptr exclusively controls its resource. It automatically releases the
! resource if it goes out of scope. No copy semantics are required, and it can be
! used in containers and algorithms of the Standard Template Library.
! std::unique_ptr is as cheap and fast as a raw pointer when no special delete
! function is used.

Characteristics #
The std::unique_ptr :
! can be instantiated with and without a resource.
! manages the life cycle of a single object or an array of objects.
! transparently offers the interface of the underlying resource.
! can be parametrized with its own deleter function.
! can be moved (move semantics).
! can be created with the helper function std::make_unique .


Methods #
These are the methods of std::unique_ptr :

! get --> Returns a pointer to the resource.
! get_deleter --> Returns the delete function.
! release --> Returns a pointer to the resource release and releases it.
! reset --> Resets the resource.
! swap --> Swaps the resources.

Special Deleters #
std::unique_ptr can be parametrized with special deleters:
std::unique_ptr<int, MyIntDeleter> up(new int(2011), myIntDeleter()) .
std::unique_ptr uses, by default, the deleter of the resource.


std::make_unique #
! The helper function std::make_unique was unlike its sibling std::make_shared,
! and was forgotten" in the C++11 standard. Therefore, std::make_unique was
! added with the C++14 standard. std::make_unique enables us to create an
! std::unique_ptr in a single step:
std::unique_ptr<int> uniqPtr1 = std::make_unique<int>(2011);
auto uniqPtr2 = std::make_unqiue<int>(2014);


! Always use std::make_unique.
! If we use:
func(std::make_unique<int>(2014), functionMayThrow());
func(std::unique_ptr<int>(new int(2011)), functionMayThrow());
! and functionMayThrow throws, we have a memory leak with new int(2011) for
! this possible sequence of calls:
new int(2011)
functionMayThrow()
std::unique_ptr<int>(...)


! Rarely, when we create std::unique_ptr in an expression and the compiler
! optimizes this expression, a memory leak may occur with an std::unique_ptr
! call. Using std::make_unique guarantees that no memory leak will occur.



Under the hood, std::unique_ptr uses the perfect forwarding pattern. The
same holds for the other factory methods such as std::make_shared ,
std::make_tuple , std::make_pair , or an std::thread constructor.


! The key question of the std::unique_ptr is when to delete the underlying resource. This occurs when the
! std::unique_ptr goes out of scope or receives a new resource.

*/

#include<iostream>
#include<memory>
#include<utility>

struct MyInt{
    MyInt(int i ): i_(i){}
    ~MyInt()
    {
        std::cout<<"Good bye from"<<i_<<"\n";
    }
    int i_;
};


int main()
{
    std::unique_ptr<MyInt> uniquePtr1 {new MyInt(1998)};

    std::cout<<uniquePtr1.get()<<"\n";

    std::unique_ptr<MyInt> uniquePtr2;
    uniquePtr2 = std::move(uniquePtr1);

    std::cout<<uniquePtr1.get()<<"\n";
    std::cout<<uniquePtr2.get()<<"\n";

    {
        std::unique_ptr<MyInt> localPtr{new MyInt(2003)};
    }

    uniquePtr2.reset(new MyInt(2011));
    MyInt* myInt = uniquePtr2.release();
    delete myInt;

    std::unique_ptr<MyInt> uniquePtr3{new MyInt(2017)};
    std::unique_ptr<MyInt> uniquePtr4{new MyInt{2022}};

    std::cout<<uniquePtr3.get()<<"\n";
    std::cout<<uniquePtr4.get()<<"\n";

    std::swap(uniquePtr3,uniquePtr4);

    std::cout<<uniquePtr3.get()<<"\n";
    std::cout<<uniquePtr4.get()<<"\n";

}

/*
std::unique_ptr has a specialization for arrays. The access is transparent,
meaning that if the std::unique_ptr manages the lifetime of an object, the
operators for the object access are overloaded ( operator* and operator-> ). If
std::unique_ptr manages the lifetime of an array, the index operator [] is
overloaded. The invocations of the operators are, therefore, transparently
forwarded to the underlying resource.

*/
#include<iomanip>
#include<iostream>
#include<memory>


class MyStruct{
        public:
            MyStruct(){
                std::cout<<std::setw(15)<<std::left<<(void *) this <<" hello"<<"\n";
            }

            ~MyStruct()
            {
                std::cout<<std::setw(15)<<std::left<<(void*) this <<" goodbye "<<"\n";
            }
};


int main()
{
    std::unique_ptr<int> uniqInt(new int(2011));
    std::cout<<"*uniqueInt"<<*uniqInt<<"\n"; //2011 ---> dereference kardim 
    {
        std::unique_ptr<MyStruct[]> myUniqueArray{new MyStruct[5]}; //Mystruct[] yani pointer be array mikhaym ijad kunim --> ye array 5 element e ijad kardim
    } //inja 5 ta elements array az beyn mire

    {
        std::unique_ptr<MyStruct[]> myUniqueArray{new MyStruct[1]}; //We create a MyStruct instance on the heap
        MyStruct myStruct; //We create a MyStruct instance on the stack
        myUniqueArray[0] = myStruct; //we assign the local object to the std::unique_pr 
    }

    {
        std::unique_ptr<MyStruct[]> myUniqueArray{new MyStruct[1]};
        MyStruct myStruct;
        myStruct = myUniqueArray[0];
    }

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///SHARED POINTER
/*

Introduction #

! std::shared_ptr shares ownership of the resource. They have two handles: one
! for the resource, and one for the reference counter. By copying an
! std::shared_ptr , the reference count is increased by one. It is decreased by
! one if the std::shared_ptr goes out of scope. If the reference counter becomes
! the value 0, the C++ runtime automatically releases the resource, since there is
! no longer an std::shared_ptr referencing the resource. The release of the
! resource occurs exactly when the last std::shared_ptr goes out of scope. The
! C++ runtime guarantees that the call of the reference counter is an atomic
! operation. Due to this management, std::shared_ptr consumes more time
! and memory than a raw pointer or std::unique_ptr .
! Take a look at the image below to better visualize the concept---> pdf 159--> std::shared_ptr<int> shared2(shared1);
! Due to shared1 , shared2 is initialized. In the end, the reference count is 2 and
! both smart pointers have the same resource.



Methods #
! get --> Returns a pointer to the resource.
! get_deleter --> Returns the delete function.
! reset --> Resets the resource.
! swap -->Swaps the resources.
! unique --> Checks if the std::shared_ptr is the exclusive owner of the resource.
! use_count --> Returns the value of the reference counter.


std::make_shared #
! The helper function std::make_shared creates the resource and returns it in
! an std::shared_ptr . Use std::make_shared rather than directly creating an
! std::shared_ptr because std::make_shared is much faster. Additionally, such
! as in the case of std::make_unique , std::make_shared guarantees no memory
! leaks.

std::shared_ptr from this #
This unique technique, in which a class derives from a class template
having itself as a parameter, is called CRTP and stands for Curiously
Recurring Template Pattern.

Using the class std::enable_shared_from_this, we can create objects that return
an std::shared_ptr to themselves. To do so, we must publicly derive the class
from std::enable_shared_from_this . So the class ShareMe support the method
shared_from_this , and return std::shared_ptr :

*/

/*
Implement the class ShareMe so the objects of type ShareMe return an
std::shared_ptr to themselves.
With the class std::enable_shared_from_this, we can create objects which
return an std::shared_ptr on itself. For that, we must derive the class
public from std::enable_shared_from_this .
*/
#include<iostream>
#include<memory>

class ShareMe: public std::enable_shared_from_this<ShareMe>{ //in komak mikune ke object hayee besazim ke std::shred_ptr be khoodes return mikune
    public:
        std::shared_ptr<ShareMe> getShared(){
            return shared_from_this();
        }
};

int main()
{
    std::shared_ptr<ShareMe> shareMe(new ShareMe);
    std::shared_ptr<ShareMe> shareMe1 = shareMe->getShared(); //! shareMe->getShared() in line 19 creates a new smart pointer.
    
    
    // both resources have the same address
    std::cout<< "Address of resource of shareMe "<<(void*)shareMe.get() <<" "<< "\n"; //! returns a pointer to the resource
    std::cout<< "Address of resource of shareMe1 "<<(void*) shareMe1.get()<<" "<<"\n";


    // the use_count is 2
    std::cout<< "shareME.use_count(): "<<shareMe.use_count()<<"\n";
    
    
    
    {
        auto shareMe2(shareMe1);
        std::cout<<shareMe.use_count()<<"\n";
    }
    std::cout<<shareMe.use_count()<<"\n";
    shareMe1.reset();
    std::cout<<shareMe1.use_count();
}





//Example ---> cyclic references when using std::shared_ptr -->We get cyclic references of std::shared_ptr if they refer to each other. masalan 1 be 2 va 2 be 3 va 3 be 1
//! If we have a cyclic reference of std::shared_ptr , the reference counter will never become 0. We can break this cycle if by embedding an std::weak_ptr in
//! the cycle. std::weak_ptr does not modify the reference counter.
/*
Theoretically, we can use a raw pointer to break the cycle of
std::shared_ptr 's, but a raw pointer has two disadvantages. First, they
don’t have a well-defined interface. Second, they don’t support an
interface that can create an std::shared_ptr out of it.
*/
#include<iostream>
#include<memory>
class Son;
class Daughter;
struct Mother
{
    ~Mother(){std::cout<<"Mother gone \n";}

    void setSon(const std::shared_ptr<Son> s)
    {
        son = s;
    }

    void setDaughter(const std::shared_ptr<Daughter> d)
    {
        daughter = d;
    }

    std::shared_ptr<const Son>  son; //! we have a cyclic reference of std::shared_ptr between mother and son --> chun mother be son va son ham dar peen be mother point mikune. Therefore, the reference counter is always greater than 0, and the destructor will not automatically be invoked.
    std::weak_ptr<const Daughter> daughter; //! beyne mother va daughter ham hamine monteha chun weak ptr use kardim, cycle break mishe! --> so  If the daughter goes out of scope, the reference counter of the std::shared_ptr myMother (line 36) becomes 0 and the resource will automatically be deleted.
};


struct Son
{
    Son(std::shared_ptr<Mother> m ): myMother(m){}
    ~Son(){std::cout<<"Son gone;\n";}
    std::shared_ptr<Mother> myMother;
};

struct Daughter
{
    Daughter(std::shared_ptr<Mother> m): myMother(m){}
    ~Daughter(){std::cout<<"Daughter gone \n";}
    std::shared_ptr<Mother> myMother;
};


int main()
{
    {
        std::shared_ptr<Mother> mother = std::shared_ptr<Mother>(new Mother); //chejori default constructor ro seda zade vaghti implement esh nakarde??!!!
        std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
        std::shared_ptr<Daughter> daughter = std::shared_ptr<Daughter>(new Daughter(mother));
        std::cout<<mother.use_count()<<"\n";
        std::cout<<son.use_count()<<"\n";
        std::cout<<daughter.use_count()<<"\n";

        mother->setSon(son);
        mother->setDaughter(daughter);

        std::cout<<mother.use_count()<<"\n";
        std::cout<<son.use_count()<<"\n";
        std::cout<<daughter.use_count()<<"\n";
        /*
            ! agar be use count ha negah bokini mishe 3 va 2 va 1 ke bad az scope faghat daughter pak mishe --> taze oon daughter ro ham agar dar class mother weak nakarde bodi ke inam pak nemishod!
        */
    }
}





//Example

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

    sharPtr = shared_ptr<MyInt>(new MyInt(2011)); //! inja 1998 pak mishe resourcesesh be sorate automatic chun akharin chizi ke behesh point mikune sharPtr bood ke oonam alan be jaye dg ee point mikune! --> so the destructor of sharPtr is invoked

}//The last new resource MyInt(2011) will be destroyed at the end of main.




//Example --> custom deleter for smart pointers
//In this example, we create a special std::shared_ptr that logs how much memory has already been released.
//custom deleter
//Watch https://www.youtube.com/watch?v=bVhNu7h-3wM
// custom deleter for shared pointer ---> std::shared_ptr<A> spA(new A() , &deleteA) --> deleteA mitone function pointer bashe ya lambda function bashe ya functor ke bayad operatro() ro overload kune 
// custom deleter for unique_ptr --> std::unique_ptr<A,std::function<void(A*)>> ---> yani bayad toye template esh ham benivsi
#include<iostream>
#include<memory>
#include<random>
#include<typeinfo>


template<typename T>
class Deleter{
    public:
        void operator()(T* ptr)
        {
            ++Deleter::count; //It counts how often the call operator was used.
            delete ptr;
        }

        void getInfo()
        {
            std::string typeId{typeid(T).name()};
            size_t sz = Deleter::count* sizeof(T);
            std::cout<<" Deleted "<<Deleter::count<<" objects of type: " <<typeId <<"\n";
            std::cout<<"Freed size in bytes "<<sz <<"\n";
            std::cout<<"\n";
        }

    private:
        static int count;
};
template<typename T>
int Deleter<T>::count = 0;


typedef Deleter<int> IntDeleter;
typedef Deleter<double> DoubleDeleter;

void createRandomNumbers(){ // creates between 1 to 1000
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> thousand(1,1000);
    int ranNumber = thousand(engine);
    for(int i = 0 ; i<=ranNumber; ++i) std::shared_ptr<int>(new int(i) , IntDeleter());
}
int main()
{
    {
        std::shared_ptr<int> sharedPtr1(new int , IntDeleter()); //IntDeleter() --> the () is overloaded in the functor //std::shared_ptr parametrized by the special deleter intDeleter() 
        std::shared_ptr<int> sharedPtr2(new int , IntDeleter());
        auto intDeleter = std::get_deleter<IntDeleter>(sharedPtr1);
        intDeleter ->getInfo(); //shows that no resource has been released.
        sharedPtr2.reset(); //releasing the resource
        intDeleter->getInfo();//An int variable with 4 bytes has been released
    }
    createRandomNumbers(); //The call createRandomNumbers() creates  std::shared_ptr<int>
    IntDeleter().getInfo();
    {
        std::unique_ptr<double,DoubleDeleter> uniquePtr(new double , DoubleDeleter()); //Of course, we can use the deleter for an std::unique_ptr

        std::unique_ptr<double,DoubleDeleter> uniquePtr1(new double,DoubleDeleter());
        std::shared_ptr<double> sharedPtr(new double , DoubleDeleter());

        std::shared_ptr<double> sharedPtr4(std::move(uniquePtr));
        std::shared_ptr<double> sharedPtr5 = std::move(uniquePtr1);
        DoubleDeleter().getInfo();
    } //The memory for the double objects will be released after the end of the block,

    DoubleDeleter().getInfo();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///WEAK POINTER
/*
To be honest, std::weak_ptr is not a classic smart pointer, since it supports no
transparent access to the resource; it only borrows the resource from an
std::shared_ptr .


Methods #
The table provides an overview of the methods of std::weak_ptr .

expired --> Checks if the resource was deleted.
lock --> Creates a std::shared_ptr on the resource.
reset --> Resets the resource.
swap --> Swaps the resources.
use_count -->Returns the value of the reference counter.

! There is one main reason for the existence and use of std::weak_ptr .
! It breaks the cycle of std::shared_ptr . We will discuss these cyclic
! references in detail in the next lessons.

! As compared to the std::shared_ptr, std::weak_ptr does not change the reference counter of the shared variable.
! Let's take a look at this feature in the example below.
*/


#include<iostream>
#include<memory>

int main()
{
    auto sharedPtr = std::make_shared<int>(2011);
    std::weak_ptr<int> weakPtr(sharedPtr); //! we create an std::weak_ptr that borrows the resource from the std::shared_ptr . --> ref count ro ziad nemikune

    std::cout<<"weakPtr.use_count(): "<<weakPtr.use_count()<<"\n"; //output : 1 --> std::weak does not increment the counter.
    std::cout<<"sharedPtr.use_count(): "<<sharedPtr.use_count()<<"\n";//output : 1 --> std::weak does not increment the counter.
    std::cout<<"weakPtr.expired():" <<weakPtr.expired()<<"\n"; //! checks if the resource was already deleted. --> equivalent to---> weakPtr.use_count() == 0

    if(std::shared_ptr<int> sharedPtr1 = weakPtr.lock() ){  //! create an std::shared_ptr out of it --> The reference counter will now be increased to 2
        std::cout<<" *sharedPtr: "<< *sharedPtr <<"\n";
        std::cout<<"sharedPtr1.use_count(): "<<sharedPtr1.use_count()<<"\n";
    }
    else{
        std::cout<<"Don't get the resource!" <<"\n";
    }

    weakPtr.reset(); //! After resetting the weakPtr (line 25), the call weakPtr.lock() fails.

    if(std::shared_ptr<int> sharedPtr1 = weakPtr.lock())
    {
        std::cout<<"*sharedPtr: "<<*sharedPtr<<"\n";
        std::cout<<"sharedPtr1.use_count(): "<<sharedPtr1.use_count()<<"\n";
    }
    else
    {
        std::cout<<"Don't get the resource!"<<"\n";
    }


}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///CYCLIC REFERENCE
/*
We get cyclic references of std::shared_ptr if they refer to each other.

The issue #
! If we have a cyclic reference of std::shared_ptr , the reference counter will
! never become 0. We can break this cycle if by embedding an std::weak_ptr in
! the cycle. std::weak_ptr does not modify the reference counter.

! Theoretically, we can use a raw pointer to break the cycle of
! std::shared_ptr 's, but a raw pointer has two disadvantages. First, they
! don’t have a well-defined interface. Second, they don’t support an
! interface that can create an std::shared_ptr out of it.

see the pictures in pdf 163 ---> 
shared pointer 1 -> shared pointer 2 --> shared pointer 3 --> shared pointer 1

There are two cycles in the graphic below: first, between the mother and her
daughter; second, between the mother and her son. The subtle difference is
that the mother references her daughter with an std::weak_ptr . Therefore,
the std::shared_ptr cycle is broken.
picture in pdf 163
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///PERFORMANCE COMPARISSON BETWEEN SMART POINTERS
#include<chrono>
#include<iostream>
#include<memory>
static const long long numInt = 100000000;

int main()
{
    auto start = std::chrono::system_clock::now();

    for (long long i = 0; i <numInt ; ++i)
    {
        //int* tmp(new int(i));
        //delete tmp;
        //std::shared_ptr<int> tmp(new int(i));
       //std::shared_ptr<int> tmp(std::make_shared<int>(i));
        //std::unique_ptr<int> tmp(new int(i));
        std::unique_ptr<int> tmp(std::make_unique<int>(i));
    }

    std::chrono::duration<double> dur = std::chrono::system_clock::now()-start;
    std::cout<<"time native: "<< dur.count()<<" seconds"<<"\n";


}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

