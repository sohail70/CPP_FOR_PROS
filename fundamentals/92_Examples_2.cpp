/* PDF 93
Example 2: Abstract base class inheritance #

Explanation #

We have created a pure virtual class Abstract and we cannot make an
instance of this class as it will give an error.

The classes Man and Woman inherit publically from the class HumanBeing .

getSex function is pure virtual so we cannot make an instance of
HumanBeing in main .

The instances of the Man and Woman classes can access the getSex
function by using the . operator and they must be overridden in derived
classes.



*/

#include<iostream>
#include<string>

class Abstract{
    public:
        virtual ~Abstract() = 0;
};

Abstract::~Abstract(){};

class Concrete: public Abstract{};

class HumanBeing{
    public:
        HumanBeing(const std::string n): name(n){
            std::cout<< name <<" created. "<<"\n";
        }

        virtual std::string getSex() const = 0;

    private:
        std::string name;
};

class Man: public HumanBeing{
    public:
        // using HumanBeing::HumanBeing
        Man(const std::string n): HumanBeing(n){}

        std::string getSex() const{
            return "male";
        }
};


class Woman: public HumanBeing{
    public:
        // using HumanBeing::HumanBeing
        Woman(const std::string n): HumanBeing(n){}

        std::string getSex() const{
            return "female";
        }
};


int main()
{
    //Abstract abstract; //Error
    Concrete concrete;

    //HumanBeing humanBeing("grimm"); //Error

    Man schmidt("Schmidt");
    Woman huber("huber");

    std::cout<<schmidt.getSex()<<"\n";
    std::cout<<huber.getSex()<<"\n";

}   

