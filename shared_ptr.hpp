#ifndef HEADER_HPP
#define HEADER_HPP
struct ctrl_block{
    int counter;
};

template <typename T>
class sh_ptr{
    private:
        T* data;
        ctrl_block* ctrl;

    public:
        sh_ptr(T* d = nullptr) noexcept : data{d}, ctrl{d ? new ctrl_block{1} : nullptr} {}
        sh_ptr(const sh_ptr<T>& ptr )noexcept ;
        sh_ptr& operator=(const sh_ptr<T>& ptr)noexcept;
        sh_ptr(sh_ptr<T>&& ptr)noexcept;
        sh_ptr& operator=(sh_ptr<T>&& ptr)noexcept;
    public:
        void swap(sh_ptr<T>& r)noexcept;
        T* get_d()const noexcept;
        ctrl_block* get_c()const noexcept;
        void reset();
    public:
        T& operator*()const noexcept;
        T* operator->()const noexcept;
        long use_count()const noexcept;
        bool unique()const noexcept;

        explicit operator bool()const noexcept{ return get_d() != nullptr; }

     public:
        ~sh_ptr(){
           reset();
        }   
};

template <typename T>
sh_ptr<T>::sh_ptr(const sh_ptr<T>& ptr )noexcept:data{ptr.data}, ctrl{ptr.ctrl} { if(ctrl)++ctrl->counter; }

template <typename T>
sh_ptr<T>& sh_ptr<T>::operator=(const sh_ptr<T>&  ptr)noexcept {
    this->reset();
    data = ptr.data;
    ctrl = ptr.ctrl;
    ++ctrl->counter;
    return *this;
}
template <typename T>
sh_ptr<T>::sh_ptr(sh_ptr<T>&& ptr)noexcept:data{ptr.data}, ctrl{ptr.ctrl}{
    ptr.data = nullptr;
    ptr.ctrl = nullptr;
} 
template <typename T>

sh_ptr<T>& sh_ptr<T>::operator=(sh_ptr<T>&& ptr)noexcept {
    this->reset();
    data = ptr.data;
    ctrl = ptr.ctrl;
    ptr.data = nullptr;
    ptr.ctrl = nullptr;
    return *this;

}

template <typename T>
void sh_ptr<T>::swap(sh_ptr<T>& r)noexcept {
    
    std::swap(data, r.data);
    std::swap(ctrl, r.ctrl);

}
template <typename T>
T* sh_ptr<T>::get_d()const noexcept {
    return this->data;
}
template <typename T>
ctrl_block* sh_ptr<T>::get_c()const noexcept {
    return this->ctrl;
}
template <typename T>
void sh_ptr<T>::reset() {
    if(this->ctrl){
        --ctrl->counter;
        if(--ctrl->counter == 0 ){
            delete data;
            delete ctrl;
        }    
    }
    data = nullptr;
    ctrl = nullptr;
    
}
template <typename T>
T& sh_ptr<T>::operator*()const noexcept{
    return *get_d();
}
template <typename T>
T* sh_ptr<T>::operator->()const noexcept{
    return get_d();
}
template <typename T>
long sh_ptr<T>::use_count()const noexcept {
    return ctrl ? ctrl->counter : 0;
}
template <typename T>
bool sh_ptr<T>::unique()const noexcept {
    return use_count() == 1;
}
template <typename T>
std::ostream& operator<<(std::ostream& ost, const sh_ptr<T>& ptr){
    ost<<ptr.get_d();
    return ost;
}
template <typename T>
bool operator==(const sh_ptr<T>& lhs, const sh_ptr<T>& rhs){
    return lhs.data == rhs.data;
}
template <typename T>
bool operator!=(const sh_ptr<T>& lhs, const sh_ptr<T>& rhs){
    return lhs.data != rhs.data;
}
template <typename T>
bool operator<(const sh_ptr<T>& lhs, const sh_ptr<T>& rhs){
    return lhs.data < rhs.data;
}
template <typename T>
bool operator<=(const sh_ptr<T>& lhs, const sh_ptr<T>& rhs){
    return lhs.data <= rhs.data;
}
template <typename T>
bool operator>(const sh_ptr<T>& lhs, const sh_ptr<T>& rhs){
    return lhs.data > rhs.data;
}
template <typename T>
bool operator>=(const sh_ptr<T>& lhs, const sh_ptr<T>& rhs){
    return lhs.data >= rhs.data;
}


#endif