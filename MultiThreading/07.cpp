// lock unlock


#include<mutex>

#include<iostream>
#include<thread>
#include<vector>

std::mutex g_mutex ; //Mutex is shared --> its shared amongst all the threads that are using critical section

unsigned long g_counter;

void Incrementor() // each thread is counting 100 times and we have 100 threads so the result should be 10000 and because of mutex we get the 10000 each time we run the code
{
    for(size_t i = 0 ; i <100 ; i++)
    {
        g_mutex.lock(); //to start your critical section
        g_counter++; //!this is the critical section which is between lock and unlock - movazeb bash inja age exception rokh bede ye dafe az for loop miaym biron va mutex unlock anjam nemishe va in bade chun dg hich thread ee nemitone bere tosh!
        g_mutex.unlock(); // to end your critical section
    }
    
}

int main()
{
    std::vector<std::thread> threads;
    for (int j = 0 ; j<100; j++)
    {
        threads.push_back(std::thread(Incrementor));
    }

    for(std::thread &t : threads)
    {
        t.join();
    }
    std::cout<<g_counter<<"\n";
     
}


/*
you need one mutex per critical section and it has to be shared variable among all the threads that are using it
lock and unlock should match --> yani bad az lock bayad hatman unlock bashe va do ta bakc to back lock ya back to back unlock nadarim!
Don't forget to unlock --> age yadet bere lock roye ye mutex mimone va dead lock khahim dasht 
nokte mohem ine ke age exception dar critical section rokh bede --> az for loop kharej mishim va unlock nemishe ---> mutex remains locked for ever--> other threads will not have chance to get into critical section  
*//*
you need one mutex per critical section and it has to be shared variable among all the threads that are using it
lock and unlock should match --> yani bad az lock bayad hatman unlock bashe va do ta bakc to back lock ya back to back unlock nadarim!
Don't forget to unlock --> age yadet bere lock roye ye mutex mimone va dead lock khahim dasht 
nokte mohem ine ke age exception dar critical section rokh bede --> az for loop kharej mishim va unlock nemishe ---> mutex remains locked for ever--> other threads will not have chance to get into critical section  
//! c++ ye lock guard gozashte vase hale in moshkel --> RAII (resource acquisition is initialization) , automatic lock/unlock



void Incrementor() 
{
    for(size_t i = 0 ; i <100 ; i++)
    {
        std::lock_guard<std::mutex> guard(g_mutex); //be mahze inke construct beshe be sorate automatic mutex lock mishe va critical section ha badesh nevsehte mishe va be mahze out of scope shodan unlock be sorate automatic farakhani mishe pas niazi nist lock va unlock ro explicit anjam bedi 
        g_counter++; //critical section
    }
    
}


*/