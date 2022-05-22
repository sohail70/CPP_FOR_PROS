/* PDF 74

Static methods #

Explanation #
The static attribute, deposits , is being initialized on line 8. Whenever the
constructor is called, its value is incremented by 1 .

On lines 22 and 29, we can see that the static getDeposits() method can
be called without an instance of Account .

After the creation of account1 and account2 , the value of deposits is
incremented to 2 . We can check this by invoking getDeposits() on the
objects, as done on lines 27 to 29, or by using the scope resolution
operator with the class name.


*/
#include<iostream>

class Account{
    public:
        Account(){deposits++;}

        static int getDeposits()
        {
            return Account::deposits;
        }

    private:
        static int deposits;
};
int Account::deposits = 0;

int main()
{ 
    std::cout<<Account::getDeposits()<<"\n";

    Account account1;
    Account account2;

    std::cout<<account1.getDeposits()<<"\n";
    std::cout<<account2.getDeposits()<<"\n";
    std::cout<<Account::getDeposits()<<"\n";


}