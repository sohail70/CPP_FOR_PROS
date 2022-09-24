#include<iostream>
#include<string.h>

const char* min(const char* s , const char* t)
{
    return(strcmp(s,t)<0) ? s:t;
}

float min(float x, float y )
{
    return(x<y) ? x:y;
}


int main()
{
    const char* s = min("abc","xyz");
    float f = min(4.4f , 1.23f);
    int f2 = min(2011,2014);

    std::cout<<s<<"\n";
    std::cout<<f<<"\n";
    std::cout<<f2<<"\n";
}