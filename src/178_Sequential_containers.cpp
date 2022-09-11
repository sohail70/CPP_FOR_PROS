/*  PDF 175

The sequential containers have a lot in common, but each container has its
special domain. Before we dive into the details, we’ll look at an overview of all
five sequential containers of the std namespace.


! The sequential containers:

criteria                            Array                                               vector                                              Deque                                                   list                                                Forward list
size                                static                                              dynamic                                             dynamic                                                 dynamic                                             dynamic
Implementation                      static array                                        dynamic array                                       sequence of arrays                                      doubled linked list                                 single linked list
Access                              random                                              random                                              random                                                  forward and backward                                forward
Optimized for insert and delete at  -                                                   end: O(1)                                           begin and end:O(1)                                      begin and end: O(1) arbitrary: O(1)                 begin: O(1); arbitrary : O(1)  
memory reservation                  -                                                   yes                                                 no                                                      no                                                  no
Release of memory                   -                                                   shrink_to_fit                                       shrink_to_fit                                           always                                              always
Strength                            no memory allocation;minimal memory requirements    95% solution                                        insertion and deletion at the begin and end             insertion and deletion at an arbitrary position     fast insertion and deletion; minimal memory requiements
Weakness                            no dynamic memory; memory allocation                Insertion adn deletion at arbitrary position O(n)   Insertion and deletion at an arbitrary position O(n)    no random access                                    no random access


! A few additional remarks to bring to the table.
O(1) stands for the complexity (runtime) of an operation. So O(1) means that
the runtime of an operation on a container is constant and is independent of
the size of the container. Opposite to that, O(n) means that the runtime
depends linearly on the number of the elements of the container. What does
that mean for an std::vector ? The access time on an element is independent
of the size of the std::vector , but the insertion or deletion of an arbitrary
element with k-times more elements is k-times slower.

! Although the random access on the elements of an std::vector has the same
! complexity, O(1), as the random access on the element of an std::deque , that
! doesn’t mean, that both operations are equally fast.

! The complexity guarantee O(1) for the insertion or deletion of a double
! ( std::list ) or single linked list ( std::forward_list ) is only guaranteed if the
! iterator points to the right element.



! std::string is like std::vector
! Of course std::string is not a container of the standard template
! library. But from a behavioral point of view, it is like a sequential
! container, specifically an std::vector<char> . Therefore, we will treat
! std::string like an std::vector<char> .




*/