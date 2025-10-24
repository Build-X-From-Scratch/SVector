#include <gtest/gtest.h>
#include "../header/vector.hpp"

TEST(push_testing,Push_back_basicTest){
    Vector<int>v  = {1,2,3,4,5};
    EXPECT_EQ(v.get_size(),5);
    v.push_back(6);
    EXPECT_EQ(v.get_size(),6);
    std::vector<int>expectation =  {1,2,3,4,5,6};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(push_testing,push_back_LoopTesting){
    Vector<int>v  = {1,2,3,4,5};
    EXPECT_EQ(v.get_size(),5);
    for(int i = 6;i <= 100;i++){
        v.push_back(i);
    }
    std::vector<int>expectation;
    for(int i = 1;i <= 100;i++){
        expectation.push_back(i);
    }
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}