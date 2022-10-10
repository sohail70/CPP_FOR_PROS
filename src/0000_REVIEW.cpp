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



/*
The functions listed in this lesson make searching more efficient.

! Ordered associative containers are optimized for searching, and so they offer
! unique search functions.

Special search functions of the ordered associative containers
Seach function                      Description
ordAssCont.count(key)               Returns the number of values with the key .
ordAssCont.find(key)                Returns the iterator of key in ordAssCont . If there is no key in ordAssCont it returns ordAssCont.end()
ordAssCont.lower_bound(key)         Returns the iterator to the first key in ordAssCont in which key would be inserted.
ordAssCont.upper_bound(key)         Returns the last position of key in ordAssCont in which key would be inserted.
ordAssCont.equal_range(key)         Returns the range ordAssCont.lower bound(key) and ordAssCont.upper_bound(key) in a std::pair .

*/



#include<iostream>
#include<set>

int main()
{
    std::multiset<int> mySet{3,1,5,3,4,5,1,4,4,3,2,2,7,6,4,3,6};

    for(auto s:mySet) std::cout<<s<<" "; //1 1 2 2 3 3 3 4 4 4 4 5 5 6 6 7
    std::cout<<"\n";

    mySet.erase(mySet.lower_bound(4),mySet.upper_bound(4));
    for(auto s: mySet) std::cout<< s<<" "; //1 1 2 2 3 3 3 3 5 5 6 6 7
    std::cout<<"\n";

    std::cout << mySet.count(3) << std::endl; // 4
    std::cout << *mySet.find(3) << std::endl; // 3
    std::cout << *mySet.lower_bound(3) << std::endl; // 3
    std::cout << *mySet.upper_bound(3) << std::endl; // 5
    auto pair= mySet.equal_range(3);
    std::cout << "(" << *pair.first << "," << *pair.second << ")"; // (3,5)
    std::cout<<"\n";
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///MAP
/*
! std::map is by far the most frequently used associative container. The reason
! is simple; It combines
! adequate(https://www.educative.io/collection/page/10370001/51289822047764
! 48/5935479880941568) with a very convenient interface. We can access its
! elements via the index operator. If the key doesn’t exist, std:map creates a
! key-value pair. For the value, the default constructor is used.


! Consider std::map as a generalization of std::vector
! Often, std::map is called an associative array because std::map supports
! the index operator like a sequential container. The subtle difference is
! that its index is not restricted to a number like in the case of
! std::vector . Its index can be almost any arbitrary type.
! The same observations hold for its namesake std::unordered_map .

! In addition to the index operator, std::map supports the at method.The
! compiler checks the at function to make sure it is not out of bounds. So if the
! request key doesn’t exist in the std::map , an std::out_of_range exception is
! thrown.


*/


///Exercise
/*
The program how frequently a word is used in a text.This is a typical use-case
for an ordered associative container.
Execute the program
Analyze the source code
*/

#include <regex>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <utility>


using str2Int = std::unordered_map<std::string ,size_t>;
using intAndWords = std::pair<std::size_t,std::vector<std::string>>;
using int2Words = std::map<std::size_t , std::vector<std::string>>;

//count the frequency of each word

str2Int wordCount(const std::string& text){
    std::regex wordReg(R"(\w+)");
    std::sregex_iterator wordItBegin(text.begin(), text.end(), wordReg);
    const std::sregex_iterator wordItEnd;
    str2Int allWords;
    for(; wordItBegin != wordItEnd; ++wordItBegin){
        ++allWords[wordItBegin->str()];
    }
    return allWords;
}

// get to all frequencies the appropriate words
int2Words frequencyOfWords(str2Int& wordCount)
{
    int2Words freq2Words;
    for(auto wordIt : wordCount){
        auto freqWord = wordIt.second;
        if( freq2Words.find(freqWord) == freq2Words.end()){
            freq2Words.insert(intAndWords(freqWord,{wordIt.first}));
        }
        else{
            freq2Words[freqWord].push_back(wordIt.first);
        }
    }
    return freq2Words;
}

int main(int argc, char* argv[]){
    std::cout << std::endl;
    // get the filename
    std::string myFile = "Test.rtf";
    // open the file
    std::ifstream file(myFile, std::ios::in);
    if (!file){
    std::cerr << "Can't open file "+ myFile + "!" << std::endl;
    exit(EXIT_FAILURE);
    }
    // read the file
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text(buffer.str());
    // get the frequency of each word
    auto allWords= wordCount(text);
    std::cout << "The first 20 (key, value)-pairs: " << std::endl;
    auto end= allWords.begin();
    std::advance(end, 20);
    for (auto pair= allWords.begin(); pair != end; ++pair){
    std::cout << "(" << pair->first << ": " << pair->second << ")";
    }
    std::cout << "\n\n";
    std::cout << "allWords[Web]: " << allWords["Web"] << std::endl;
    std::cout << "allWords[The]: " << allWords["The"] << "\n\n";
    std::cout << "Number of unique words: ";
    std::cout << allWords.size() << "\n\n";
    size_t sumWords=0;
    for (auto wordIt: allWords) sumWords+= wordIt.second;
    std::cout << "Total number of words: " << sumWords <<"\n\n";
    auto allFreq= frequencyOfWords(allWords);
    std::cout << "Number of different frequencies: " << allFreq.size() << "\n\n";
    std::cout << "All frequencies: ";
    for (auto freqIt: allFreq) std::cout << freqIt.first << " ";
    std::cout << "\n\n";
    std::cout << "The most frequently occurring word(s): " << std::endl;
    auto atTheEnd= allFreq.rbegin();
    std::cout << atTheEnd->first << " :";
    for (auto word: atTheEnd->second) std::cout << word << " ";
    std::cout << "\n\n";
    std::cout << "All word which appears more then 1000 times:" << std::endl;
    auto biggerIt= std::find_if(allFreq.begin(), allFreq.end(), [](intAndWords iAndW){return iAndW;});
    if (biggerIt == allFreq.end()){
    std::cerr << "No word appears more then 1000 times !" << std::endl;
    exit(EXIT_FAILURE);
    }
    else{
    for (auto allFreqIt= biggerIt; allFreqIt != allFreq.end(); ++allFreqIt){
    std::cout << allFreqIt->first << " :";
    for (auto word: allFreqIt->second) std::cout << word << " ";
    std::cout << std::endl;
    }
    }
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///UNORDERED ASSOCIATIVE CONTAINERS
/*
The main difference between unordered and ordered associative containers is the idea of sorted keys

key ---> hash function ---> buckets

! With the new C++11 standard, C++ has four unordered associative containers:
! std::unordered_map , std::unordered_multimap , std::unordered_set , and
! std::unordered_multiset . They have a lot in common with their namesakes,
! the ordered associative containers. The difference is that the unordered ones
! have a richer interface and their keys are not sorted.

This shows the declaration of an std::unordered_map .
*/
template<class key , class val , class Hash = std::hash<key>> ,  
                class KeyEqual = std::equal_to<key>,
                class Alloc = std::allocator<std::pair<const key, val>>>
class unordered_map;

/*
! Like std::map , std::unordered_map has an allocator, but std::unordered_map
! needs no comparison function. Instead std::unordered_map needs two
! additional functions: One to determine the hash value of its key:
! std::has<key> and a second to compare the keys for equality:
! std::equal_to<key> . Because of the three default template parameters, we
! only have to provide the type of the key and the type of the value. For
! example, declaration of std::unordered_map would be
! std::unordered_map<char,int> unordMap .
*/


/*
This lesson is about the different properties of keys and values in this type of associative container.
There are special rules for the key and value of an unordered associative
container.

The key has to be
! comparable
! available as hash value
! copyable or moveable

The value has to be
! default constructible
! copyable or moveable
*/


/*
The unordered associative container type is more optimized when compared to its ordered sibling.

! Performance. That’s the simple reason why the unordered associative
! containers were so long missed in C++. In the example below, one million
! randomly created values are read from an std::map and std::unordered_map
! with 10 million values. The impressive result is that the linear access time of
! an unordered associative container is 20 times faster than the access time of
! an ordered associative container. That is just the difference between constant
! and logarithmic complexity O(log n) of these operations.

! Note: The given code might take more time to execute than normal.

*/

#include<chrono>
#include<iostream>
#include<map>
#include<random>
#include<unordered_map>


static const long long mapSize = 1000000;
static const long long accSize = 1000000;

int main()
{
    std::map<int,int> myMap;
    std::unordered_map<int,int> myHash;

    for(long long i = 0 ; i<mapSize ; ++i)
    {
        myMap[i] = i;
        myHash[i] = i;
    }

    std::vector<int> randValues;
    randValues.reserve(accSize);

    // random values
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> uniformDist(0,mapSize);
    for(long long i =0 ; i <accSize ; ++i) randValues.push_back(uniformDist(engine));

    auto start = std::chrono::system_clock::now();
    for(long long i = 0 ; i<accSize ; ++i){
        myMap[randValues[i]];
    }

    std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
    std::cout<<"time for std::map "<<dur.count() <<" seconds" <<std::endl;

    auto start2 = std::chrono::system_clock::now();
    for(long long i = 0 ; i<accSize ; ++i){
        myHash[randValues[i]];
    }
    std::chrono::duration<double> dur2 = std::chrono::system_clock::now() - start2;
    std::cout<<"time for std::unordered_map: "<<dur2.count() <<" seconds"<<"\n";
    
}



/*
Here, we will understand why hash functions are essential in unordered associative pairs.


! The reason for the constant access time of an unordered associative container
! is the hash function. The hash function maps the key to its value (its hash
! value). A hash function is good if it produces as few collisions as possible and
! equally distributes the keys onto the buckets. Because the execution of the
! hash function takes a constant amount of time, accessing the elements in the
! base case is also constant.


The hash function #
! is already defined for the built-in types like boolean, natural numbers, and floating point numbers.
! is available for std::string and std::wstring .
! generates, for a C string, const char a hash value of the pointer address.
! can be defined for user-defined data types.


! For user-defined types, which are used as a key for an unordered associative
! container, we have to keep two requirements in mind: They need a hash
! function and an equality operator to be defined in order for them to be
! compared.

yani alan dar mesale paeen masalan MyHash ro pak kuni error mide --> pas ham ye MyHash niaze va Ham niaze operator== overload beshe 
*/

#include<iostream>
#include<unordered_map>


struct MyInt{
    MyInt(int v): val(v){}
    bool operator== (const MyInt& other) const{ //
        return val == other.val;
    }

    int val;
};


struct MyHash{
    std::size_t operator()(MyInt m) const{
        std::hash<int> hashVal;
        return hashVal(m.val);
    }
};


std::ostream& operator << (std::ostream& st, const MyInt& myIn){
    st<<myIn.val;
    return st;
}


int main()
{
    typedef std::unordered_map<MyInt, int , MyHash> MyIntMap;
    MyIntMap myMap{{MyInt(-2),-2} , {MyInt(-1),-1} , {MyInt(0),0} , {MyInt(1),1}};

    for(auto m: myMap) std::cout<<"{" <<m.first<<" , "<<m.second<<"}"; // {MyInt(1),1} {MyInt(0),0} {MyInt(-1),-1} {MyInt(-2),-2}

    std::cout<<myMap[MyInt(-2)]<<"\n"; //-2

}


/*

The unordered associative containers store their indices in buckets. In which
bucket the index goes depends on the hash function, which maps the key to
the index. If different keys are mapped to the same index, it’s called a
collision. The hash function tries to avoid this.

Indices are typically stored in the bucket as a linked list. Since the access to
the bucket is constant, the access to the linked list in the bucket is linear. The
number of buckets is called capacity, the average number of elements for each
bucket is called the load factor. In general, the C++ runtime generates new
buckets if the load factor is greater than 1. This process is called rehashing and
can also be triggered explicitly:

With the method max_load_factor , you can read and set the load factor in
order to influence the probability of collisions and rehashing. I want to
emphasize one point in the short example below: the key 500 is in the 5th
bucket at first, but after rehashing, it is in the 500th bucket.

*/

#include<iostream>
#include<unordered_set>
using namespace std;

void getInfo(const unordered_set<int>& hash)
{
    cout<<hash.bucket_count()<<"\n";
    cout<<hash.load_factor()<<"\n";
}


int main()
{
   // Create an unoredered set and initialize it with the array
    // Set will contain only random elements

    int arr[100];
    for(int i = 0 ; i <100 ; i++)
        arr[i] = (rand() % 100) +1 ;
    unordered_set<int> hash(arr,arr+sizeof(arr)/sizeof(int));
    cout<<hash.max_load_factor()<<"\n"; 

    getInfo(hash);//hash.bucket_count(): 103hash.load_factor(): 0.660194
    cout<<endl;

    hash.insert(500);
    cout<<hash.bucket(500)<<"\n"; //88

    getInfo(hash);//hash.bucket_count(): 103hash.load_factor(): 0.669903
    cout<<endl;

    hash.rehash(500);

    getInfo(hash);//hash.bucket_count(): 503hash.load_factor(): 0.137177500
    cout<<endl<<hash.bucket(500); //hash.bucket(500): 500


}


///Exercise
/*
Problem statement #

Use std::unordered_set instead of std::unordered_map and
std::unordered_multiset instead of std::unordered_multimap in the program.
std::set , std::multiset , and all variations are only degenerated
versions of std::map and std::multimap , missing the associated value.



Explanation #
In lines 10 and 11, we have initialized an std::unordered_multiset with
some integer values and also an std::unordered_set , which contains
unique values which are repeated in std::unordered_multiset .

In lines 25 and 26, we inserted the value -1000 in both sets.

In lines 54 and 55, we have erased the value 5 from both sets.

In lines 61 and 62, we have used the clear function which deletes all
elements from both of the sets.
*/

#include <iostream>
#include <set>
#include <unordered_set>
int main(){
    std::cout << std::endl;
    // constructor
    std::unordered_multiset<int> multiSet{1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::unordered_set<int> uniqSet(multiSet.begin(), multiSet.end());
    // show the difference
    std::cout << "multiSet: ";
    for(auto m : multiSet) std::cout << m << " ";
    std::cout << std::endl;
    std::cout << "uniqSet: ";
    for(auto s : uniqSet) std::cout << s << " ";
    std::cout << std::endl << std::endl;
    // insert elements
    multiSet.insert(-1000);
    uniqSet.insert(-1000);
    std::set<int> mySet{-5, -4, -3, -2, -1};
    multiSet.insert(mySet.begin(), mySet.end());
    uniqSet.insert(mySet.begin(), mySet.end());
    // show the difference
    std::cout << "multiSet: ";
    for(auto m : multiSet) std::cout << m << " ";
    std::cout << std::endl;
    std::cout << "uniqSet: ";
    for(auto s : uniqSet) std::cout << s << " ";
    std::cout << std::endl << std::endl;
    // search for elements
    auto it = uniqSet.find(5);
    if (it != uniqSet.end()){
    std::cout << "uniqSet.find(5): " << *it << std::endl;
    }
    std::cout << "multiSet.count(5): " << multiSet.count(5) << std::endl;
    std::cout << std::endl;
    // remove
    int numMulti = multiSet.erase(5);
    int numUniq = uniqSet.erase(5);
    std::cout << "Erased " << numMulti << " times 5 from multiSet." << std::endl;
    std::cout << "Erased " << numUniq << " times 5 from uniqSet." << std::endl;
    // all
    multiSet.clear();
    uniqSet.clear();
    std::cout << std::endl;
    std::cout << "multiSet.size(): " << multiSet.size() << std::endl;
    std::cout << "uniqSet.size(): " << uniqSet.size() << std::endl;
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///ALGORITHM C++17
/*
! The Standard Template Library has a large number of algorithms that work
! with containers and their elements. As the algorithms are function templates,
! they are independent of the type of elements in the container. The glue
! between the containers and algorithms is the iterators. If our custom
! container supports the interface of an STL container, we can apply the
! algorithms to our container.
*/


#include<iostream>
#include<algorithm>
#include<deque>
#include<list>
#include<string>
#include<vector>



template <typename Cont, typename T> //ta vase container haye mokhtalef az func paeen estefade kunim ---> chun ro container haye stl mishe alg haye yeksan ro use kard.
void doTheSame(Cont cont,T t)
{
    for(const auto c: cont) std::cout<< c <<" ";
    
    std::cout<< std::endl;
    std::cout<<cont.size()<<std::endl;
    std::reverse(cont.begin(),cont.end());
    
    for(const auto c: cont) std::cout<< c<<" ";
    std::cout<<"\n";
    std::reverse(cont.begin(),cont.end());
    
    for(const auto c: cont) std::cout<< c <<" ";
    std::cout<<"\n";
    auto It = std::find(cont.begin(),cont.end(),t);
    std::reverse(It, cont.end());
    
    for(const auto c: cont) std::cout<< c <<" ";
}

int main()
{
    std::vector<int> myVec{1,2,3,4,5,6,7,8,9,10};
    std::deque<std::string> myDeq({"A","B","C","D","E","F","G","H","I"});
    std::list<char> myList({'a','b','c','d','e','f','g','h'});

    doTheSame(myVec,5);
    std::cout<<"\n\n";
    // 1 2 3 4 5 6 7 8 9 10
    // 10
    // 10 9 8 7 6 5 4 3 2 1
    // 1 2 3 4 5 6 7 8 9 10
    // 1 2 3 4 10 9 8 7 6 5


    doTheSame(myDeq, "D");
    std::cout << "\n\n";
    // A B C D E F G H I
    // 9
    // I H G F E D C B A
    // A B C D E F G H I
    // A B C I H G F E D

    doTheSame(myList, 'd');
    std::cout << "\n\n";
    // a b c d e f g h
    // 8
    // h g f e d c b a
    // a b c d e f g h
    // a b c h g f e d
}

/*
Headers #
! The algorithms are defined in various headers:
<algorithm>  Contains the general algorithms.
<numeric>    Contains numeric algorithms.
<functional>     Predefined function objects and function adapters.

Name Conventions #
! Many of the algorithms have the name suffix _if and _copy .
_if     The algorithm can be parametrized by a predicate.
_copy   The algorithm copies its elements in another range.

! Algorithms like auto num = std::count(InpIt first, InpIt last, const T&
! val) return the number of elements that are equal to val in the given range
! [first, last) . num is of type iterator_traits<InpIt>::difference_type . This
! means we have the guarantee that num is sufficient to hold the result, and
! because of the automatic return type deduction with auto , the compiler will
! give us the right types.

! If the container uses an additional range, it has to be valid
! The algorithm std::copy_if uses an iterator for the beginning of its
! destination range. This destination range has to be valid.



! Naming conventions for the algorithms
! We use a few naming conventions for the type of arguments and the
! return type of the algorithms to make them easier to read.

Name      Description
InIt     [Input iterator]
FwdIt    [Forward iterator]
BiIt     [Bidirectional iterator]
UnFunc   [Unary callable]
BiFunc   [Binary callable]
UnPre    [Unary predicate]
BiPre    [Binary predicate]
Search   The searcher encapsulates the search algorithm.
ValType  From the input range automatically deduced value type.
ExePol   [Execution policy]

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///for_each --> std::for_each applies a unary callable to each element of its range. The range is given by the input iterators.
/*
UnFunc std::for_each(InpIt first , InpIt second , UnFunc func)
void std::for_each(ExePol pol , FwdIt first , FwdIt second , UnFunc func)

std::for_each , when used without an explicit execution policy is a special
algorithm because it returns its callable argument. If we invoke std::for_each
with a function object, we can store the result of the function call directly in
the function object.

InpIt std::for_each_n(InpIt first, Size n, UnFunc func)
FwdIt std::for_each_n(ExePol pol, FwdIt first, Size n, UnFunc func)

std::for_each_n is new with C++17 and applies a unary callable to the first n
elements of its range. The range is given by an input iterator and a size.
*/

#include<array>
#include<algorithm>
#include<iostream>
#include<vector>


template<typename T>
class ContainerInfo{
    public:
        void operator()(T t){
            num++;
            sum+= t;
        }

        int getSum() const{
            return sum;
        }

        int getSize() const{return num;}

        double getMean() const{
            return static_cast<double>(sum) / static_cast<double>(num);
        }

    private:
        T sum{0};
        int num{0};
        
};
//! deghat kun ke for_each hamoon callable khodesho barmigardoone yani dar khate auto vecInfo ,vecInfo hamon object ee az ContainerInfo hast
int main()
{
    std::cout << std::endl;
    std::vector<double> myVec{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    auto vecInfo= std::for_each(myVec.begin(), myVec.end(), ContainerInfo<double>()); //fek mikunam ContainerInfo<double>() operator overload ee bashe ke bala neveshtim//dar vaghe class bala ye function object hast ke dadim be for_each
    std::cout << "vecInfo.getSum(): " << vecInfo.getSum() << std::endl;
    std::cout << "vecInfo.getSize(): " << vecInfo.getSize() << std::endl;
    std::cout << "vecInfo.getMean(): " << vecInfo.getMean() << std::endl;
    std::cout << std::endl;
    std::array<int, 100> myArr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto arrInfo= std::for_each(myArr.begin(), myArr.end(), ContainerInfo<int>());
    std::cout << "arrInfo.getSum(): " << arrInfo.getSum() << std::endl;
    std::cout << "arrInfo.getSize(): " << arrInfo.getSize() << std::endl;
    std::cout << "arrInfo.getMean(): " << arrInfo.getMean() << std::endl;
    std::cout << std::endl;
}



//Problem statement #
//Calculate the mean of an std::vector and an std::array with std::for_each .

//javabe khodam:
#include<iostream>
#include<vector>
#include<algorithm>


class Mean{
        public:
                void operator()(int v)
                {
                        num++;
                        mean = (mean*(num-1) + v)/ num;
                }       
                void printMean() const {std::cout<<mean<<"\n";}
        private:
                int sum{0};
                int num{0};
                double mean;
};      



int main()
{
        std::vector<int> myVec {1,2,3,4,5,6,7,8,9,10};
        auto f = std::for_each(myVec.begin(),myVec.end(),Mean());
        f.printMean();
}

//javabe pdf:

#include<array>
#include<algorithm>
#include<iostream>
#include<string>
#include<vector>

template <typename T>
class ContainerInfo{
    public:
        void operator()(T t){
            size++;
            sum += t;
        }
        int getSum() const{
            return sum;
        }
        int getSize() const{ return size; }
        double getMean() const{
            return static_cast<double>(sum)/static_cast<double>(size);
        }
    private:
        T sum{0};
        int size{0};
};
int main(){
    std::cout << std::endl;
    std::vector<double> myVec{1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};auto vecInfo = std::for_each(myVec.begin(), myVec.end(), ContainerInfo<double>());
    std::cout << "vecInfo.getSum(): " << vecInfo.getSum() << std::endl;
    std::cout << "vecInfo.getSize(): " << vecInfo.getSize() << std::endl;
    std::cout << "vecInfo.getMean(): " << vecInfo.getMean() << std::endl;
    std::cout << std::endl;
    std::array<int, 100> myArr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto arrInfo    = std::for_each(myArr.begin(), myArr.end(), ContainerInfo<int>());
    std::cout <<"arrInfo.getSum(): " << arrInfo.getSum() << std::endl;
    std::cout <<"arrInfo.getSize(): " << arrInfo.getSize() << std::endl;
    std::cout <<"arrInfo.getMean(): " << arrInfo.getMean() << std::endl;
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Non-modifying algorithms --> used for searching and counting elements , compare given ranges, or search for ranges given any range.
/*

Returns an iterator to the first element that matches the search criteria.

InpIt find(InpIt first, InpI last, const T& val)
InpIt find(ExePol pol, FwdIt first, FwdIt last, const T& val)
InpIt find_if(InpIt first, InpIt last, UnPred pred)
InpIt find_if(ExePol pol, FwdIt first, FwdIt last, UnPred pred)
InpIt find_if_not(InpIt first, InpIt last, UnPred pre)
InpIt find_if_not(ExePol pol, FwdIt first, FwdIt last, UnPred pre)


Returns an iterator to the first element in the range:
FwdIt1 find_first_of(InpIt1 first1, InpIt1 last1, FwdIt2 first2, FwdIt2 last2)
FwdIt1 find_first_of(ExePol pol, FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2)
FwdIt1 find_first_of(InpIt1 first1, InpIt1 last1, FwdIt2 first2, FwdIt2 last2, BiPre pre)
FwdIt1 find_first_of(ExePol pol, FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2, Bi

Returns identical, adjacent elements in a range:
FwdIt adjacent_find(FwdIt first, FwdIt last)
FwdIt adjacent_find(ExePol pol, FwdIt first, FwdIt last)
FwdIt adjacent_find(FwdIt first, FwdI last, BiPre pre)
FwdIt adjacent_find(ExePol pol, FwdIt first, FwdI last, BiPre pre)

The algorithms require input or forward iterators as arguments and return an
iterator on the element when successfully found. If the search is not
successful, they return an end iterator.

*/
#include<iostream>
#include<algorithm>
#include<set>
#include<list>

using namespace std;



bool isVowel(char c){
    string myVowels{"aeiouaou"};
    set<char> vowels(myVowels.begin(),myVowels.end());
    return (vowels.find(c) != vowels.end());
}


int main()
{
    list<char> myCha{'a','b','c','d','e','f','g','h','i','j'};
    int cha[] = {'A','B','C'};

    cout <<*find(myCha.begin(),myCha.end(),'g')<<endl; //g
    cout << *find_if(myCha.begin(), myCha.end(), isVowel) << endl; //a
    cout << *find_if_not(myCha.begin(), myCha.end(), isVowel) << endl; //b

    auto iter= find_first_of(myCha.begin(), myCha.end(), cha, cha + 3);
    if (iter == myCha.end()) cout << "None of A, B or C." << endl; // None of A, B or C.

    auto iter2= find_first_of(myCha.begin(), myCha.end(), cha, cha+3, 
            [](char a, char b){ return toupper(a) == toupper(b); }); //compare mikune  first1-last1 ro ba first2-last2 ke age upper har do baham barabar bood true beshe va find kune

    if (iter2 != myCha.end()) cout << *iter2 << endl; //a
    auto iter3= adjacent_find(myCha.begin(), myCha.end());

    if (iter3 == myCha.end()) cout << "No same adjacent chars." << endl;
    // No same adjacent chars.
    auto iter4= adjacent_find(myCha.begin(), myCha.end(),
        [](char a, char b){ return isVowel(a) == isVowel(b); });

    if (iter4 != myCha.end()) cout << *iter4; // b

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///count algorithms -->  assist us in counting the number of elements in a range which satisfy a certain predicate
/*
We can count elements (with or without a predicate) using STL algorithms.
They return the number of elements:

Num count(InpIt first, InpIt last, const T& val)
Num count(ExePol pol, FwdIt first, FwdIt last, const T& val)
Num count_if(InpIt first, InpIt last, UnPred pre)
Num count_if(ExePol pol, FwdIt first, FwdIt last, UnPred pre)

*/
#include<algorithm>
#include<cctype>
#include<iostream>
#include<string>

int main()
{
    std::cout << std::endl;
    std::string str{"abcdabAAAaefaBqeaBCQEaadsfdewAAQAaafbd"};
    std::cout << "count: " << std::count(str.begin(), str.end(), 'a') << std::endl;
    std::cout << "count_if: " << std::count_if(str.begin(), str.end(), [](char a){ return std::isupper(a);}); //Khodam isupper ro neveshtam
    std::cout << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// test ranges
/*
C++17 contains several algorithms to check whether a value or values in a range fulfill our given condition. Let's
look at these algorithms now.

The three functions std::all_of , std::any_of , and std::none_of answer the
question of whether all, at least one, or no elements of a range satisfy the
condition. As arguments, the functions need input iterators, a unary predicate,
and return a boolean.
Checks if all elements of the range satisfy the condition:
bool all_of(InpIt first, InpIt last, UnPre pre)
bool all_of(ExePol pol, FwdIt first, FwdIt last, UnPre pre)


Checks if at least one element of the range satisfies the condition:
bool any_of(InpIt first, InpIt last, UnPre pre)
bool any_of(ExePol pol, FwdIt first, FwdIt last, UnPre pre)

Checks if no element of the range satisfies the condition:
bool none_of(InpIt first, InpIt last, UnPre pre)
bool none_of(ExePol pol, FwdIt first, FwdIt last, UnPre pre)

*/

#include<algorithm>
#include<iostream>
#include<vector>

int main()
{
    std::cout<< std::boolalpha<<std::endl;

    auto even = [](int i){return i%2;};

    std::vector<int> myVec{1 , 2 ,3,4,5,6,7,8,9};


    std::cout<<"std::any_of: \t" <<std::any_of(myVec.begin(), myVec.end(),even) <<std::endl;
    std::cout<<"std::all_of: \t"<<std::all_of(myVec.begin(),myVec.end(),even)<<std::endl;
    std::cout<<"std::none_of: \t"<<std::none_of(myVec.begin(),myVec.end(),even)<<std::endl;

    std::cout<<std::endl;

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Compare ranges
/*
The functions described below allow us to check the degree of equality between ranges.

With std::equal , we can compare ranges. std::lexicographical_compare and
std::mismatch compute which range is the smallest one.
equal : checks if both ranges are equal.


bool equal(InpIt first1, InpIt last1, InpIt first2)
bool equal(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2)
bool equal(InpIt first1, InpIt last1, InpIt first2, BiPre pred)
bool equal(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, BiPre pred)
bool equal(InpIt first1, InpIt last1, InpIt first2, InpIt last2)
bool equal(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2)
bool equal(InpIt first1, InpIt last1, InpIt first2, InpIt last2, BiPre pred)
bool equal(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2, BiPre pred)


lexicographical_compare : checks if the first range is smaller than the second.

bool lexicographical_compare(InpIt first1, InpIt last1, InpIt first2, InpIt last2)
bool lexicographical_compare(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2
bool lexicographical_compare(InpIt first1, InpIt last1, InpIt first2, InpIt last2, BiPre pred
bool lexicographical_compare(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2


mismatch : finds the first position at which both ranges are not equal.

pair<InpIt, InpIt> mismatch(InpIt first1, InpIt last1, InpIt first2)
pair<InpIt, InpIt> mismatch(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2)
pair<InpIt, InpIt> mismatch(InpIt first1, InpIt last1, InpIt first2, BiPre pred)
pair<InpIt, InpIt> mismatch(ExePol pol, FwdIt first1, FwdIt last2, FwdIt first2, BiPre pred)
pair<InpIt, InpIt> mismatch(InpIt first1, InpIt last1, InpIt first2, InpIt last2)
pair<InpIt, InpIt> mismatch(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2)
pair<InpIt, InpIt> mismatch(InpIt first1, InpIt last1, InpIt first2, InpIt last2, BiPre pred)
pair<InpIt, InpIt> mismatch(ExePol pol, FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2,

The algorithms take input iterators and eventually a binary predicate.
std::mismatch returns a pair pa of input iterators as its result. pa.first holds
an input iterator for the first element that is not equal. pa.second holds the
corresponding input iterator for the second range. If both ranges are identical,
we get two end iterators.
*/

#include <algorithm>
#include<cctype>
#include<iostream>
#include<string>


int main()
{
    std::cout<<std::boolalpha<<std::endl;


    std::string str1{"Only For Testing Purpose."};
    std::string str2{"only for testing purpose."};

    std::cout<<"str1"<<str1<<std::endl;
    std::cout<<"str2"<<str2<<std::endl;

    std::cout<<std::endl;

    std::cout<<std::equal(str1.begin(),str1.end(),str2.begin())<<"\n";
    std::cout<<std::equal(str1.begin(),str1.end(),str2.begin()),[](char c1, char c2){return c1==c2;};


    str1= {"Only for testing Purpose."};
    str2= {"Only for testing purpose."};

   auto pair= std::mismatch(str1.begin(), str1.end(), str2.begin());
if ( pair.first == str1.end() ){ //end fek kunam ye done bad az element akhar bashe, doroste? ke vaghti chizi peyda nemishe yani ta oonja rafte! --> are doroste mire ye done bad az akharin element age pyda nashe! --> kolan end index e yedone bad az akhar hast
std::cout << "str1 and str2 are equal" << std::endl;
}
else{
std::cout << "str1 and str2 are different at position " << std::distance(str1.begin(), pa
<< " with (" << *pair.first << ", " << *pair.second << ")" << std::endl;
}
auto pair2= std::mismatch(str1.begin(), str1.end(), str2.begin(), [](char c1, char c2){ ret //kamel kun khoodet badan
if ( pair2.first == str1.end() ){
std::cout << "str1 and str2 are equal" << std::endl;
}
else{
std::cout << "str1 and str2 are different at position " << std::distance(str1.begin(), pa //kamel kun khodet badan
<< " with(" << *pair2.first << ", " << *pair2.second << ")" << std::endl;
}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///search ranges
/*

Need to acquire a sub-range from any existing range? std::search solves the problem ef ciently.


std::search      Searches for a range in another range from the beginning.
std::find_end    Searches for a range in another range from the end.
std::search_n    Searches for n consecutive elements in the range.

All algorithms that take a forward iterator can be parametrized by a binary
predicate and return an end iterator for the first range, if the search was not
successful.

Searches the values of the second range in the first range and returns the
position. Starts at the beginning:

FwdIt1 search(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2)
FwdIt1 search(ExePol pol, FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2)
FwdIt1 search(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2, BiPre pre)
FwdIt1 search(ExePol pol, FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2, BiPre pre
FwdIt1 search(FwdIt1 first, FwdIt last1, Search search)


Searches the values of the second range in the first range and returns the
position. Starts at the end:

FwdIt1 find_end(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2 FwdIt2 last2)
FwdIt1 find_end(ExePol pol, FwdIt1 first1, FwdIt1 last1, FwdIt2 first2 FwdIt2 last2)FwdIt1 find_end(FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2, BiPre pre)
FwdIt1 find_end(ExePol pol, FwdIt1 first1, FwdIt1 last1, FwdIt2 first2, FwdIt2 last2, BiPre p


Searches count for consecutive values in the first range:

FwdIt search_n(FwdIt first, FwdIt last, Size count, const T& value)
FwdIt search_n(ExePol pol, FwdIt first, FwdIt last, Size count, const T& value)
FwdIt search_n(FwdIt first, FwdIt last, Size count, const T& value, BiPre pre)
FwdIt search_n(ExePol pol, FwdIt first, FwdIt last, Size count, const T& value, BiPre pre)

The algorithm search_n is very special
The algorithm FwdIt search_n(FwdIt first, FwdIt last, Size count,
const T& value, BiPre pre) is very special. The binary predicate BiPre
uses, as first argument, the values of the range and, as second argument,
the value value .
*/
#include<algorithm>
#include<array>
#include<cmath>
#include<iostream>


int main(){
    std::cout << std::endl;
    std::array<int, 10> arr1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::array<int, 5> arr2{3, 4, -5, 6, 7};
    auto fwdIt= std::search(arr1.begin(), arr1.end(), arr2.begin(), arr2.end());
    if (fwdIt == arr1.end()) std::cout << "arr2 not in arr1." << std::endl;
    else{
    std::cout << "arr2 at position " << std::distance(arr1.begin(), fwdIt) << " in arr1." <
    }
    
    auto fwdIt2= std::search(arr1.begin(), arr1.end(), arr2.begin(), arr2.end(), [](int a, int //badan kamel kun
    if (fwdIt2 == arr1.end()) std::cout << "arr2 not in arr1." << std::endl;
    else{
    std::cout << "arr2 at position " << std::distance(arr1.begin(), fwdIt2)
    }
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///copy elements and ranges
/*
In this lesson, we'll learn how to perform various copy operations on a given range.

We can copy ranges forward with std::copy , backward with
std::copy_backward and conditionally with std::copy_if . To copy n elements,
we can use std::copy_n .


copy : copies the range.


OutIt copy(InpIt first, InpIt last, OutIt result)
FwdIt2 copy(ExePol pol, FwdIt first, FwdIt last, FowdIt2 result)


copy_n : copies n elements.

OutIt copy_n(InpIt first, Size n, OutIt result)
FwdIt2 copy_n(ExePol pol, FwdIt first, Size n, FwdIt2 result)

copy_if : Copies the elements dependent on the predicate pre .
OutIt copy_if(InpIt first, InpIt last, OutIt result, UnPre pre)
FwdIt2 copy_if(ExePol pol, FwdIt first, FwdIt last, FwdIt2 result, UnPre pre)


copy_backward : Copies the range backward.
BiIt copy_backward(BiIt first, BiIt last, BiIt result)


The algorithms need input iterators to copy their elements to result . They
return an end iterator to the destination range.
*/

#include<algorithm>
#include<iostream>
#include<string>
#include<vector>


int main()
{
    std::cout<< std::endl;

    std::vector<int> myVec{0,1,2,3,4,5,6,7,9};
    std::vector<int> myVec2(10);

    std::copy_if(myVec.begin(),myVec.end(),myVec2.begin()+3,[](int a){return a%2;}); //if the a%2 returns 1 then its true and it copies the input but if a%2=0 then it doesn't copy the input
    for(auto v: myVec2) std::cout<<v<<" ";

    std::cout<<"\n\n";
    std::string str{"Iamstring1"};
    std::string str2{"Hellostring---------------------2"};
    std::cout << str2 << std::endl;
    std::copy_backward(str.begin(), str.end(), str2.end());
    std::cout << str2 << std::endl;
    std::cout << std::endl;
    std::cout << str << std::endl;
    std::copy_backward(str.begin(), str.begin() + 5, str.end()); //copy starts from the end of str and then one by one it steps backward and copies each char
    std::cout << str << std::endl;
    std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Replace elements and ranges --> Let's look at the functions we can use to update and replace values in ranges.
/*

There are four variations of std::replace , std::replace_if ,
std::replace_copy , and std::replace_copy_if that can be used to replace
elements in a range. The algorithms differ in two aspects: first, does the
algorithm need a predicate? Second, does the algorithm copy the elements in
the destination range?

replace : Replaces the old elements in the range with newValue , if the old
element has the value old .
void replace(FwdIt first, FwdIt last, const T& old, const T& newValue)
void replace(ExePol pol, FwdIt first, FwdIt last, const T& old, const T& newValue)

replace_if : Replaces the old elements of the range with newValue , if the old
element fulfills the predicate pred .
void replace_if(FwdIt first, FwdIt last, UnPred pred, const T& newValue)
void replace_if(ExePol pol, FwdIt first, FwdIt last, UnPred pred, const T& newValue)



replace_copy : Replaces the old elements in the range with newValue if the old
element has the value old . Copies the result to result .
OutIt replace_copy(InpIt first, InpIt last, OutIt result, const T& old, const T& newValue)
FwdIt2 replace_copy(ExePol pol, FwdIt first, FwdIt last, FwdIt2 result, const T& old, const T




replace_copy_if : Replaces the old elements of the range with newValue if the
old element fulfills the predicate pred . Copies the result to result .
OutIt replace_copy_if(InpIt first, InpIt last, OutIt result, UnPre pred, const T& newValue)
FwdIt2 replace_copy_if(ExePol pol, FwdIt first, FwdIt last, FwdIt2 result, UnPre pred, const

*/

#include<algorithm>
#include<cctype>
#include<iostream>
#include<string>

int main()
{
    std::cout << std::endl;
    std::string str{"Only for testing purpose."};
    std::cout << str << std::endl;
    std::replace(str.begin(), str.end(), ' ', '1');
    std::cout << str << std::endl;
    std::replace_if(str.begin(), str.end(), [](char c){ return c == '1'; }, '2'); //replace if the predicate (lambda) returns true which is 1
    std::cout << str << std::endl;
    std::string str2;
    std::replace_copy(str.begin(), str.end(), std::back_inserter(str2), '2', '3'); //back inserter inserts at the end of str2 - repalace 2 with 3 and put it in str2
    std::cout << str2 << std::endl;
    std::string str3;
    std::replace_copy_if(str2.begin(), str2.end(), std::back_inserter(str3), [](char c){ return c=='3';},'4');
    std::cout << str3 << std::endl;

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

