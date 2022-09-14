#include<iostream>
#include<string>


struct T1{};

struct T2
{
    int mem = 0;
    public:
        T2(){}
};

auto n =0;

int main()
{
    using namespace std::string_literals;
    auto n = 0;
    auto s = ""s;
    auto t1 = T1();
    auto t2 = T2();
    
    std::cout<<::n<<" "<<n<<" "<<s<<" "<<t2.mem<<"\n";
}
