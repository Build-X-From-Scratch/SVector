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
#include <limits>
#include <memory>
#include <iostream>
#include <initializer_list>
#include <ostream>
#include <concepts>
#include <ranges>
#include <stdexcept>
#include <sys/types.h>
template <typename It>
concept my_input_iterator = requires(It it) {
    *it;    // Bisa di-dereference
    ++it;   // Bisa pre-increment
    it++;   // Bisa post-increment
};
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
            this->capacity = array.size() > 0 ? array.size() : 1;
            this->arr = element_traits::allocate(alloc,capacity);
            int i = 0;
            for(const T& x: array){
                element_traits::construct(alloc,std::addressof(arr[i]),x);
                i++;
            }
        }
        // ranges constructor use Vector<int>(v->this container);
        template <std::ranges::input_range R>
        Vector(R&& r){
            //declare and initialization cap 2 * ranges size
            capacity = r.size() * 2;
            // use size on ranges
            size = r.size();
            element_traits::allocate(alloc,capacity);
            // construct element
            int i = 0;
            for(auto it = r.begin();it != r.end();it++,i++){
                element_traits::construct(alloc,std::addressof(arr[i]),*it);
            }
        }
        // // ranges
        template<typename It>
        requires my_input_iterator<It>
        Vector(It first,It last){
            if(first == last){
                return;
            }
            auto n = std::distance(first,last);
            capacity = n * 2;
            size = n;
            arr = element_traits::allocate(alloc,capacity);
            int i = 0;
            for(auto it = first;it != last;++it,i++){
                element_traits::construct(alloc,std::addressof(arr[i]),*it);
            }
        }
        //copy coppy assignment
        Vector operator==(const Vector& others){
            if(this == &others){
                return *this;
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
        Vector(const Vector& others){
            size = others.size;
            capacity = others.capacity;
            arr = element_traits::allocate(alloc,capacity);
            for(int i = 0;i < others.size;i++){
                element_traits::construct(alloc,std::addressof(arr[i]),others.arr[i]);
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
                friend class Vector;
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
                Iterator operator+(difference_type i)const{
                    return Iterator(ptr + i);
                }
                difference_type operator-(const Iterator& others)const{
                    return ptr - others.ptr;
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
    private:
        using const_iterator    = const Iterator;
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
        std::size_t max_size()const noexcept{
            return std::numeric_limits<T>::max() / sizeof(T);
        }
    private:
        bool is_full()const noexcept{
            if(size == max_size()){
                return true;
            }
            return false;
        }
    public:
        void push_front(const T& value){
            if(is_full()){
                throw std::overflow_error("max capacity container reached");
            }
            if(is_empty()){
                create_element(0,value);
                size++;
                return;
            }
            if(size == capacity){
                grow();
            }
            for(int i = size;i > 0;i--){
                arr[i] = arr[i - 1];
            }
            create_element(0, value);
            size++;
        }
        void push_front(const T&& value){
            if(is_full()){
                throw std::overflow_error("max capacity container reached");
            }
            if(is_empty()){
                create_element(0,value);
                size++;
                return;
            }
            if(size == capacity){
                grow();
            }
            for(int i = size;i > 0;i--){
                arr[i] = arr[i - 1];
            }
            create_element(0, value);
            size++;
        }     
        void push_back(const T& value){
            if(is_full()){
                throw std::overflow_error("max capacity container reached");
            }
            if(size == capacity){
                grow();
            }
            create_element(size, value);
            size++;
        }
        void push_back(const T&& value){
            if(is_full()){
                throw std::overflow_error("max capacity container reached");
            }
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
        /**
        * @brief insert,adalah salah satu method dalam dynamic array,yang digunakan untuk insert
        * value ke container dengan beberapa kriteria berdasarkan parameter
        */
        Iterator insert(const_iterator pos,const T& val){
            int index = pos - begin();
            if(is_empty()) {
                push_back(val);
                return Iterator(arr + index);
            }
            if (size + 1 > capacity) {
                std::size_t offset = index;
                grow();
                index = offset; // karena grow() bisa realokasi dan ubah arr
            }
            for (std::size_t i = size; i > index; --i) {
                arr[i] = std::move(arr[i - 1]); // pindahkan elemen
            }
            // Buat elemen baru di posisi yang kosong
            element_traits::construct(alloc,arr + index,val);
            ++size;
            return Iterator(arr + index);
        }
        Iterator insert(const_iterator pos,const T&& val){
            int index = pos - begin();
            if(is_empty()) {
                    push_back(val);
                    return Iterator(arr + index);
                }
                if (size + 1 > capacity) {
                    std::size_t offset = index;
                    grow();
                    index = offset; // karena grow() bisa realokasi dan ubah arr
                }
                for (std::size_t i = size; i > index; --i) {
                    arr[i] = std::move(arr[i - 1]); // pindahkan elemen
                }
                // Buat elemen baru di posisi yang kosong
                element_traits::construct(alloc,arr + index,val);
                ++size;
                return Iterator(arr + index);
        }
        Iterator insert(const_iterator pos,std::size_t n,const T& val){
            if(is_empty()){
                for(std::size_t i = 0;i < n;i++){
                    element_traits::construct(alloc,std::addressof(arr[i]),val);
                    size++;
                }
                return begin();
            }
            if(size + n >= capacity){
                grow(n);
            }
            ssize_t index = pos - begin();
            // geser
            for(ssize_t i = size - 1;i >= index;--i){
                arr[i + n] = arr[i];
            }
            // insert element
            for(ssize_t i = 0;i < ssize_t(n);i++){
                element_traits::construct(alloc,std::addressof(arr[pos + i]),val);
            }
            size += n;
            return Iterator(arr + index);
        }
        Iterator insert(const_iterator pos,std::size_t n,const T&& val){
            if(is_empty()){
                for(std::size_t i = 0;i < n;i++){
                    element_traits::construct(alloc,arr + i,val);
                    size++;
                }
                return begin();
            }
            ssize_t end = pos - begin();
            if(size + n >= capacity){
                grow(n);
            }
            for(ssize_t i = size - 1;i >= end;--i){
                arr[i + n] = arr[i];
            }
            for(ssize_t i = 0;i < std::size_t(n);i++){
                element_traits::construct(alloc,std::addressof(arr[end + i]),val);
            }
            size += n;
            return Iterator(arr + end);
        }
        Iterator insert(const_iterator pos,std::initializer_list<T>ilist){
            ssize_t offset = pos - begin();
            if(size + ilist.size() >= capacity){
                grow(ilist.size() * 2);
            }
            ssize_t end = offset;
            if(is_empty()){
                int i = 0;
                for(auto it = ilist.begin();it != ilist.end();i++,it++){
                    element_traits::construct(alloc,std::addressof(arr[i]),*it);
                    size++;
                }
                return begin();
            }
            std::size_t n = ilist.size();
            // geser element ke kanan
            for(ssize_t i = size  - 1;i >= end;i--){
                arr[i + n] = arr[i]; 
            }
            // insert element
            int i = 0;
            for(auto it = ilist.begin();it != ilist.end();i++,++it){
                element_traits::construct(alloc,std::addressof(arr[end + i]),*it);
            }
            size += n;
            return Iterator(arr + end);
        }  
        template <typename It>
        requires my_input_iterator<It>
        Iterator insert(const_iterator pos,It first,It last){
            int index = pos - begin();
            if(first == last){
                return (arr + index);
            }
            if(is_empty()){
                int i = 0;
                for(auto it = first;it != last;++it,i++){
                    element_traits::construct(alloc,arr + i,*it);
                    size++;
                }
                return begin();
            }
            auto n = std::distance(first,last);
            if(size + n >= capacity){
                grow(n);
            }
            //pindahkan objek
            for(decltype(index) i = size - 1;i > 0;i--){
                arr[i + n] = arr[i];
            }
            for(decltype(n) i = 0;i < n;i++,++first){
                create_element(i + index,*first);
            }
            size += n;
            return Iterator(arr + index);
        } 
    public:
        /**
        * @brief erase adalah method untuk menghapus element tertentu berdasarkan iterator pos
        * didalam array dinamis.Ide utama untuk melakukan ini adalah geser ke kanan element
        * yang akan dihapus,lalu destroy dan deallocate
        * @details pada erase mengembalikan dimana posisi iterator dihapus
        * misal return Iterator(arr + pos) jika bukan diakhir element,jika diakhir maka
        * retutn end();
        *
        */
        Iterator erase(Iterator pos){
            if(is_empty()){
                throw std::underflow_error("container is empty");
            }
            if(pos == end()){
                return end();
            }
            // destory and deallocate element
            ssize_t index = pos - begin();
            for(ssize_t i = index;i < size - 1;i++){
                arr[i] = arr[i + 1];
            }
            // simulasi erase pos 1
            // 1 2 3 4 5
            // 1 3 4 5
            // destroy
            destroy(size - 1);
            size--;
            if(index <= size){
                return end();
            }
            return Iterator(arr + index);
        }
        Iterator erase(Iterator first,Iterator last){
            if(first == last){ //end
                return first;
            }
            if(is_empty()){
                throw std::underflow_error("container is empty");
            }
            // case last_index === end()
            auto n = std::distance(first,last);
            ssize_t first_index = first - begin();
            ssize_t last_index = last - begin();
            if(n == size){
                // destroy
                for(ssize_t i = 0;i < size;i++){
                    element_traits::destroy(alloc,std::addressof(arr[i]));
                }
                size = 0;
                return end();
            }
            // geser
            for(ssize_t i = last_index;i < size;i++){
                arr[i - n] = arr[i];
            }
            // destroy
            for(ssize_t i = size - n;i < size;i++){
                element_traits::destroy(alloc,std::addressof(arr[i]));
            }
            size -= n;
            return Iterator(arr + first_index);
        }
    public:
        void swap(Vector& others)noexcept{
            // swap cap
            std::size_t temp_cap = capacity;
            capacity = others.capacity;
            others.capacity = temp_cap;
            // swap size
            std::size_t temp_size = size;
            size = others.size;
            others.size = temp_size;
            // swap container
            // allocate temp   
            T* temp_container = arr;
            arr = others.arr;
            others.arr = temp_container;
        }
        void swap(Vector&& others)noexcept{
            // swap cap
            std::size_t temp_cap = capacity;
            capacity = others.capacity;
            others.capacity = temp_cap;
            // swap size
            std::size_t temp_size = size;
            size = others.size;
            others.size = temp_size;
            // swap container
            // allocate temp   
            T* temp_container = arr;
            arr = others.arr;
            others.arr = temp_container;
        }
    public:
        /***
        * @brief assign adalah method pada vector yang digunakan untuk mereplace container dengan n value
        * dimana n,adalah jumlah element.assign memiliki 3 overload function
        * 1.void assign(std::size_t count,const T& value)
        * 2.template <class InputIt>
        * void asssign(InputIt first,InputIt last)
        * 3.void assign(std::initializer list)
        */
        void assign(std::size_t count,const T& value){
            if(count >= capacity){
                grow();
            }
            for(int i = 0;i < count;i++){
                arr[i] = value;
            }
            if(count < size){
                for(ssize_t i = count;i < size;i++){
                    element_traits::destroy(alloc,arr + i);
                }
            }
            size = count;
        }
        template <typename It>
        requires my_input_iterator<It>
        void assign(It first,It last){
            if(first == last){
                size = 0;
                return;
            }
            auto n = std::distance(first,last);
            if(n >= capacity){
                grow();
            }
            std::copy(first,last,begin(),arr);
            if(n < size){
                for(ssize_t i = n;i < size;i++){
                    element_traits::destroy(alloc,std::addressof(arr[i]));
                }
            }
            size = n;
        }
        void assign(std::initializer_list<T>l){
            if(l.begin() == l.end()){
                size = 0;
                return;
            }
            auto n = std::distance(l.begin(),l.end());
            if(n < capacity){
                grow();
            }
            std::copy(l.begin(),l.end(),arr);
            if(n < size){
                for(ssize_t i = n;i < size;i++){
                    element_traits::destroy(alloc,std::addressof(arr[i]));
                }
                //pos1,pos2
            }
            size = n;
        }
    // public:
        // template<std::ranges::input_range R>
        // void assign_range(R&& range){
        //     auto n = range.size();
        //     if(n > size){
        //         grow();
        //     }
        // }
    private:
        void grow(){
            grow(capacity * 2);
            //
        }
        void grow(std::size_t min_cap){
            std::size_t new_capacity = capacity *  2;
            if(new_capacity < min_cap){
                new_capacity = min_cap;
            }
            std::size_t old_cap = capacity;
            //allocate temp
            T* temp = element_traits::allocate(alloc,new_capacity);
            if(arr != nullptr){
                for(std::size_t i = 0;i < size;i++){
                    element_traits::construct(alloc,std::addressof(temp[i]),std::move(arr[i]));
                }
                for(size_t i = 0;i < size;i++){
                    element_traits::destroy(alloc,std::addressof(arr[i]));
                }
                element_traits::deallocate(alloc,arr,old_cap);
            }
            arr = temp;
            //update cap
            capacity = new_capacity;
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
        /**
        * @brief shrink adalah method pada vector yang digunakan untuk memangkas memory aloccation
        * yang sia-sia biasanya dipakai saat jumlah element saaat ini setengah dari cap,ketika shrink
        * dijalankan maka capacity akan sama dengan size.
        */
        void shrink(){
            std::size_t new_capacity = capacity / 2;
            std::size_t old_cap = capacity;
            T temp = element_traits::allocate(alloc,new_capacity);
            for(int i = 0;i < capacity;i++){
                element_traits::construct(alloc,std::addressof(temp[i]),std::move(arr[i]));
            }
            for(size_t i = 0;i < size;i++){
                element_traits::destroy(alloc,std::addressof(arr[i]));
            }
            element_traits::deallocate(alloc,arr,old_cap);
            arr = temp;
            capacity = new_capacity;
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