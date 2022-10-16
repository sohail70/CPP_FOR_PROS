// unique lock --> lock guard + and option to lock adn unlock
// so instead of using lock guard use unique_lock age mikhay alave bar RAII betoni az func haye lock va unlock use kuni
/*
std::mutex g_mutex;
unsinged long g_counter;

void Incrementor()
{
    for(size_t i = 0 ; i<100 ; i++)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        g_counter++;
        ul.unlock();
        std::cout<<"Doing sth non-critical.."<<std::endl;
        ul.lock();
    }
}

*/



/* shared_lock --> now we have multiple readers

std::shared_mutex g_shared_mutex; 
unsgined long g_counter;


void Incrementor()
{
    for(size_t i=0 ; i <100 ; i++)
    {
        std::unique_lock<std::shared_mutex> ul(g_shared_mutex); //! we use unique lock for all the writes
        g_counter++; //! critical section is here -->BUT ONLY A SINGLE THREAD CAN BE HERE --> SO WE HAVE ONLY ONE WRITER
    }
}


void ImJustAReader()
{
    for(size_t i = 0 ; i<100 ; i++)
    {
        std::shared_lock<std::shared_mutex> sl(g_shared_mutex); //! we use shared lock for all the readers
        std::cout<<g_counter<<"\n"; //! crtical section is here --> BUT MULTIPLE THREADS CAN BE HERE(TO READ!) IF NO WRITER HAS LOCKED
    }
}


*/



/* Multiple locks --> lock on multiple mutexes!
std::mutex g_mutex1 , g_mutex2;

unsigned long g_counter;
//! dead lock --> because thread 1 is wating for thread 2 and thread 2 is wainting for thread 1
void Incrementor_Bad1() //! chera in bade? chun momkene ye thread dg haminkaro bokone monteha in reverse order. alan dar func aval thread 1 lock karde ro mut1 va montazer dovomi hast va dar func 2 thread2 lock karde va montazer thread 1 hast.THIS IS DEADLOCK!
{
    for(size_t i = 0 ; i<100 ; i++)
    {
        std::lock_guard<std::mutex> lock1(g_mutex1); //! aval ino lock kardim 
        std::lock_guard<std::mutex> lock2(g_mutex2); //! dovom ino lock kardim
        g_counter++;
    }
}


void Incrementor_Bad2()
{
    for(size_t i = 0 ; i<100 ; i++)
    {
        std::lock_guard<std::mutex> lock2(g_mutex2);
        std::lock_guard<std::mutex> lock1(g_mutex1);
        g_counter++;
    }
}

//! ravesh bala ghalate --> solution --> std::lock --> it has a feature called all-or-nothing

void Incrementor_better()
{
    for(size_t i = 0 ; i<100 ; i++)
    {
        //lock both mutexes without deadlock
        std::lock(g_mutex1 , g_mutex2); //tries to lock both of the mutexes --> age yekodom ro nakone nemishe yani hichkodom ro lock nemikune --> ya hard do ya hichi --> all or nothing    
        //! critical section be lafasele bade lock nevsehte mishe! --> se khate paeen critical section hastan
        // make sure both already-locked mutexes are unlocked at the end of scope
        std::lock_guard<std::mutex> lock1(g_mutex1  , std::adopt_lock); //chun dar bala lock kardim --> bayad lock_guard bezarim ta badan bad az ascope, unolock beshe
        std::lock_guard<std::mutex> lock2(g_mutex2 , std::adopt_lock); //! std::adopt_lock yani be sorate automatic lock nakon chun do khat balatar lock kardim khodemon! --> so it assumes the mutex is already locked
        g_counter++;
    }
}


//! ravesh bala behtare vali clean syntax nist!! -->c++17 ye syntax behtar dorost karde vase in kar!
void Incrementor_Best(){
    for(size_t i  = 0 ; i<100 ; i++)
    {
        std::scoped_lock scoped_lock_name(g_mutex1,g_mutex2); //! All or nothing with RAII --> az scope harej beshe khodesh unlock mikune!
        g_counter++; //! critical section
    }
}


*/



