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

        MyDistance operator "" _soheil(unsigned long long int d)
        {
            return MyDistance(d*0.1);
        } 

        std::string operator "" _sam(const char* d , size_t)
        {
            return d;
        } 

    }

}

using namespace Distance::Unit;
int main()
{
    std::cout<<1_soheil<<"\n";
    std::cout<<"saman"_sam<<"\n";
    std::cout<<"1_km: "<<1.0_km<<std::endl;
    std::cout<<"1_m: "<<1.0_m<<std::endl;
    std::cout<<"1_cm: "<<1.0_cm<<std::endl;
    std::cout<<"In meters: "<<1.0_m+1.0_ft+1.0_mi<<"\n";

}