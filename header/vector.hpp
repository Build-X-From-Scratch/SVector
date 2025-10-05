#ifndef __VECTOR
#define __VECTOR
#include <cstddef>
#include <memory>
#include <initializer_list>
template <typename T,typename Allocator = std::allocator<T>>
class Vector{
    private:
        std::size_t capacity;
        std::size_t size;
        T* arr;
    private://abstraksi untuk helper allocator
        using element_traits = std::allocator_traits<Allocator>;
        Allocator alloc;
    public: 
        Vector(){
            this->size = 0;
            this->capacity = 0;
            this->arr = element_traits::allocate(alloc,capacity);
        }
        Vector(std::size_t capacity){
            this->capacity = capacity;
            this->size = 0;
            this->arr = element_traits::allocate(alloc,capacity);
        }
        Vector(std::initializer_list<T>array){
            this->size = array.size();
            this->capacity = array.size();
            this->arr = element_traits::allocate(alloc,capacity);
            for(auto it = array.begin();it != array.end();it++){
                arr[it] = array[it];
            }
        }
    // private:
    //     class Iterator{

    //     };
};
#endif