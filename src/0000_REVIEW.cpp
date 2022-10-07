///sequential and associative containers of the Standard Template library
/*
each container has an allocator, hence the size of a container can be adjusted at runtime --> The call std::vector<int> results in a call
std::vector<int, std::allocator<int>>

C++ covers the sequential containers std::array, std::vector, std::deque, std::list,
and std::forward_list, in detail.
The same holds true for associative containers, which can be classified in the
ordered and unordered associative container.


! Because of the std::allocator we can adjust the size of all containers dynamically, except for std::array .
! We can access the elements of a container quite easily with an iterator.

*/


/*

The table shows the constructors and destructors of a container. All these
functions can be used with std:vector.

TYPE                        EXAMPLE
Default                     std::vector<int> vec1
Range                       std::vector<int> vec2(vec1.begin(), vec1.end())
Copy                        std::vector<int> vec3(vec2)
Copy                        std::vector<int> vec3= vec2
Move                        std::vector<int> vec4(std::move(vec3))
Move                        std::vector<int> vec4= std::move(vec3)
Sequence (Initializer list) std::vector<int> vec5 {1, 2, 3, 4, 5}
Sequence (Initializer list) std::vector<int> vec5= {1, 2, 3, 4, 5}
Destructor                  vec5.~vector()
Delete elements             vec5.clear()

Creation and deletion of a container
! Because std::array is generated at compile-time, there are a few things that
! are special. std::array has no move constructor and can’t be created with a
! range or with an initializer list. However, an std::array can be initialized
! with an aggregate initialization. Also, std::array has no method for removing
! its elements.
! Now we can use the different constructors on the different containers.
*/

#include<iostream>
#include<map>
#include<unordered_map>
#include<vector>

using namespace std;

int main()
{
    vector<int> vec = {1,2,3,4,5,6,7,8,9};
    map<string,int> m ={{"bart",12345},{"jenne",34929},{"huber",840284}};
    unordered_map<string,int> um{m.begin(),m.end()};

    for(auto v:vec) cout<<v<<" "; //1 23 4 5 6 7 8 9
    cout<<"\n";
    for(auto p:m) cout<<p.first <<","<<p.second<<" "; //bart,123345 huber,840284 jenne 34929
    cout<<"\n";
    for(auto p: um) cout<<p.first<<","<<p.second<<" "; //bart,12345 jenne,34929 hubber ...
    cout<<"\n";

    vector<int> vec2=vec;
    cout<<vec.size()<<endl; //9
    cout<<vec2.size()<<endl; //9

    vector<int> vec3 = move(vec);
    cout<<vec.size() <<endl; //0
    cout<<vec3.size()<<endl; //9

    vec3.clear();
    cout<<vec3.size()<<endl; //0
    return 0;
}


/* container cont
cont.empty() ---> to see if the container is empty
cont.size() ---> returns the current number of elements
cont.max_size() ---> returns the maximum number of elements cont can have --> The maximum number of elements is implementation defined.

! For a container cont , use the method cont.empty() instead of(cont.size() == 0) to determine if the container is empty. First,
! cont.empty() is, in general, faster than (const.size() == 0) ; second, the
! container std::forward_list has no method size() .

*/




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ACCESS THE ELEMENTS OF A CONTAINER
/*
access the elements of a container---> we can use an iterator. --->A begin and end iterator forms a half-open range-->It is half-open because the begin 
iterator belongs to the range, the end iterator refers to a position past the range

Functions available for iterators in containers:
Iterator                            Description
cont.begin() and cont.end()         Pair of iterators to iterate forward.
cont.cbegin() and cont.cend()       Pair of iterators to iterate const forward.
cont.rbegin() and cont.rend()       Pair of iterators to iterate backward.
cont.crbegin() and cont.crend()     Pair of iterators to iterate const backward.

Now I can modify the container.
*/

#include<iostream>
#include<vector>


using namespace std;

struct MyInt{
    MyInt(int i ): myInt(i){};
    int myInt;
};

