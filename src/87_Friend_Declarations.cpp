/* PDF 89
Friend Declarations
WE'LL COVER THE FOLLOWING
• Rules:

! The friend declaration appears in a class body and grants a function or
! another class access to private and protected members of the class where the
! friend declaration appears. Friends have access to all members of a class.


! A class can declare friendship to a function, a method, or a class.


Rules: #
! 1. The declaration of a friendship can be anywhere.
! 2. The access specifier of the friendship declaration is not relevant.
! 3. Friendship cannot be inherited (your friend’s children are not your
! friends).
! 4. Friendship is not transitive (a friend of your friend is not your friend).


! Access specifiers have no effect on the meaning of friend declarations (they
! can appear in private: or in public: sections, with no differences).

! A friend has full control of the internals of a class.
*/