#include <iostream>
#include "../header/vector.hpp"
using namespace mystl;
int main(){
    Vector<int>v = {100,200,300};
    std::cout << "print use built in function" << std::endl;
   // v.print();
    for(int i = 0;i < v.get_size();i++){
        std::cout << v[i] << " ";
    }  
    mystl::Vector<int>a = {500,600,700};
    a.erase(a.begin() + 0);
    a.print();
    return 0;
}