int main()
{
    std::vector<MyInt> myIntVec;
    myIntVec.push_back(MyInt(5));
    myIntVec.emplace_back(1);
    std::cout<<myIntVec.size()<<"\n"; //2

    std::vector<int> intVec;
    intVec.assign({1,2,3});
    for(auto v: intVec) std::cout<<v<<" "; //1 2 3
    cout<<std::endl;

    intVec.insert(intVec.begin(), 0 );
    for(auto v: intVec) std::cout<<v<<" "; //0 1 2 3
    cout<<std::endl;

    intVec.insert(intVec.begin()+4,4);
    for(auto v:intVec) std::cout << v<<" "; //0 1 2 3 4
    cout<<"\n";

    intVec.insert(intVec.end(), {5,6,7,8,9,10,11});

    for(auto v:intVec) std::cout<<v<<" "; //0 1 2 3 4 5 6 7 8 9 10 11
    cout<<std::endl;

    for(auto revIt = intVec.rbegin(); revIt != intVec.rend(); ++revIt)
        std::cout<<*revIt<<" "; //11 10 9 8 7 6 5 4 3 2 1
    cout<<std::endl;

    intVec.pop_back();
    for(auto v: intVec) std::cout<<v <<" "; //0 1 2 3 4 5 6 7 8 9 10
    cout<<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ACCESS AND SWAP
/*
! If we want to assign a container cont2 to another
! container cont1 , we can do so either through copy assignment cont1= cont2
! or move assignment cont1= std::move(cont2) . In a move assignment, the
! value of cont2 is copied to cont1 and cont2 becomes empty. A special form of
! assignment is the one with an initializer list: cont= {1, 2, 3, 4, 5} . In the
! case of std:array , an initializer list is not possible, hence we use aggregate
! initialization. The function swap exists in two forms. It is a method
! cont1(swap(cont2)) and also a function template std::swap(cont1, cont2) .
*/


#include<iostream>
#include<set>

int main()
{
    std::set<int> set1{0,1,2,3,4,5};
    std::set<int> set2{6,7,8,9};

    for(auto s: set1) std::cout<< s<< " "; //0 1 2 3 4 5
    std::cout<< "\n";
    for(auto s: set2 ) std::cout<<s <<" "; //6 7 8 9
    std::cout<<"\n";


    set1 = set2;
    for(auto s: set1) std::cout<<s <<" "; //6 7 8 9
    std::cout<<"\n";
    for(auto s:set2) std::cout<<s<<" "; //6 7 8 9
    std::cout<<"\n";

    set1 = std::move(set2); //moves value of set2 in set1 and set2 becomes empty
    for(auto s: set1) std::cout<< s<< " "; //6 7 8 9
    std::cout<<" \n";
    for(auto s :set2) std::cout<<s<<" "; //prints null since set2 becomes empty after the...

    set2 = {60,70,80,90};
    for(auto s:set1) std::cout<<s<<" "; //6 7 8 9
    std::cout<<"\n";
    for(auto s:set2) std::cout<<s<<" "; //6 7 8 9
    std::cout<<"\n";


    std::swap(set1,set2);
    for(auto s: set1) std::cout<< s <<" "; //60 70 80 90
    std::cout<<"\n";
    for(auto s: set2) std::cout<<s<<" "; //6 7 8 9
    std::cout<<"\n";
    
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///All the general comparison operators work on containers.
/*
! Containers support the comparison operators == , != , < , > , <= , and >= . The
! comparison of two containers happens on the elements of the containers.
! When associative containers are compared, their keys are compared.
! Unordered associative containers support only the comparison operator ==
! and != .
*/


#include<iostream>
#include<array>
#include<set>
#include<unordered_map>
#include<vector>

using namespace std;

//output 1 represents true and 0 represents false
int main()
{
    vector<int> vec1{1,2,3,4};
    vector<int> vec2{1,2,3,4};
    cout<<(vec1==vec2)<<"\n"; //1

    array<int,4> arr1{1,2,3,4}; //ME: fek kunam chun array compile time ijad mishe bayad size ro begim
    array<int ,4> arr2{1,2,3,4};
    cout<<(arr1 == arr2)<<"\n"; //1

    set<int> set1{1,2,3,4};
    set<int> set2{4,3,2,1};
    cout<<(set1==set2)<<"\n"; //1

    set<int> set3{1,2,3,4,5};
    cout<<(set1<set3)<<endl; //1

    set<int> set4{1,2,3,-3}; //in adade akharesh baes shode kochaktar beshe az set1
    cout<<(set1>set4)<<"\n"; //1

    unordered_map<int,string> uSet1{{1,"one"},{2,"two"}};
    unordered_map<int,string> uSet2{{1,"one"},{2,"Two"}};
    cout<<(uSet1==uSet2)<<"\n"; //0 --> because the elements don't need to be in the same order in each map

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///SEQUENTIAL CONTAINERS
/*

! The sequential containers:

criteria                            Array                                               vector                                              Deque                                                   list                                                Forward list
size                                static                                              dynamic                                             dynamic                                                 dynamic                                             dynamic
Implementation                      static array                                        dynamic array                                       sequence of arrays                                      doubled linked list                                 single linked list
Access                              random                                              random                                              random                                                  forward and backward                                forward
Optimized for insert and delete at  -                                                   end: O(1)                                           begin and end:O(1)                                      begin and end: O(1) arbitrary: O(1)                 begin: O(1); arbitrary : O(1)  
memory reservation                  -                                                   yes                                                 no                                                      no                                                  no
Release of memory                   -                                                   shrink_to_fit                                       shrink_to_fit                                           always                                              always
Strength                            no memory allocation;minimal memory requirements    95% solution                                        insertion and deletion at the begin and end             insertion and deletion at an arbitrary position     fast insertion and deletion; minimal memory requiements
Weakness                            no dynamic memory; memory allocation                Insertion and deletion at arbitrary position O(n)   Insertion and deletion at an arbitrary position O(n)    no random access                                    no random access


 
! A few additional remarks to bring to the table.
O(1) stands for the complexity (runtime) of an operation. So O(1) means that
the runtime of an operation on a container is constant and is independent of
the size of the container. Opposite to that, O(n) means that the runtime
depends linearly on the number of the elements of the container. What does
that mean for an std::vector ? The access time on an element is independent
of the size of the std::vector , but the insertion or deletion of an arbitrary
element with k-times more elements is k-times slower.

! Although the random access on the elements of an std::vector has the same
! complexity, O(1), as the random access on the element of an std::deque , that
! doesn’t mean, that both operations are equally fast.

! The complexity guarantee O(1) for the insertion or deletion of a double
! ( std::list ) or single linked list ( std::forward_list ) is only guaranteed if the
! iterator points to the right element. --> khoob shod goft vagarna manam be shak andakhte bood.


! std::string is like std::vector
! Of course std::string is not a container of the standard template
! library. But from a behavioral point of view, it is like a sequential
! container, specifically an std::vector<char> . Therefore, we will treat
! std::string like an std::vector<char> .
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ARRAYS
/*

! std::array is a homogeneous container of fixed length. It requires the header
! <array> . An instance of std::array combines the memory and runtime
! characteristic of a C array with the interface of an std::vector .In particular,
! an std::array knows its size. We can use STL algorithms on instances of
! std::array .


Keep a few special rules in mind for initializing an std::array .
! std::array<int, 10> arr : The 10 elements are not initialized.
! std::array<int, 10> arr{} : The 10 elements initialized to 0 by default.
! std::array<int, 10> arr{1, 2, 3, 4, 5} : The unspecified elements are initialized to 0 by default.

std::array supports three types of index access.
! arr[n]
! arr.at(n)
! std::get<n>(arr)


! The most commonly used first type of index access using angle brackets does
! not check the boundaries of the arr . This is in contrast to arr.at(n) . We will
! eventually get an std::range-error exception. The last form in the above
! snippet shows the relationship of std::array with the std::tuple, because both
! are containers of fixed length.


*/

#include<iostream>
#include<array>
#include<numeric>

using namespace std;

int main()
{
    std::array<int,10> arr{1,2,3,4,5,6,7,8,9,10};
    for(auto a: arr) std::cout<<a<<" "; //1 2 3 4 5 6 7 8 9 10
    cout<< "\n";

    double sum = accumulate(arr.begin(),arr.end(), 0);
    std::cout<< sum<<std::endl; //55

    double mean = sum /arr.size();
    std::cout<<mean <<"\n"; //5.5
    std::cout<< (arr[0] == std::get<0>(arr))<<"\n"; //1 (1 represents true)
}




///Exercise
/*
Problem statement
Try to access the index of the array that is greater than the size.
Implement it with the index operator and the at function.

Explanation #
! On line 13, we are trying to access arr[5] which is out of the bounds of the
! array. However, this line will not throw an exception and we would never know if we have accessed an index that is not in the range. On line 20, we
! tried to access the same index using the at function. This function checks if
! the index being accessed is out of bounds or not. Since 5 is greater than the
! size of the array, it throws an exception and terminates the program.
*/

#include<array>
#include<iostream>

int main()
{
    std::array<int ,4> arr = {1,2,3,4};

    for (auto a: arr){std::cout<<a<<" ";}

    arr[1] = 1000;
    arr[5] = 5;

    for(auto a:arr){std::cout<<a<<" ";}

    arr.at(0) = 10000;
    arr.at(5) = 5;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///VECTOR
/*
! Vectors are more refined version of arrays. They simplify the insertion and deletion of values.
! std::vector needs the header <vector>
! it’s length can be adjusted at runtime.
! std::vector supports pointer arithmetic.
*/
for (int i= 0; i < vec.size(); ++i){
    std::cout << vec[i] == *(vec + i) << std::endl; // true
}


/*
! std::vector<int> vec(10); ---> vector with capacity 10
! std::vector<int> vec{10}; ---> vector with element of 10 --> curly braces are interpreted as initializer lists so the sequence constructor is used.
! std::vector<int>(10, 2011); ---> 10 elements initialized to 2011
*/
#include<vector>
#include<utility>

int main()
{
    std::vector<int> first;
    std::vector<int> second(4,2011);
    std::vector<int> third(second.begin(),second.end());
    std::vector<int> forth(second);
    std::vector<int> fifth(std::move(second));
    std::vector<int> sixth{1,2,3,4,5};
}

/*
Size vs. Capacity
! The number of elements an std::vector has usually take up less space than
! what is already reserved. There is a simple reason for this. With extra
! memory already allocated, the size of the std::vector can increase without
! an expensive allocation of new memory.

There are a few methods for smartly handling memory:
Memory management of std::vector :

METHOD                                      DESCRIPTION
vec.size()                                  Returns the number of elements of vec .
vec.capacity()                              Returns the number of elements, which vec can have without reallocation.
vec.resize(n)                               vec will be increased to n elements.
vec.reserve(n)                              Reserve memory for at least n elements.
vec.shrink_to_fit()                         Reduces capacity of vec to the size.

! The call vec.shrink_to_fit() is not binding. That means the runtime can
! ignore it. But on popular platforms, I always observed the desired behavior.

*/
#include <iostream>
#include <vector>
int main(){
    std::vector<int> intVec1(5, 2011);
    intVec1.reserve(10);
    std::cout << intVec1.size() << std::endl; // 5
    
    std::cout << intVec1.capacity() << std::endl; // 10
    intVec1.shrink_to_fit();
    std::cout << intVec1.capacity() << std::endl; // 5
    std::vector<int> intVec2(10);
    std::cout << intVec2.size() << std::endl; // 10
    std::vector<int> intVec3{10};
    std::cout << intVec3.size() << std::endl; // 1
    std::vector<int> intVec4{5, 2011};
    std::cout << intVec4.size() << std::endl;
    return 0;
}


/*
! std::vector vec has a few methods to access its elements. vec.front() , yields
! the first element, and vec.back() yields the last element of vec . To read or
! write the (n+1)-th element of vec , we can use the index operator vec[n] or
! the method vec.at(n) . The second one checks the boundaries of vec , so that
! we eventually get an std::range_error exception.

Besides the index operator, std::vector offers additional methods to assign,
insert, create or remove elements. See the following overview.

Modify the elements of a std::vector:

Method                          Description
vec.assign( ... )               Assigns one or more elements, a range or an initializer list.
vec.clear()                     Removes all elements from vec .
vec.emplace(pos, args ... )     Creates a new element before pos with the args in vec and returns the new position of the element.
vec.emplace_back(args ... )     Creates a new element in vec with args ... .
vec.erase( ... )                Removes one element or a range and returns the next position.
vec.insert(pos, ... )           Inserts one or more elements, a range or an initializer list and returns the new position of the element.
vec.pop_back()                  Removes the last element.
vec.push_back(elem)             Adds a copy of elem at the end of vec .
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///DEQUE ---> DOUBLE ENDED QUEUE ---> sequence of arrays
/*
std::deque needs the header <deque>
quite similar to std::vector  ---> has three additional methods deq.push_front(elem) , deq.pop_front() , and deq.emplace_front(args... ) to add or remove elements at the beginning.

*/

#include<iostream>
#include<deque>

using namespace std;

class MyInt{
    private:
        int myInt;
    public:
        MyInt(int i): myInt(i){};
        friend ostream& operator << (ostream& os , const MyInt& m)
        {
            os << m.myInt<<" ";
            return os;
        }  
};


int main()
{
    std::deque<MyInt> myIntDeq;

    myIntDeq.push_back(MyInt(5));
    myIntDeq.emplace_back(1);
    std::cout<<myIntDeq.size()<<"\n"; //2

    std::deque<int> intDeq;

    intDeq.assign({1,2,3});
    for(auto v: intDeq) cout<<v<<" "; //1 2 3
    cout<<endl;

    intDeq.insert(intDeq.begin(), 0);
    for (auto v: intDeq) cout << v << " "; //0 1 2 3
    cout<<endl;


    intDeq.insert(intDeq.begin()+4,4);
    for(auto v: intDeq) cout<<v<<" "; //0 1 2 3 4
    cout<<endl;

    intDeq.insert(intDeq.end(), {5,6,7,8,9,10,11});
    for(auto v: intDeq) cout<<v<<" "; //0 1 2 3 4 5 6 7 8 9 10 11
    cout<<endl;

    for(auto revIt = intDeq.rbegin(); revIt != intDeq.rend();++revIt)
        std::cout<<*revIt<<" "; //11 10 9 8 7 6 5 4 3 2 1 0
    cout<<endl;

    intDeq.pop_back();
    for(auto v: intDeq) cout<< v<<" "; //0 1 2 3 4 5 6 7 8 9 10
    cout<<endl;

    intDeq.push_front(-1);
    for(auto v: intDeq) cout<<v<<" "; //-1 0 1 2 3 4 5 6 7 8 9 10
    cout<<endl;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///LISTS
/*
! std::list is a doubled linked list. std::list needs the header <list> .

Although it has a similar interface to std::vector or std::deque , std::list is
quite different from both of them. That’s due to its structure.

std::list makes the following points unique:
! It supports no random access.
! Accessing an arbitrary element is slow because we might have to iterate through the whole list.
! Adding or removing an element is fast, if the iterator points to the right place.
! If we add or remove an element, the iterator remains valid.


Because of its special structure, std::list has a few special methods.
Special methods of std::list #

Method                  Description
lis.merge(c)            Merges the sorted list c into the sorted list lis , so that lis remains sorted.
lis.merge(c, op)        Merges the sorted list c into the sorted list lis , so that lis remains sorted. Uses op as sorting criteria.
lis.remove(val)         Removes all elements from lis with value val .
lis.remove_if(pre)      Removes all elements from lis ,fulfilling the predicate pre .
lis.splice(pos, ... )   Splits the elements in lis before pos . The elements can be single elements, ranges or lists.
lis.unique()            Removes adjacent element with the same value.
lis.unique(pre)         Removes adjacent elements, fulfilling the predicate pre .
*/

#include<iostream>
#include<list>
#include<algorithm>


int main()
{
    std::list<int> list1{15,2,18,19,4,15,1,3,18,5,
                    4,7,17,9,16,8,6,6,17,1,2};
    list1.sort();
    for(auto l: list1) std::cout<<l<<" ";
    //1 1 2 2 3 4 4 5 6 6 7 8 9 15 15 16 17 17 18 18 19
    std::cout<<std::endl;

    list1.unique();
    for(auto l: list1) std::cout<<l <<" ";
    //1 23 4 5 6 7 8 9 15 16 17 18 19
    std::cout<<"\n";

    std::list<int> list2{10,11,12,13,14};

    list1.splice(std::find(list1.begin(),list1.end(),15),list2);

    for(auto l: list1) std::cout<<l<<" ";
    //  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

    std::cout<<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FORWARD LISTS
/*
! std::forward_list is a singly linked list, which needs the header
! <forward_list> . std::forward_list has a drastically reduced interface and is
! optimized for minimal memory requirements.



! std::forward_list has a lot in common with std::list :
! It doesn’t support the random access.

! The access of an arbitrary element is slow because in the worst case, we
! have to iterate forward through the whole list.

! To add or remove an element is fast, if the iterator points to the right
! place.

! If we add or remove an element, the iterator remains valid.

! Operations always refer to the beginning of the std::forward_list or the
! position past the current element.



! Being able to iterate through an std::forward_list forward has a great
! impact. The iterators cannot be decremented and therefore, operations like -
! - (decrement) on iterators are not supported. For the same reason,
! std::forward_list has no backward iterator. std::forward_list is the only
! sequential container which doesn’t know its size.

! std::forward_list has a very special domain
! std::forward_list is the replacement for single linked lists. It’s
! optimized for minimal memory management and performance if the
! insertion, extraction, or movement of elements only affects adjacent elements. This is typical for sorting algorithms.



The following are the special methods of std::forward_list :
Special methods of std::forward_list


Method                              Description
forw.before_begin()                 Returns an iterator before the first element.
forw.emplace_after(pos, args...)    Creates an element after pos with the arguments args... .
forw.emplace_front(args...)         Creates an element at the beginning of forw with the arguments args... .
forw.erase_after(pos, ...)          Removes from forw the element pos or a range of elements, starting with pos .
forw.insert_after(pos, ...)         Inserts new elements after pos .These elements can be single elements, ranges or initialiser lists.
forw.merge(c)                       Merges the sorted forward list c into the sorted forward list forw , so that forw keeps sorted.
forw.merge(c, op)                   Merges the forward sorted list c into the forward sorted list forw , so that forw keeps sorted. Uses op as sorting criteria.
forw.splice_after(pos, ...)         Splits the elements in forw before pos . The elements can be single elements, ranges or lists.
forw.unique()                       Removes adjacent element with the same value.
forw.unique(pre)                    Removes adjacent elements, fulfilling the predicate pre .

*/
#include<iostream>
#include<algorithm>
#include<forward_list>

using std::cout;

int main()
{
    std::forward_list<int> forw;
    std::cout<<forw.empty()<<"\n"; //1 (1 denoted true)

    forw.push_front(7);
    forw.push_front(6);
    forw.push_front(5);
    forw.push_front(4);
    forw.push_front(3);
    forw.push_front(2);
    forw.push_front(1);

    for(auto i: forw) cout<<i <<" "; //1 2 3 4 5 6 7
    cout<<"\n";


    forw.erase_after(forw.before_begin()); //faghat element aval ro erase mikune
    cout<<forw.front(); //2
    cout<<"\n";

    std::forward_list<int> forw2;
    forw2.insert_after(forw2.before_begin(),1);
    forw2.insert_after(++forw2.before_begin(),2);
    forw2.insert_after(++(++(forw2.before_begin())),3);
    forw2.push_front(1000);
    for(auto i = forw2.cbegin(); i != forw2.cend();++i) cout<<*i <<" "; //1000 1 2 3
    // 1 2 2 3 3 4 5 6 7 1000
    cout<<"\n";

    auto IteratorTo5 = std::find(forw.begin(), forw.end(), 5);
    forw.splice_after(IteratorTo5 , std::move(forw2)); //az index ee ke 5 toshe splice mikune va forw2 to mirize on vasat 
    for(auto i = forw.cbegin(); i != forw.cend(); ++i) cout<<*i<<" "; //2 3 4 5 1000 1 2 
    // 1000 7 6 5 4 3 3 2 2 1
    cout<<"\n";

    forw.unique();
    for(auto i = forw.cbegin() ; i != forw.cend() ;++i) cout<<*i<<" ";
    //1000 7 6 5 4 3 2 1
    cout<<"\n";
}

/*
! std::forward_list has a reduced interface, so we can’t use it with a lot of
! STL algorithms.

What are the characteristics of the methods of std::forward_list ?


Pointers that might help us to solve the above exercise:

Accessing of an arbitrary element is slow because we might have to
iterate forward through the whole list.

To add or remove an element is fast, if the iterator points to the right
place.

If we add or remove an element, the iterator remains valid.

We can only move forward with the iterator.


*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ASSOCIATIVE CONTAINERS
/*
C++ has eight different associative containers. Four of them are associative
containers with sorted keys: std::set , std::map , std::multiset , and
std::multimap . The other four are associative containers with unsorted keys:
std::unordered_set , std::unordered_map , std::unordered_multiset , and
std::unordered_multimap . The associative containers are special containers.
That means they support all of the operations described in the chapter
containers in general.



Overview
All eight ordered and unordered containers have one thing in common: they
associate a key with a value. We can use the key to get the value. To classify
the associative containers, three simple questions need to be answered:
! Are the keys sorted?
! Does the key have an associated value?
! Can a key appear more than once?

! The following table with 2 3 = 8 rows gives the answers to the three questions.
! The answer to a fourth question is in the table. How fast is the access time of a
! key in the best case?



Characteristics for associative containers

Associative container               sorted          Associated value        More Identical keys         Access time

std::set                            Yes             No                      No                          Logarithmic

std::unordered_set                   no              no                      no                          constant

std::map                            yes             yes                     no                          logarithmic

std::unordered_map                  no              yes                     no                          constant

std::multiset                       yes             no                      yes                         logarithmic

std::unordered_multiset             no              no                      yes                         constant

std::multimap                       yes             yes                     yes                         logarithmic

std::unordered_multimap             no              yes                     yes                         constant



! Since C++98, there have been ordered associative containers; with C++11 came
! unordered associative containers. Both classes have a very similar interface.
! That’s the reason that the following code sample is identical for std::map and
! std::unordered_map . To be more precise, the interface of std::unordered_map is
! a superset of the interface of std::map . The same holds true for the remaining
! three unordered associative containers. So, porting your code from the
! ordered to unordered containers is quite easy.


! We can initialize the containers with an initializer list and add new elements
! with the index operator. To access the first element of the key-value pair p ,
! we have p.first , and for the second element, we have p.second . p.first is
! the key and p.second is the associated value of the pair.



! There is a subtle difference between the two program executions: The keys of
! the std::map are ordered, the keys of the std::unordered_map are unordered.
! The question is: Why do we have such similar containers in C++? We already
! pointed this in the table above. The reason is so often the same: performance.
! The access time to the keys of an unordered associative container is constant
! and therefore independent of the size of the container. If the containers are
! big enough, the performance difference is significant. Have a look at the
! section about performance.

*/
#include<iostream>
#include<map>
#include<unordered_map>


// std::map

int main()
{
    std::map<std::string,int> m{{"Dijkstra", 1972},{"Scott",1976}};
    m["Ritchie"] = 1983;
    std::cout<< m["Ritchie"];           //1983
    std::cout<<"\n";

    for(auto p : m) std::cout<<"{"<<p.first<<","<<p.second<<"}";    //{Dijkstra,1972},{Ritchie,1983},{Scott,1976}
    std::cout<<"\n";

    m.erase("Scott");
    for(auto p:m) std::cout<<"{"<<p.first <<","<<p.second<<"}"; //{Dijkstra,1972},{Ritchie,1983}
    std::cout<<"\n";

    m.clear();
    std::cout<<m.size()<<std::endl; //0

    //std::unordered_map

    std::unordered_map<std::string , int> um {{"Dijkstra",1972},{"Scott",1976}};
    um["Ritchie"] = 1983;
    std::cout<<um["Ritchie"];       //1983
    std::cout<<"\n";


    for(auto p : um) std::cout<<"{"<<p.first <<","<<p.second<<"}";  //{Ritchie,1983},{Scott,1976},{Dijkstra,1972}
    std::cout<<"\n";

    um.erase("Scott");
    for(auto p : um) std::cout<< "{" <<p.first <<","<<p.second<<"}";    //{Ritchie,1983},{Dijkstra,1972}
    std::cout<<"\n";

    um.clear();
    std::cout<<um.size()<<std::endl;    //0


}
////
///Insertion and Deletion in associative containers -->  values are inserted and deleted based on the keys they have.
/*

! The insertion ( insert and emplace ) and deletion ( erase ) of elements in
! associative containers is similar to the rules of an std::vector. For an
! associative container that can have a key only once, the insertion fails if the
! key is already in the container. Additionally, ordered associative containers
! support a special function ordAssCont.erase(key) , which removes all pairs
! with the key and returns their number. See the usage of the function below.
*/
#include<iostream>
#include<set>
#include<array>


int main()
{
    std::multiset<int> mySet{3,1,5,3,4,5,1,4,4,3,2,2,7,6,4,3,6};

    for(auto s:mySet) std::cout<<s<<" "; //1 1 2 2 3 3 3 3 4 4 4 4 5 5 6 6 7
    std::cout<<"\n";

    mySet.insert(8);
    std::array<int,5> myArr{10,11,12,13,14};
    mySet.insert(myArr.begin(),myArr.begin()+3);
    mySet.insert({22,21,20});
    for(auto s:mySet) std::cout<<s<<" ";
    // 1 1 2 2 3 3 3 3 4 4 4 4 5 5 6 6 7 10 11 12 20 21 22
    std::cout<<"\n";

    std::cout<<mySet.erase(4); //4
    mySet.erase(mySet.lower_bound(5),mySet.upper_bound(15)); //fek kunam ---> az index avali ke 5 hast va akharin index ee ke 15 hast ro erase kun har chi in beyn hast
    for(auto s:mySet) std::cout<<s<<" ";
    // 1 1 2 2 3 3 3 3 20 21 22
    std::cout<<"\n";
}

/*
! All four ordered containers are parametrized by their type, their allocator,
! and their comparison function. The containers have default values for the
! allocator and the comparison function, depending on the type. The
! declaration of std::map and std::set show this very nicely.

template < class key, class val, class Comp= less<key>,
            class Alloc= allocator<pair<const key, val> >
class map;

template < class T, class Comp = less<T>,
            class Alloc = allocator<T> >
class set;

The declaration of both associative containers shows that std::map has an
associated value. The key and the value are used for the default allocator:
allocator<pair<const key, val>> . With a little bit more imagination, we can
derive more from the allocator. std::map has pairs of the type
std::pair<const key, val> . The associated value val does not matter for the
sort criteria: less<key> . All observations also hold for std::multimap and
std::multiset .

*/

/*
There are special rules for the key and the value of an ordered associative
container.

The key has to be
! sortable (by default, they are sorted in ascending order)
! copyable and moveable

The value has to be
! default constructible
! copyable and moveable

The key associated with the value builds a pair p so that we get a member
with p.first and the value with p.second .
*/
#include<iostream>
#include<map>

int main()
{
    std::multimap<char, int> multiMap = {{'a',10},{'a',20},{'b',30}}; //chun multimap hast mitone key tekrari ham dashte bashe
    for(auto p: multiMap) std::cout<< "{" << p.first << "," <<p.second<<"} ";   // {a,10},{a,20},{b,30}
    std::cout<<"\n";
    return 0;
}



// rules followed by ordered associative containers when comparing the values inside them.
/*
! The default comparison criterion of the ordered associative containers is
! std::less . If we want to use a user-defined type as the key, we have to
! overload the operator < . It’s sufficient to overload the operator < for our data
! type because the C++ runtime compares, with the help of the relation (!
! (elem1<elem2 || elem2<elem1)) , two elements for equality.


We can specify the sorting criterion as a template argument that must
implement a strict weak ordering.

Strict weak ordering
Strict weak ordering for a sorting criterion on a set S is given if the
following requirements are met:
For every s from S it has to hold that s < s is not possible.

For all s1 and s2 from S it must hold: If s1 < s2 , then s2 < s1 is
not possible.

For all s1 , s2 and s3 with s1 < s2 and s2 < s3 the following must
hold: s1 < s3 .

For all s1 , s2 and s3 with s1 not comparable with s2 and s2 not
comparable with s3 the following must hold: s1 is not comparable
with s3 .



In contrast to the definition of the strict weak ordering, the usage of a
comparison criterion with strict weak ordering is a lot simpler for an
std::map .
*/
#include<iostream>
#include<map>

int main()
{
    std::map<int,std::string,std::greater<int>> int2Str{
        {5,"five"},{1,"one"},{4,"four"},{3,"three"},
        {2,"two"},{7,"seven"},{6,"six"}
    };

    for(auto p : int2Str) std::cout<<"{" <<p.first<<","<<p.second<<"} ";// {7,seven} {6,six} {5,five} {4,four} {3,three} {2,two} {1,one}
    std::cout<<"\n";
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

