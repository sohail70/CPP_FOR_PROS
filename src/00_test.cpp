#include<iostream>
#include<vector>
#include<algorithm>


class Mean{
        public:
                void operator()(int v)
                {
                        num++;
                        mean = (mean*(num-1) + v)/ num;
                }       
                void printMean() const {std::cout<<mean<<"\n";}
        private:
                int sum{0};
                int num{0};
                double mean;
};      



int main()
{
        std::vector<int> myVec {1,2,3,4,5,6,7,8,9,10};
        auto f = std::for_each(myVec.begin(),myVec.end(),Mean());
        f.printMean();
}