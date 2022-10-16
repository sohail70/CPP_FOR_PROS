/* PDF 100
Destructor Calls

WE'LL COVER THE FOLLOWING
• Sequence followed by destructor calls
    • Example

Sequence followed by destructor calls #

! When we (directly or indirectly) call a destructor, a series of destructor calls may be triggered.

! This guarantees that each base object is properly destructed.

! The sequence of destructor calls starts with the most derived class and
! ends with the base class.

Example #
In the commented portion, the destructor sequence is mentioned when
delete is called:

struct A{};
struct B: A{};
struct C: B{};
C* c = new C; // A -> B -> C
delete c;     // ~c -> ~A -> ~A

! We might have noticed that constructor calls follow the exact opposite
! behavior of destructor calls.

*/