/*
MIT License

Copyright (c) 2025 Build X  From  Scratch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef __VECTOR
#define __VECTOR
#include <cstddef>
#include <iterator>
#include <memory>
#include <iostream>
#include <initializer_list>
#include <ostream>
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
        template <typename U>
        friend std::ostream& operator<<(std::ostream& os,const Vector<U>& others);
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
            this->capacity = array.size() * 2; //doubling
            this->arr = element_traits::allocate(alloc,capacity);
            int i = 0;
            for(const T& x: array){
                element_traits::construct(alloc,std::addressof(arr[i]),x);
                i++;
            }
        }
        //copy constructor
        Vector operator==(const Vector& others){
            if(this == &others){//self copy
                return;
            }
            size = others.size;
            capacity = others.capacity;
            arr = element_traits::allocate(alloc,capacity);
            int i = 0;
            for(const T& x: others.arr){
                element_traits::construct(alloc,std::addressof(arr[i]),x);
                i++;
            }
        }
        ~Vector(){
            free_storage();
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
        T& operator[](std::size_t pos){
            if(pos > size){
                throw std::out_of_range("Index out of range");
            }
            return arr[pos];
        }
         const T& operator[](std::size_t pos)const{
            if(pos > size){
                throw std::out_of_range("Index out of range");
            }
            return arr[pos]; 
        }
    public: //getter
        int get_size(){
            return this->size;
        }
        int get_capacity(){
            return this->capacity;
        }
        bool is_empty(){
            if(size == 0){
                return true;
            }
            return false;
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
            if(is_empty()){
                create_element(0,value);
                size++;
                return;
            }
            if(ensure_capacity()){
                grow();
            }
            for(int i = size;i > 0;i--){
                arr[i] = arr[i - 1];
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
        void insert(std::size_t pos,const T& val){
            if (is_empty()) {
                    push_back(val);
                    return;
                }

                if (size + 1 > capacity) {
                    std::size_t offset = pos;
                    grow();
                    pos = offset; // karena grow() bisa realokasi dan ubah arr
                }

                // Geser elemen ke kanan, gunakan placement new di slot mentah
                new (&arr[size]) T(std::move(arr[size - 1])); // buat elemen baru di slot akhir

                for (std::size_t i = size - 1; i > pos; --i) {
                    arr[i] = std::move(arr[i - 1]); // pindahkan elemen
                }

                // Buat elemen baru di posisi yang kosong
                arr[pos] = val;

                ++size;

        }
        void insert(std::size_t pos,std::size_t n,const T& val){
            if(size + n >= capacity){
                grow();
            }
            for(int i = size - 1;i >= pos;--i){
                arr[i + n] = arr[i];
            }
            for(size_t i = 0;i < std::size_t(n);i++){
                arr[pos + i] = val;
            }
            size += n;
        }
    private:
        void grow(){
            // update cap
            std::size_t new_capacity = capacity *  2;
            std::size_t old_cap = capacity;
            //allocate temp
            T* temp = element_traits::allocate(alloc,new_capacity);
            for(std::size_t i = 0;i < size;i++){
                element_traits::construct(alloc,std::addressof(temp[i]),std::move(arr[i]));
            }
            for(size_t i = 0;i < size;i++){
                element_traits::destroy(alloc,std::addressof(arr[i]));
            }
            element_traits::deallocate(alloc,arr,old_cap);
            arr = temp;
            //update cap
            capacity = new_capacity;
            //
        }
        void resize(std::size_t n){
            resize(n,T{});
        }
        void reserve(std::size_t n){
            //alokasi capacity baru
            capacity = n;
            element_traits::allocate(alloc,capacity);
        }
        void resize(std::size_t n,const T& val){
            if(n == size){
                return;
            }else if(n < size){
                for(size_t i = size;i > n;i--){
                    destroy(i);
                }
                size = n;
                return;
            }else if(n > size && n < capacity){
                for(size_t i = size ;i < n;i++){
                    create_element(val);
                }
                size = n;
            }   
            if(n > capacity){
                reserve(recomended_cap(n));
                for(int i = size;i < n;i++){
                    create_element(1,val);
                }
                size = n;
            }

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
        std::size_t recomended_cap(std::size_t need)const{
            std::size_t grow = capacity ? capacity * 2 : 1;
            return grow < need ? need : grow;
        }
    public:
        void print()const noexcept{
            for(int i = 0;i < size;i++){
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }
};
template <typename U>
std::ostream& operator<<(std::ostream& os,const Vector<U>& others){
    os << "[ ";
    for(std::size_t i = 0;i < others.size;i++){
        os << others.arr[i];
    }
    os << "]";
    return os;
}
#endif