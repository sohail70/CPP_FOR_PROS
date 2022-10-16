/* PDF 93
Examples
WE'LL COVER THE FOLLOWING
• Example 1: Inheritance
    • Explanation
• Example 2: Abstract base class inheritance
    • Explanation
• Example 3: Access rights in inheritance
    • Explanation
• Example 4: Base class inheritance
    • Explanation


Example 1: Inheritance #
Explanation #

We have created two classes, i.e., Account and BankAccount .

The BankAccount class inherits the Account class publicly in line 25.

The public member functions of the Account class are available to the
BankAccount class and we can access them using the . operator (line 46).
*/

#include<iostream>

class Account{
    public:
        Account(double b): balance(b){}

        void deposit(double amt){
            balance+=amt;
        }

        void withdraw(double amt){
            balance -= amt;
        }

        double getBalance() const{
            return balance;
        }

    private:
        double balance;
};

class BankAccount : public Account{
    public:
        BankAccount(double b): Account(b){}

        void addInterest()
        {
            deposit(getBalance()*0.05);
        }
};

int main()
{
    BankAccount bankAcc(100.0);
    bankAcc.deposit(50.0);
    bankAcc.deposit(25.15);
    bankAcc.withdraw(30);
    bankAcc.addInterest();

    std::cout<<bankAcc.getBalance()<<"\n";

}