#include <iostream>
#include "../header/vector.hpp"
int main(){
    Vector<int>v;
//     std::cout << "print use built in function" << std::endl;
//    // v.print();
//     for(int i = 0;i < v.get_size();i++){
//         std::cout << v[i] << " ";
//     }  
//     std::cout << std::endl;
//     std::cout << "implement push_back" << std::endl;
//    // v.insert(0,4);
//     v.push_back(4);
//     std::cout << "implement push_front" << std::endl;
    v.push_front(100);
    v.print();
    
    std::cin.get(); 
}