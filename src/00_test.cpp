#include<iostream>

int main()
{
    double* d = new double[10];
    d[0] =1;
    d[1] = 2;
    std::cout<<*d<<"\n";

    delete d;
    std::cout<<*d<<"\n";

}