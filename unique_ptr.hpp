#ifndef HEADER_HPP
#define HEADER_HPP
#include <iostream>
#include <ostream>


template <typename T>
class u_ptr {
    private:
        T* data;
    public:
        explicit u_ptr(T* d = nullptr)noexcept:data{d} {}
        u_ptr(const u_ptr<T>& d)noexcept = delete;
        u_ptr& operator=(const u_ptr<T>& d)noexcept = delete;
        u_ptr(u_ptr<T>&& d)noexcept; 
        u_ptr& operator=(u_ptr<T>&& d )noexcept;

    public:
        ~u_ptr();    
    public:
        T* release()noexcept;   
        void reset(); 
        T* get()const noexcept;
        explicit operator bool()const noexcept { return get() != nullptr; }
        void swap(u_ptr<T>& oth)noexcept;
        T& operator*()const noexcept;
        T* operator->()const noexcept;
        void reset(T* p);
        
       
};



template <typename T>
u_ptr<T>::u_ptr(u_ptr<T>&& d)noexcept {
            this->data = d.data;
            d.data = nullptr;
} 
template <typename T>
u_ptr<T>& u_ptr<T>::operator=(u_ptr<T>&& d ) noexcept {
            if(this != &d){
            delete data; 
            this->data = d.data;
            d.data = nullptr;
            }
            return *this;
}
template <typename T>
u_ptr<T>::~u_ptr(){
    reset();
}
template <typename T>
T* u_ptr<T>::release()noexcept {
    T* oth = this->data;
    this->data = nullptr;
    return oth;

}
template <typename T>
void u_ptr<T>::reset(){
    delete this->data; 
    this->data = nullptr;

}
template <typename T>
void u_ptr<T>::swap(u_ptr<T>& oth)noexcept {
    std::swap(this->data, oth.data);
}
template <typename T>
T* u_ptr<T>::get()const noexcept {
    return this->data;
}

//template <typename T>
//T& u_ptr<T>::operator*()const noexcept {
 //return *(this->get());

///}
template <typename T>
T* u_ptr<T>::operator->()const noexcept {
    return this->get();
}   
template <typename T>
bool operator==(const u_ptr<T>& lhs, const u_ptr<T>& rhs ){
    return lhs.get() == rhs.get();    
}
template <typename T>
bool operator!=(const u_ptr<T>& lhs, const u_ptr<T>& rhs){
    return lhs.get() != rhs.get();
}

template <typename T>
bool operator<(const u_ptr<T>& lhs, const u_ptr<T>& rhs){
    return lhs.get() < rhs.get();
}
template <typename T>
bool operator<=(const u_ptr<T>& lhs, const u_ptr<T>& rhs){
    return lhs.get() <= rhs.get();
}
template <typename T>
bool operator>(const u_ptr<T>& lhs, const u_ptr<T>& rhs){
    return lhs.get() > rhs.get();
}
template <typename T>
bool operator>=(const u_ptr<T>& lhs, const u_ptr<T>& rhs){
    return lhs.get() >= rhs.get();
}

template <typename T>
std::ostream& operator<<(std::ostream& ost, const u_ptr<T>& ptr ){
    ost<<ptr.get();
    return ost;
}

template <typename T>
void u_ptr<T>::reset(T* p){
    delete this->data;
    this->data = p;
}

#endif