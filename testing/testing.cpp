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
TEST(push_testing,push_front_BasicTest){
    Vector<int>v = {1,2,3,4,5};
    EXPECT_EQ(v.get_size(),5);
    EXPECT_EQ(v.front(),1);
    v.push_front(100);
    EXPECT_EQ(v.get_size(),6);
    EXPECT_EQ(v.front(),100);
    std::vector<int>expectation = {100,1,2,3,4,5};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(push_testing,push_front_LoopTesting){
    Vector<int>v;
    EXPECT_TRUE(v.is_empty());
    for(int i = 1;i <= 100;i++){
        v.push_front(i);
    }
    std::vector<int>expectation;
    for(int i = 1;i <= 100;i++){
        expectation.push_back(i);
    }
    expectation = std::vector<int>(expectation.rbegin(),expectation.rend());
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}