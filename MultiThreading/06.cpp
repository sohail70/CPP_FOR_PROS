//javabe in problem hamishe 10000 nemishe bekhatere race condition --> each threads tries to increment while they are doing thing parallel --> sp g_counter is shared resource
// even incrementation is not atomic --> it requires reading --> then incrementing then writing
// pas har thread procesye read-increment-write ro byayad anjam bede 
/*
moshkel injast ke masalan thread 1 meghdare g_counter ro read mikune be 1 ---> dar hamin heyn thread 2 ham read mikune g_counter ro va  0 daryaft mikune
hala thread 1 increment mikune va write mikune 1 ro va thread 2 ham 0 ee ro ke daryaf karde bod incerement mkune va 1 ro write mikune
wrtie of thread 2 happens after write of thread 1 ---> mikhastim result 2 bashe vali result shode 1 --> dar kol entezar dashtim ke thread ha yeki pas az digari daryaf kunan vaili injoori nist ghazie
haghighat badtar az ine --> chun reading ham atomic operation nist --> reading mishe 2 ta proces ---> thread 1 first half ro read mikune - hala dar hamin heyn thread 2 
miad va read o incement o write ro baham anjam mide va hala thread 1 ke mikhad second half ro read kune ye javabe junk ro darayf mikune 
write ham hamine!
baz ham badtar az ine ghazie --> your machine fixes your code ---> what you write is not get executed 

code ---> compile optimize mikune ba reordering va loop unrolling -->mire be cpu va cpu ha m migire va optimizat mikune ba out of order execution va branch prediction --> bad ina write mishe be cache -dar cache prefetch va buffering anjam mishe
--> after several levels of cache now you write on main memory
pas compile va cpu va cache in vasat code ro dastkhooshe taghir gharar midan
alan hamin cache dastan mishe dar multithreading ---> shekl paeen: pas thread mostaghim ro memory nemirize balke mirize to l1 cache 
va thread badi ham mirize to l1 chache khodesh va az ham dige ham khabar nadaran

thread --> l1 cache --> l2 cache-- 
                        /         \
thread--> l1 cache------           ---> l3 cache ---> memory
                                  /
thread --> l1 cache--> l2 cache--
                         /
thread ---> l1 chach----



race condition ---> undefined behaviour ---> accessing a shared resource ---> they are using operation that are not atomic
if read  and increment and write were atomic this wouldn't have happened.
operation get interleaved ---> maslana read mishe dou ghesmat va dar hamin heyn memory curroupted mishe
due to optimiztion the actual executed code mightbe different --> in single thread optimization is not observable bu in mult thread opt become observable
! the main problem is with shared data across threads ---> race condition + wrong order of operations


What is a solution --->3 solutions --> Mutex and locks(lock/unlock -  lock-guard - unique_lock - shared_lock - scoped_lock) - std::atomic(memory modesl) - abstraction(techniques like CSP - actors - map reduce)
in session ro mutex ---> mutual exclusion --> goftim do ta thread mikhan beran samte shared memory ---> in khoob nist ---> in shread memory ro mindazim toye ye hefaz be esme
critical section ke yani faghat ye thread mitone bere tosh --> age 1 bere 2 bayad wait kune va agar 2 bere thread1 bayad wait kune
pas thread 1 read+increment+write ro anjam mide va bad thread2 inkaro anjam mide va ya bar aks! --->//! so no overlap between thread1 and 2
now thread 1 do the f1st half read the n2nd half read then increment and write and then thread 2 starts his job ---> or vice versa
so mutex solves the problem


so mutex is:
Either-me-or-you ploicy ---> mutual exclusion 
makes operations atomic
if one thread is in the critical section -=--> the other must block and wait

*/

#include<iostream>
#include<thread>
#include<vector>

unsigned int g_counter = 0 ;

void Incrementor(){
    for(size_t i = 0 ; i<100 ; i++)
    {
        g_counter++;
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