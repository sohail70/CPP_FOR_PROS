#include<iostream>
#include<ostream>

namespace Distance
{
        class MyDistance
        {
            public:
                MyDistance(double distance):m(distance){}



            friend double operator +(const MyDistance& a ,const MyDistance& b)
            {
                return a.m + b.m;
            }

            friend double operator -(const MyDistance& a ,const MyDistance& b)
            {
                return a.m - b.m;
            }

            friend double operator *(const MyDistance& a , const MyDistance& b)
            {
                return a.m*b.m;
            }

            friend std::ostream& operator <<(std::ostream& out,const MyDistance& dist)
            {
                out<<dist.m<<" m";
                return out;
            }

            private:
                double m;
        };


    namespace Unit
    {
        MyDistance operator "" _km(long double d)
        {
            return MyDistance(1000*d);
        }

        MyDistance operator "" _m(long double d)
        {
            return MyDistance(d);
        }

        MyDistance operator "" _cm(long double d)
        {
            return MyDistance(0.01*d);
        }

        MyDistance operator "" _ft(long double d)
        {
            return MyDistance(0.3048*d);
        }

        MyDistance operator "" _mi(long double d)
        {
            return MyDistance(1609.344*d);
        } 

    }

}

using namespace Distance::Unit;
int main()
{
    Distance::MyDistance work = 63.0_km;
    Distance::MyDistance work_per_day = 2 * work;
    Distance::MyDistance abbrevationToWork = 5400.0_m;
    Distance::MyDistance workout = 2 * 1600.0_m;
    Distance::MyDistance shopping = 2 * 1200.0_m;

    
    Distance::MyDistance myDistancePerWeek = 4*work_per_day- 3*abbrevationToWork + workout + shopping;


    std::cout<<"In meters: "<<myDistancePerWeek<<"\n";

}