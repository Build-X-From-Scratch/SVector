#include <gtest/gtest.h>
#include <initializer_list>
#include <stdexcept>
#include <random>
#include "../header/vector.hpp"
using namespace mystl;
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
TEST(pop_testing,pop_back_BasicTest){
    Vector<int>v = {1,2,3,4};
    EXPECT_EQ(v.back(),4);
    v.pop_back();
    EXPECT_EQ(v.back(),3);
    std::vector<int>expectation = {1,2,3};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(pop_testing,pop_bac_Empty){
    Vector<int>v;
    EXPECT_TRUE(v.is_empty());
    EXPECT_THROW(v.pop_back(), std::runtime_error);
}
TEST(pop_testing,pop_back_LoopUntilEmpty){
    Vector<int>v;
    EXPECT_TRUE(v.is_empty());
    for(int i = 1;i <= 100;i++){
        v.push_back(i);
    }
    EXPECT_FALSE(v.is_empty());
    while(!v.is_empty()){
        v.pop_back();
    }
    EXPECT_TRUE(v.is_empty());
    std::vector<int>expectation = {};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Insert_Testing,Insert_single_Element){
    Vector<int>v = {1,2,3};
    EXPECT_EQ(v.get_size(),3);
    v.insert(v.begin() + 1,100);
    EXPECT_EQ(v.get_size(),4);
    std::vector<int>expectation = {1,100,2,3};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Insert_Testing,Insert_single_Element_EmptyContainer){
    Vector<int>v;
    EXPECT_TRUE(v.is_empty());
    v.insert(v.begin() + 0,100);
    EXPECT_FALSE(v.is_empty());
    std::vector<int>expectation = {100};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Insert_Testing,Insert_single_Element_Ntimes){
    Vector<int>v = {1,2,3};
    EXPECT_EQ(v.get_size(),3);
    v.insert(v.begin() + 1,5,100);
    EXPECT_EQ(v.get_size(),8);
    std::vector<int>expectation = {1,100,100,100,100,100,2,3};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(constructorTesting,rangeConstructor){
    Vector<int>a = {100,200,300};
    Vector<int>b(a);
    std::vector<int> x = {100,200,300};
    std::vector<int>y = {100,200,300};
    EXPECT_EQ(x,y);
}
TEST(constructorTesting,firstConstructor){
    std::vector<int>a = {100,200,300};
    Vector<int>b(a.begin(),a.end());
    std::vector<int>expectation = a;
    std::vector<int>actual;
    for(auto x: b){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Insert_Testing,InsertUseAnotherContainer){
    Vector<int>v;
    EXPECT_TRUE(v.is_empty());
    std::vector<int>lst = {1,2,3,4};
    v.insert(v.begin() + 1,lst.begin(),lst.end());
    std::vector<int>expectation = {1,2,3,4};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Insert_Testing,InsertInitializerList){
    Vector<int>v = {100,200,300};
    EXPECT_EQ(v.get_size(),3);
    EXPECT_FALSE(v.is_empty());
    v.insert(v.begin() + 1,{1,2,3});
    std::vector<int>expectation = {100,1,2,3,200,300};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(v.get_size(),6);
    EXPECT_EQ(actual,expectation);
}
TEST(Insert_Testing,InsertLargeContainer){
    Vector<int>v = {1,2,3};
    std::vector<int>tmp;
    for(int i = 100;i <= 150;i++){
        tmp.push_back(i);
    }
    v.insert(v.begin() + 1,tmp.begin(),tmp.end());
    std::vector<int>expectation = {1};
    for(int i = 100;i <= 150;i++){
        expectation.push_back(i);
    }
    expectation.push_back(2);
    expectation.push_back(3);
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Assign_test,AssignNelement){
    Vector<int>v = {1,2,3,4};
    EXPECT_EQ(v.get_size(),4);
    v.assign(4,0);
    std::vector<int>expectation;
    expectation.assign(4,0);
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Assign_test,AssignUseInitializerList){
    Vector<int>v = {1,2,3};
    EXPECT_EQ(v.get_size(),3);
    v.assign({100,200,300});
    std::vector<int>expectation,actual;
    expectation.assign({100,200,300});
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(Assign_test,AssignUseAnothersContainer){
    Vector<int>v = {100,200,300};
    EXPECT_EQ(v.get_size(),3);
    std::vector<int>a = {500,600,700};
    v.assign(a.begin(),a.end());
    std::vector<int>expectation,actual;
    expectation.assign(a.begin(),a.end());
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expectation);
}
TEST(delete_test,deleteSingleElementAtFront){
    Vector<int>v = {1,2,3,4,5};
    int size = v.get_size();
    EXPECT_EQ(v.get_size(),5);
    v.erase(v.begin() + 0);
    EXPECT_EQ(v.get_size(),size - 1);
    std::vector<int>expected,actual;
    expected = {2,3,4,5};
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expected);
}
TEST(delete_test,DeleteNElement){
    Vector<int>v = {100,200,300,400,500,600,700};
    int size = v.get_size();
    v.erase(v.begin() + 0,v.begin() + 2);
    std::vector<int>expected = {300,400,500,600,700};
    std::vector<int>actual;
    for(auto x: v){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expected);
}
TEST(merge_test,UseInputIterator){
    std::vector<int>temp = {100,200,400};
    int sizeTemp = temp.size();
    mystl::Vector<int>a = {10,20,40};
    int sizeA = a.get_size();
    a.merge(temp.begin(),temp.end());
    EXPECT_EQ(a.get_size(),(sizeTemp + sizeA));
    std::vector<int>expected,actual;
    expected = {10,20,40,100,200,400,};
    for(auto x: a){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expected);
}
TEST(merge_test,UseInputIteratorRand){
    std::vector<int>temp = {500,600,700};
    std::vector<int>expected,actual;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dist(1,10000);
    Vector<int>a;
    for(int i = 0;i < 10;++i){
        int x = dist(gen);
        a.push_back(x);
        expected.push_back(x);
    }   
    for(auto x: temp){
        expected.push_back(x);
    }
    a.merge(temp);
    for(auto x: a){
        actual.push_back(x);
    }
    EXPECT_EQ(actual,expected);
}