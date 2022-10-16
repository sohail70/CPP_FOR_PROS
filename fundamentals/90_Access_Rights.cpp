/* PDF 92
Access Rights
WE'LL COVER THE FOLLOWING
• Scope of access rights
• Is-a relations
    • public
    • protected
    • private

Scope of access rights #
! The access rights of the inheritance determine which functionalities of the
! base class can be used in the derived class.

! A class can be derived public , protected , or private from its base class.
! For classes, the default access right is private ; for structs, it’s public .


! class BankAcc: Acc{...} is the same as class BankAcc: private Acc{...}

Is-a relations #
! The derived class and the base class have an is-a relationship. Public
inheritance is called an is-a relationship because the derived class has the
same interface as the base class. The derived class is a specialization of the
base class.

public #
class BankAccount: public Account{ ...

! public and protected members in the Account class are public andprotected in the BankAccount class.


protected #
class BankAccount: protected Account{ ...

! public and protected members in the Account class are protected in the BankAccount class.


private #
class BankAccount: private Account{ ...

! public and protected members in the Account class are private in the BankAccount.

*/