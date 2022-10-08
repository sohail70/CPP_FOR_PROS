#include<iostream>
#include<unordered_set>

void getInfo(const std::unordered_set<int>& hash)
{
        std::cout<<hash.bucket_count()<<"\n";
        std::cout<<hash.load_factor()<<"\n";
}

int main()
{
        int arr[100];
        for (int i = 0 ; i<100 ; i++)
                arr[i] = (rand() % 100) + 1;
        std::cout<<arr<< " "<<sizeof(arr) <<" "<<sizeof(int)<<"\n";
        std::unordered_set<int> hash(arr,arr+sizeof(arr)/sizeof(int));

        std::cout<<hash.max_load_factor()<<"\n";

        getInfo(hash);
        hash.insert(500);
        std::cout<<hash.bucket(500)<<"\n";

        getInfo(hash);
        std::cout<<"\n";
        hash.rehash(500);
        getInfo(hash);
        std::cout<<hash.bucket(500);
        std::cout<<"\n";
}