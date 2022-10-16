/* PDF 171

For a container cont , use cont.empty() to see if the container is empty.
cont.size() returns the current number of elements, and cont.max_size()
returns the maximum number of elements cont can have. The maximum
number of elements is implementation defined.


! Use cont.empty() instead of cont.size()
! For a container cont , use the method cont.empty() instead of(cont.size() == 0) to determine if the container is empty. First,
! cont.empty() is, in general, faster than (const.size() == 0) ; second, the
! container std::forward_list has no method size() .

*/

#include<iostream>
#include<map>
#include<set>
#include<vector>

using namespace std;

int main()
{
    vector<int> intVec{1,2,3,4,5,6,7,8,9};
    map<string,int> str2Int = {{"bart",12345},{"jenne",34929},{"huber",840284}};

    set<double> douSet{3.14,2.5};

    cout<<intVec.empty()<<"\n"; //false
    cout<<str2Int.empty()<<"\n"; //false
    cout<<douSet.empty()<<"\n"; //false

    cout<<intVec.size()<<"\n"; //9
    cout<<str2Int.size()<<"\n"; //3
    cout<<douSet.size()<<"\n"; //2

    cout<<intVec.max_size()<<"\n"; //4611686018427387903
    cout<<str2Int.max_size()<<"\n"; //256204778801521550
    cout<<douSet.max_size()<<"\n"; //461168601842738790
}