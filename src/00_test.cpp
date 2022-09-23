#include<iostream>
#include<string>
#include<utility>


template<typename T , typename ... Args>
T create(Args&& ... args)
{
    return T(std::forward<Args>(args)...);
}

struct MyStruct{
    MyStruct(int i, double d , std::string s){}
};


int main()
{
    //lvalue
    int five = 5;
    int myFive = create<int>(five);
    std::cout<<myFive<<"\n";

    std::string str{"lValue"};
    std::string str2 = create<std::string>(str);
    std::cout<<str2<<"\n";

    //rValue
    int myFive2 = create<int>(5);
    std::cout<<myFive2<<"\n";

    std::string str3 = create<std::string>(std::string("Rvalue"));
    std::cout<<str3<<"\n";

    std::string str4 = create<std::string>(std::move(str3));
    std::cout<<str4<<"\n";

    //Arbitrary number of arguments
    double doub = create<double>();
    std::cout<<doub<<"\n";
    MyStruct myStr = create<MyStruct>(2011,3.14,str4);

}

