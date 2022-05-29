/* PDF 94
Example 4: Base class inheritance #

Explanation #

We have created two classes,i.e., Account and BankAccount .

The class BankAccount inherits publically from the Account class.

We have created two instances of these classes in main .

For the BankAccount class, if the cur parameter is not passed, then the
default EUR is passed to the Account class.


*/


#include<iostream>
#include<string>


class Account{
    public:
        Account() = default;

        Account(double amt , std::string c): amount(amt) , cur(c){
            std::cout<<amount<<"\n";
            std::cout<<cur<<"\n";
        }

    private:
        double amount;
        std::string cur;
};

class BankAccount: public Account{
    public:
        BankAccount(double amt , std::string n): Account(amt,"EUR"),name(n){
            std::cout<<"BANCK ACCOUNT NAME: "<<name<<"\n";
        }
    private:
        std::string name;
};


int main()
{
    Account acc(100.0,"USD");
    std::cout<<"\n";

    BankAccount bankAcc(200.0 , "grimm");
    std::cout<<"\n";
}