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

