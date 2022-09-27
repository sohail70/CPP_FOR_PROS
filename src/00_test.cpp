#include<iostream>

class A{
    public:
    A() = default;

    private:
        int aa;
};


int main()
{
    A a;
    std::cout<<sizeof(a)<<"\n";
}