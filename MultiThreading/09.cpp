//conditional variable
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<future>
#include<vector>
#include<random>
#include<functional>
#include<chrono>

auto GenRandomValue = std::bind(std::uniform_int_distribution<>(0,10) , std::default_random_engine());

std::mutex g_mutex; 
std::condition_variable g_cv;
bool g_ready = false;
int g_data = 0;



void ConsumeData(int& data){}

void Consumer(){
    int data = 0;
    for(int i = 0 ;i<100 ; i++)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        //! start of critical section
        // if blocked, ul.unlock() is automatically called. -->//! vase hamin ul ro be onvan vorodi be func e wait dadim --> pas age block beshe wait unlock mikune mutex ro ta producer betone access kune be shared memory
        // if unblocked, ul.lock() is automatically called. --> //! lock mikune ta consumer betone g_ready va data ro check kune
        g_cv.wait(ul,[](){return g_ready;}); //waits for the notification and also it waits till g_ready is true
        //sample data
        data = g_data;
        std::cout<<"data: "<<data<<"\n";
        g_ready = false; //resets the ready flag for the next time ---> dar vaghe producer ham alan dare wait mikune bebine consumer rafte marhale bad ya na
        //! end of critical section
        ul.unlock();
        g_cv.notify_one();
        ConsumeData(data);
        ul.lock();
    }

}



void producer()
{
    for(int i = 0 ;i<100;i++){ //producer 100 ta data tolid mikune
        std::unique_lock<std::mutex> ul(g_mutex);
        //! start of critical section
        // Produce data
        g_data = GenRandomValue();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        g_ready = true;
        //! end of critical section
        ul.unlock(); //! khoroj az critical section
        g_cv.notify_one(); //! lozomi nadare toye crtical section bashi vase notify
        ul.lock();
        g_cv.wait(ul,[](){return g_ready == false;}); //agar consumer g_ready ro false kune va consumer notify_one ro ham befreste in wait inja rad mishe!
    }
}

int main()
{
    std::thread t1(Consumer);
    std::thread t2(producer);
    t1.join();
    t2.join();
}



/*  summary of conditional variables

sender :
    lock on a shared mutex --> typically std::lock_guard or unique_lock
    modify shared data while the lock is held
    call notify_one or notify_all--> the lock doesn't need to be held for notification


void t1()
{
    //...
    // Announce that data is produced
    g_cv.notify_one();
    //...
}




receiver:
    use std::unique_lock, on the same mutex -->//! deghat kun lock_guard nemishe chun bayad pass behse be func e wait ta betone automatic lock va unlock ro anjam bede (lock guard fek kunam ino nadare!)
    call wait--> if blocked, unlock() is called automatically.
                 if unblocked ul.lock() is called automatically


void t2(){
    std::unique_lock<std::mutex> ul(g_mutex);
    g_cv.wait(ul,[](){return condition;});
    //...
}
*/

/*
soal --> what if we only want to notify a specific thread ? faghat notify_one va ll ro darim
soal 2 --> how to break the infinte loop in producre and consumer? producer bege be consumer ke dg data nadaram 

*/





