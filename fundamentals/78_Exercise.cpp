/* PDF 77

Exercise #
Define a class template that can be invoked with an int value.

OnlyInt(5); // ok
OnlyInt(5L); // ERROR


My first solution was wrong which was like this:


template<typename T>
class OnlyInt{
public:
    OnlyInt(int a){}
    OnlyInt(T) = delete;
};

int main()
{
    OnlyInt(5); // ok
    OnlyInt(5L); // ERROR
}

*/


#include<iostream>


class OnlyInt{
public:
    OnlyInt(int){}
    template<typename T>
    OnlyInt(T) = delete;
};

int main()
{
    OnlyInt(5); // ok
    OnlyInt(5L); // ERROR
}