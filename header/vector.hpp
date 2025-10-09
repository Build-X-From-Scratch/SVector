#ifndef __VECTOR
#define __VECTOR
#include <cstddef>
#include <iterator>
#include <memory>
#include <iostream>
#include <initializer_list>
#include <stdexcept>
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
        void create_element(std::size_t pos,const T& value){
            element_traits::construct(alloc,std::addressof(arr[pos]),value);    
        }   
        void destroy(std::size_t pos){
            element_traits::destroy(alloc,std::addressof(arr[pos]));
        }
    public: 
        friend class Iterator;
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
        ~Vector(){
            free_storage();
        }
    private:
        class Iterator{
            private:
                T* ptr;
                Vector& vector_ref;
            public:
                Iterator(Vector& outer): vector_ref(outer){}
            public: 
                //iterator traits
                using iterator_category = std::random_access_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;
                friend class Vector;
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
                reference operator[](std::size_t pos){
                    if (pos >= vector_ref.size) {
                        throw std::out_of_range("Index out of range");
                    }
                    return vector_ref.arr[pos];
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
        int get_size(){
            return this->size;
        }
        int get_capacity(){
            return this->capacity;
        }
        bool ensure_capacity(){
            if(size + 1 <= capacity){
                return true;
            }
            return false;
        }
        T& at(std::size_t pos){
            if(pos >= size){
                throw std::out_of_range("behavior is undefined"); //refactor disni
            }
            return arr[pos];
        }
        T& back()const noexcept{
            return arr[size - 1];
        }
        T& front()const noexcept{
            return arr[0];
        }
        const T& at(std::size_t pos)const{
            if(pos >= size){
                throw std::out_of_range("behavior is undefined"); //refactor disni
            }
            return arr[pos];
        }
    public:
        void push_front(const T& value){
            if(ensure_capacity()){
                create_element(size, value);
                for(int i = size;i > 0;i--){
                    arr[i] = arr[i - 1];
                }
                size++;
                arr[0] = value;
            }else{
                grow();
                create_element(size, value);
                for(int i = size;i > 0;i--){
                    arr[i] = arr[i - 1];
                }
                size++;
                arr[0] = value;
            }
            create_element(0, value);
            size++;
        }
        void push_back(const T& value){
            if(size == capacity){
                grow();
            }
            create_element(size, value);
            size++;
        }
        void pop_back(){
            if(size == 0){
                throw std::runtime_error("container is empty");
            }
            destroy(size - 1);
            size--;
        }
        void pop_front(){
            if(size == 0){
                //throw
            }
            for(int i = 1;i < size;i++){
                arr[i - 1] = arr[i];
            }
            destroy(arr[size -1]);
            size--;
        }
    public:
        
    private:
        void grow(){
            T* temp = element_traits::allocate(capacity * 2);
            capacity *= 2;
            for(int i = 0;i < capacity;i++){
                create_element(i, arr[i]);
            }
            free_storage();
            arr = temp;
        }
    public: 
        void clear(){
            for(int i = 0;i < size;i++){ 
                element_traits::destroy(alloc,std::addressof(arr[i]));  
            }
            size = 0;
        }
    private:
        void free_storage(){
            for(int i = 0;i < size;i++){ 
                element_traits::destroy(alloc,std::addressof(arr[i]));  
            }
            element_traits::deallocate(alloc,arr,capacity);
            size = 0;      
        }
    public:
        void print()const noexcept{
            for(int i = 0;i < size;i++){
                std::cout << arr[i] << std::endl;
            }
        }
};
#endif