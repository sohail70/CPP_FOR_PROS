// Mutex and conditional variables

/*
why mutex? race condition ? ---> to or more thread accessing th shared resource --> they are competing  --> racing to write on variable g_x for example
this is undefined behaviour

*/

#include<iostream>
#include<vector>
#include<thread>

unsigned long g_x;

int main()
{
    for(int i = 0 ; i<1000 ; i++)
    {
        auto t1 = std::thread([]() {g_x = 1;}); //har az gahi in success mishe har az gahi paeeni
        auto t2 = std::thread([](){g_x = 2;});
        t1.join();
        t2.join();
        std::cout<<g_x<<" , ";
    }
    std::cout<<"\n";
}