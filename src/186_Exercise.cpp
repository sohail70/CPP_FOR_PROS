/* PDF 185

! std::forward_list has a reduced interface, so we can’t use it with a lot of
! STL algorithms.

What are the characteristics of the methods of std::forward_list ?


Pointers that might help us to solve the above exercise:

Accessing of an arbitrary element is slow because we might have to
iterate forward through the whole list.

To add or remove an element is fast, if the iterator points to the right
place.

If we add or remove an element, the iterator remains valid.

We can only move forward with the iterator.



*/