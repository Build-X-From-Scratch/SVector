#include <iostream>
#include "../header/vector.hpp"
int main(){
    Vector<int>v = {1,2,3};
    v.insert(v.begin() + 0,5,100);
    for(auto i = v.begin();i != v.end();i++){
        std::cout << *i << " ";
    }
    return 0;
}