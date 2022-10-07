#include<iostream>
#include<map>


int main()
{
        std::map<int,std::string,std::greater<int>> int2string{{5,"five"},{4,"four"},{7,"seven"},{6,"six"}};
        for(auto m : int2string){std::cout<<m.first<<" "<<m.second <<"\n";}
}