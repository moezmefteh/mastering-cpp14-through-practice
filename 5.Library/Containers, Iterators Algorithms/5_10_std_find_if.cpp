#include <iostream>
#include <vector>
#include <algorithm>
int main()
{
    std::vector<int> int_vec{5,6,8,78,17};
    std::vector<int>::iterator it;

    it = std::find_if(int_vec.begin(),int_vec.end(),[](int a){
        return a < 0;
    });

    if (it!=int_vec.end())
        std::cout<<it-int_vec.begin();
    else 
        std::cout<<-1;
    return 0;
}