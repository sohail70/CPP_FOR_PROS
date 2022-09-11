/* PDF 186
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

Associative container               sorted          Associated value        More Identical keys         Acess time

std::set                            Yes             No                      No                          Logarithmic

std::uordered_set                   no              no                      no                          constant

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


// orderedUnorderedComparison.cpp
#include <iostream>
#include <map>
#include <unordered_map>
// std::map
// std::map
int main(){
    std::map<std::string, int> m {{"Dijkstra", 1972}, {"Scott", 1976}};
    m["Ritchie"]= 1983;
    std::cout << m["Ritchie"];
    // 1983
    std::cout<<"\n";
    for(auto p : m) std::cout << "{" << p.first << "," << p.second << "}";
    // {Dijkstra,1972},{Ritchie,1983},{Scott,1976}
    std::cout<<"\n";
    m.erase("Scott");
    for(auto p : m) std::cout << "{" << p.first << "," << p.second << "}";
    // {Dijkstra,1972},{Ritchie,1983}
    std::cout<<"\n";
    m.clear();
    std::cout << m.size() << std::endl;
    // 0
    // std::unordered_map
    std::unordered_map<std::string, int> um {{"Dijkstra", 1972}, {"Scott", 1976}};
    um["Ritchie"]= 1983;
    std::cout << um["Ritchie"];
    // 1983
    std::cout<<"\n";
    for(auto p : um) std::cout << "{" << p.first << "," << p.second << "}";
    // {Ritchie,1983},{Scott,1976},{Dijkstra,1972}
    std::cout<<"\n";
    um.erase("Scott");
    for(auto p : um) std::cout << "{" << p.first << "," << p.second << "}";
    // {Ritchie,1983},{Dijkstra,1972}
    std::cout<<"\n";
    um.clear();
    std::cout << um.size() << std::endl;
    // 0
    return 0;
}



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