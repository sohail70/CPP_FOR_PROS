#include<iostream>
int addFunc(int a , int b){return a+b;}
int main()
{
    struct addObject{
        int operator() (int a, int b){return a+b;};
    };
    addObject addObj;
    std::cout<<addObj(2,3)<<"\n";
}