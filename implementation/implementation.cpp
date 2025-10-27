#include <iostream>
#include "../header/vector.hpp"
int main(){
    Vector<int>v = {100,200,300};
    std::cout << "print use built in function" << std::endl;
   // v.print();
    for(int i = 0;i < v.get_size();i++){
        std::cout << v[i] << " ";
    }  
//     std::cout << std::endl;
//     std::cout << "implement push_back" << std::endl;
//    // v.insert(0,4);
//     v.push_back(4);
//     std::cout << "implement push_front" << std::endl;
//     v.push_front(100);
//     v.print();
//     v.insert(v.begin() + 2,2);
    // implement insert
    std::cout << "insert single element \n";
    Vector<int>s = {1,2,3,4,5};
    // s.insert(s.begin() + 2,2);
    // std::cout << "range element \n";
    // s.insert(s.begin() + 2,4,2);
    s.print();
    std::cout << "\nproses erase single element \n";
    s.erase(s.begin() + 2);
    s.print();
    std::cout << "proses push_front use loop \n";
    Vector<int>a;
    for(int i = 1;i < 20;i++){
        a.push_front(i);
    } 
    a.print();
    std::cout << "\nrule of three \n";
    Vector<int>b(a);
    return 0;
}