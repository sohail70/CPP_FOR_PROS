#include<iostream>


class A{
    public:
        A(int a):a(a){}
        constexpr int geta() const {
            b=2;
            std::cout<<b<<"\n";
            return this->a;
        };
    private:
        double a;
        mutable double b;
};  

int main()
{
    constexpr A a(2);
    
}