///////////////////summary
/* --> func haye paeen niaz dare ke ye shared variable e mutex ya shred_mutex ijad kuni ghabl az use kardan func haye paeen
Direct lock and unlock on std::mutex ---> need to remember to unlock - incase of exception, mutex remains locked --> age in do ro mitoni hal kuni azash use kun
std::lock_guard --> locking with RAII (just declare and use)
std::unique_lock --> std::lock_guard + optional lock/unlock
std::shared_lock --> std::unique_lock + let reader read! --> multiple readers so that you don't block them unnecessarily
std::scoped_lock --> similar to std::lock_guard, but for multiple locks without deadlock 

hame func haye bala yekar mikunan! --> hamashoon wrapper roye std::mutex hastan!
*/









///////////////////////CONDITIONAL VARIABLE ///////////////////////////////
/*
main reason --> one thread wants to send a msg to another thread - --> thread communication
thread 1 --> prduce data ro ijad mikune 
thread 2 ham in data ro mikhad ---> so it need to wait for data to become available
thread 1 bayad notify kune thread 2 ro ke data amadast 

producer consumer is a common pattern --> chize na ashanee nist ---> mesle client server --> ya dar pipeline cpu --> ya dar dma controller --> dar multithredaing ham hamine ke niaz be synchronization hast
one easy way is to have thread 1 (producer ) to access some shared memory --> g_data and g_ready
thread 1 ke data ro produce kard mirize to g_data ---> g_ready ro ham true mikune ---> chun shared memory hast thread 2 mitone flag ro bebine
chun shared memory hast --> ! so we need a critical section for this shared memory


so option 1 ---> thread 2 is monitoring the critica section ---> bakhshe vasat bayad critical section beshe chun shared memory hast

thread 1        --------------> g_ready(flag) <-----------------   thread 2
Produce Data    \_____________ > g_data <______________________/ consume data



nahveye implementation --> //! The bad way of implementation!

void producer()
{
    for(int i = 0 ; i<100 ; i++)
    {
        std::uinque_lock<std::mutex> ul(g_mutex); //! vaghti ino minevisi yani section badi critical section hast
        //! critical section starts
        //produce data
        g_data = GenRandomValue();
        //Announce that data is produced
        g_ready = true;

        ul.unlock();
        std::this_thread::sleep_for(std::chrono::miliseconds(20));
        ul.lock();
    }
}


void consumer(){
    int data;
    for(int i = 0 ; i<100 ; i++)
    {
        std::unique_lock<std::mutex> ul(g_mutex);
        //Busy waiting  --> //! this is not efficent ---> so this code is bad --> because you keep the cpu busy in this while loop and you keep locking and unlocking mutex --> vase behtar shodan mishe delay gozasht dar while loop ke ye meghdar behtare!
        while(!g_ready) //! monitoring ready dare inaj anjam migire
        { //! benzaraet chera unlock va lock mikunim inaj? chun age consumer aval execute beshe!
            ul.unlock();//! age consumer aval run beshe chun bala dar unique lock mutex moshtarak ro lock karde bayad unlock kune ta producer az on taraf betone data ha ro prduce kune
            //! va age prodcuer slow bashe consumer miad lock mikune dar paaen va dobare g_ready ro check mikune!
            std::this_thread::sleep_for(std::chrono::miliseconds(10)); //! so that you burn less cpu cycles --> garche code hamchenan behine nist
            ul.lock();
        }
        g_ready = false;
    }
}

/////////////////////RAVESH BEHTAR: conditional varibale////////////////////
hamechi mesle modele ghable faghat ye g_cv yani conditonal varibale ham darim

                  ------------->g_cv --------------------------
                /                                               \
thread 1        --------------> g_ready(flag) <-----------------   thread 2
Produce Data    \_____________ > g_data <______________________/ consume data


bakhse vasat mishe shared_memory ke bayad critical section beshe ta jeloye race conditooonin ro begire
thread 1 produce data mikune flag ro set true mikune va send notification mikune be g_cv
thread2 rather than monitorin waits for a notification --> so it recieves notifaction
so the conditonal varibale is a notification chanel between priducer and consumer
dorost mesle notification mobile phone hast --> you don't keep cheking your msges --> vaghti msg byad notification migiri

//implementation
define a mutex and conditional varibale as shared varibales
std::mutex g_mutex
std::condition_varibale g_cv;
bool g_ready = false;
int g_data = 0;



void prodcuer(){
    //..
    // Announce that data is prodcued
    g_cv.notify_one(); //az notify all ham mitoni estedfade kuni agar chandta thread dari
    // ...
}

void consumer(){
    //...
    g_cv.wait(ul , [](){return g_ready;}); //wait until g_ready becomes true // param aval lock on a mutex hast va param 2 predicate hast
}


*/