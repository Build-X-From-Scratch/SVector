#include <bits/stdc++.h>
#include "../header/vector.hpp"
int main(){
    mystl::Vector<int>v = {100,200,300};
    mystl::Vector<int>x = {4,5,6};
    v.merge_reverse(x.begin(),x.end());
    v.print();
    return 0;
}