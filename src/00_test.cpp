#include<iostream>

class Account{
    public:
        Account(double amt): amount(amt){}

        double getBalance() const{
            return amount;
        }

        private:
            double amount;
};


class BankAccount: public Account{
    public:
        BankAccount(double amt): Account(amt) {}
};  

class WireAccount: public Account{
    public:
        WireAccount(double amt): Account(amt) {}
};

class CheckingAccount: public BankAccount, public WireAccount //This class has access to the getBalance methods of both classes.
{
    public:
        CheckingAccount(double amt): BankAccount(amt), WireAccount(amt){} //! Khodam: alan har kodum az az ina ke initilize beshe , har kodom ye bar Account(amt) ro ejra mikunan ke in baes mishe do bar in kar anjam begire
};

int main()
{
    CheckingAccount checkingAccount(100.0);
    //checkingAccount.getBalance(); //!ERROR---> ambiguous function
    /*
    If we try to call the getBalance method using the instance of
    CheckingAccount class, it will give us an error, but if we call it with the
    name of the base class along with the scope operator :: then it works
    fine.
    */
    std::cout<<checkingAccount.BankAccount::getBalance()<<"\n";
    std::cout<<checkingAccount.WireAccount::getBalance()<<"\n";
}