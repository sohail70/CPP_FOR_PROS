#include<iostream>
#include<chrono>
/* 
My summary for understanding the conversions: Think of std::ratio as value! so std::ratio<1,25> means every tick has the value of 1/25.
if you have 1000 ticks it means every tick has the value of 1/25 so in total your value is 40
now imagine we want to convert it to std::ratio<25,1> --->in this case every tick has the value of 25 -->it's a simple cross multiplication
so:
one tick has the value of 25
how many ticks has the value of 40
the answer is 1.6


Now imagine we have a varibale with the value 18300 (which is second)
and we want to convert it to min
in minutes--> each tick has value of 60(s)-->so create a var with std::ratio<60>
so how many ticks will be 18300?

don't try to think of the std::ratio as a multiplication because the compiler does the conversion think of it as a value of each tick

/*



The program is totally self-explanatory. The suffixes are expressive
enough. Making the correct additions is the job of the compiler. The time
literals support basic addition, subtraction, multiplication, division, and
modulo operations.
*/
 using namespace std::literals::chrono_literals;
//about std::ratio --> https://stackoverflow.com/questions/25005205/why-can-i-have-a-ratio-object-in-c
//std::ratio<1,3> one_third;
//count means tick and std::ratio in the duration is like a time unit I think
//see https://en.cppreference.com/w/cpp/chrono/duration
// tick is number of seconds per tick --> tick's period
//for example in the first line hour(20) means 20 ticks and if the ratio is <20,1> it means 20/1 which means every tick is 20 seconds so 400 seconds
//SO YOU ACTUALLY DEFINE THE (CUSTOME) UNIT OF YOUR NUMBER IN std::ratio
int main()
{
    typedef std::chrono::duration<long long , std::ratio<3600>> hour; //std::ratio<3600,1> is equivalant to std::ratio<3600>
    auto school_hour = hour(2); //Two with the unit of 3600 means 2 hours or 7200 seconds. It also means 2 ticks and every tick has the unit 3600/1 --> so 1 tick takes 3600 unit --> we specify this for when we want to convert to another unit
    //I think you can write 1h instead of the line above. I don't know whats the difference?! may be its there for when you wanna shift to minutes or miliseconds
    auto short_break = 900s; //900s --->the smallest unit between these variable is this and its in seconds so school_day_in_seconds variable's unit is in second now
    auto long_break = 30min; // 1800s

    auto school_way = 20min; //1200s
    auto homework = 2h; //7200s

    auto school_day_in_seconds = 1*school_way + 1*school_hour + 1*short_break + long_break + homework; //check out the auto: it's the smallest unit between them all
    

    std::cout<<"School day in seconds is :" << school_day_in_seconds.count()<<"\n";
    //Now that we have a variable with 18300 ticks (which we know semantically that's in seconds) we can change the unit of the ticks:
    std::chrono::duration<double , std::ratio<60,1>> school_day_in_mins = school_day_in_seconds;
    std::chrono::duration<double,std::ratio<3600,1>> school_day_in_hours = school_day_in_seconds;
    std::chrono::duration<double,std::ratio<1,1000>> school_day_in_milliseconds = school_day_in_seconds;

    std::cout<<"School day in hour: "<<school_day_in_hours.count()<<"\n";
    std::cout<<"School day in minutes: " <<school_day_in_mins.count()<<"\n";
    std::cout<<"School day in milliseconds: " <<school_day_in_milliseconds.count()<<"\n";
    
    
    
    //typedef std::chrono::duration<long long , std::ratio<1,25>> hour; 
    //auto school_hour = hour(1000); 
    //auto test = school_hour;
    //std::chrono::duration<double,std::ratio<25,1>> test2 = test;
    //std::chrono::duration<double,std::ratio<50,1>> test3 = test;

    //std::cout<<"test1: " <<test.count()<<"\n";
    //std::cout<<"test1: " <<test2.count()<<"\n";
    //std::cout<<"test1: " <<test3.count()<<"\n";
}