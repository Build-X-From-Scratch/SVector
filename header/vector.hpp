#ifndef __VECTOR
#define __VECTOR
#include <cstddef>
#include <iterator>
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
    private:
        T create_element(std::size_t pos,const T& value){
            return element_traits::construct(alloc,std::addressof(arr[pos]),value);    
        }   
        void destroy(std::size_t pos){
            element_traits::destroy(alloc,std::addressof(arr[pos]));
        }
    public: 
        Vector(){
            this->size = 0;
            this->capacity = 1;
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
                create_element(it, *arr);
            }
        }
    private:
        class Iterator{
            private:
                T* ptr;
            public: 
                //iterator traits
                using iterator_category = std::random_access_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;
            public: 
                Iterator(T* p = nullptr):ptr(p){}

                //deference 
                T& operator*()const{
                    return *ptr;
                }
                Iterator& operator++(){
                    ++ptr;
                    return *this;
                }
                Iterator operator++(int){
                    Iterator temp = *this;
                    ++ptr;
                    return temp;
                }
                bool operator==(const Iterator& others){
                    return ptr == others.ptr;
                }
                bool operator!=(const Iterator& others){
                    return ptr != others.ptr;
                }
        };
    public: 
        Iterator begin()const{
            return arr;
        }
        Iterator cbegin()const noexcept{
            return arr;
        }
        Iterator end()const{
            return (arr + size);
        }
        Iterator cend()const noexcept{
            return (arr + size);
        }
        Iterator rbegin()const{
            return (arr + size);
        }
        Iterator rend()const{
            return arr;
        }
        Iterator crend()const noexcept{
            return arr;
        }
        Iterator crbegin()const noexcept{
            return (arr + size);
        }
    public: //getter

    public: 
        void clear(){
            for(int i = 0;i < size;i++){ 
                element_traits::destroy(alloc,std::addressof(arr));  
            }
            element_traits::deallocate(alloc,capacity);
        }
};
#endif