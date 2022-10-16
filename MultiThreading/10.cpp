/*
lock() creates a critical section
lock() is an atomic operation --> lock will not get separated into multiple operations
lock() is a blocking operation --> yani age ye thread lock kune thread dg block mikune thread jadid ro ke natone access kune b shared memory
prior unlock() operations on the same mutex synchronize-with this lock() operation --> yani unlock dar ye thread synch mishe ba lock dar ye thread dg
undefined behavior if the thread already owns the mutex --> do ta lock back to back illegal hast
*/

/*
unlock()
its an atomic operation
its not a blocking operation
synchronizes-with the subsequent successful lock operations on the same object
The behavior is undefined if the calling thread doesn not own the mutex --> two unlock sequentially is illegal
*/


 // moshekle solution aval ma vase race conditon --> dead lock hast --> masaln thread 1 is waiting for 2 and 2 for 1
 // deadlock is a side effect of mutex and lock
 // ya masalan thread 1 is waitnign for 2 and thread 2 created an exceptionand never reply back!



 //Its more than mutual exclusion --> sequential consistency

/*
void f1() //thread1 runs f1
{
    std::lock_guard<std::mutex> lg(std::mutex);
    g_x = g_x + 1;//crtical section //g_x is a global variable
}

void f2() //thread2 runs f2
{
    std::lock_guard<std::mutex> lg(std::mutex);
    g_x = g_x + 2; //crtical section
}
*/
/*
ya f1 run mishe aval bad f2 ya f2 run mishe aval bad f1 --> because we have critical section
az koja malom bad inke f1 karesh tamom shod natije visible mishe vase f2? chun goftim reslt g_x dar f1 mire maslan to l1 cache ke may not be visible to f2 bashe
furtunately c++ standrads requires that unlock() synchornizes with lock(): //! this implies the values written in f1 will be seen by f2 --> yani values written by f1 are reuqired to be picked up by f2
yani unlock e critical section e f1 sync bashe be lock e critical section e f2
yad avari mikunam ke dar destructor lock_guard --> unlock be sorate implicit hast
va ye implicit lock dar constructor lock_guard hast
pas mutex faghat baraye race conditon nist balke vase sequential consistenyc ham hast ke access dashte bashe be reulst thread ha
! so if you want some memory location to be picked up by the other threads u need to put it inside mutex
*/




/* A closer look to conditional vars
can we wai wake up spuriously? yani --> can I wake up without anyone sending us any notification?
yes
The OS sometime wakes threads up spuriously --> that's why we use the predicate --> predicate protects us against spurious wake up --> age true bood wake up kunim
so wait can be called and passed for no apparent reason --> implementation OS injoorie


*/

/* can notifications get lost?? age critical section nadashte bashim yani dar code producer va consumer unique_lock haro nazarim 
onvaght race conditon rokh mide 
chun g_cv.notify_one() mojod dar producre mikhad g_cv ro notify kune va dar hamin hal g_cv.wait(ul) dar consumer ham mikhad be g_cv dastrasi peyda kune
pas age masaln consumer aval run beshe az line g_cv.wait(ul) rad beshe (spurious wake up ) va badesh producer run beshe notify_one esh lost mishe


so can my notidicaions get lost? No ! because mutex(sequential consistency )+ predicate

pas vaghti data ro thread one beroz kard va g_cv ro notify kard thread 2 ham chun wait karde hala notify mishe ---> sequential consistency
hala age az bad hadese thread 2 aval run beshe baz ham moshkeli nist chun predicate darim thread 2 ro sleep mikune yani az line e wait rad nemishe! ta zamani ke notification biad
*/


/*
! kholase ---> protect a conditional variable using a mutex
            ! always use a predicate 

*/





/* summary in ghesmat --> ghesmate 2 

if you have shared vars, check for race conditions
    use mutex for mutual exclusion and sequential consistency
use conditional vars for thread communication and message passing
Lock(), and wait() are blocking actions:
    beware of deadlock!
Sharing is not caring
    Avoid and minimize shared varibales as much as you can 
*/