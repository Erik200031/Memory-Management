#ifndef RM_H
#define RM_H

template <typename T>
class Rm {
public:
    Rm();
    Rm(T*);
    Rm(Rm&&)noexcept;
    Rm& operator=(Rm&&);
    T& operator*() const;
    T* operator->() const noexcept;
    T* get() const noexcept;
    T* release();
    void reset(T*);
    ~Rm();
private:
    Rm(const Rm&) = delete;
    Rm& operator=(const Rm&) = delete;
    T* ptr;
};

template <typename T>
Rm<T>::Rm() {
    ptr = nullptr;
}

template <typename T>
Rm<T>::Rm(T* pt) {
    ptr = pt;
}
template <typename T>
Rm<T>::~Rm() {
    if(ptr != nullptr){
    delete ptr;
    ptr = nullptr;
    }
    
}

template <typename T>
Rm<T>::Rm(Rm&& rhs)  noexcept : ptr(rhs.release()) {}

template <typename T>
Rm<T>& Rm<T>::operator=(Rm<T>&& rhs) {
    reset(rhs.release());
    return *this;
}

template <typename T>
T& Rm<T>::operator*() const {
    return *ptr;
}

template <typename T>
T* Rm<T>::operator->() const noexcept {
    return ptr;
}

template <typename T>
T* Rm<T>::get() const noexcept {
    return ptr;
}

template <typename T>
T* Rm<T>::release() {
    T* tmp = ptr;
    ptr = nullptr;
    return tmp;
}

template <typename T>
void Rm<T>::reset(T* p) {
    delete ptr;
    ptr = p;
}

template <typename E>
class Rm<E[]> {
public:
    Rm();
    Rm(E*);
    Rm(Rm&&)noexcept;
    Rm& operator=(Rm&&);
    E& operator*() const;
    E* operator->() const noexcept;
    E& operator[](int index) const;
    E* get() const;
    E* release();
    void reset(E*);
    ~Rm();
private:
    Rm(const Rm&) = delete;
    Rm& operator=(const Rm&) = delete;
    E* ptr;
};

template <typename E>
Rm<E[]>::Rm() {
    ptr = nullptr;
}

template <typename E>
Rm<E[]>::Rm(E* pt) {
    ptr = pt;
}

template <typename E>
Rm<E[]>::~Rm() {
    if(ptr != nullptr) {
    delete[] ptr;
    ptr = nullptr;
    }
}

template <typename E>
Rm<E[]>::Rm(Rm&& rhs) noexcept{
    this->ptr = rhs.ptr;
    rhs.ptr = nullptr;
}

template <typename E>
Rm<E[]>& Rm<E[]>::operator=(Rm<E[]>&& rhs) {
    if(this == &rhs) {
        return *this;
    }
    delete ptr;
    this->ptr = rhs.ptr;
    rhs.ptr = nullptr;
}

template <typename E>
E& Rm<E[]>::operator*() const {
    return *ptr;
}

template <typename E>
E* Rm<E[]>::operator->() const noexcept {
    return ptr;
}

template <typename E>
E& Rm<E[]>::operator[](int index) const {
    return ptr[index];
}

template <typename E>
E* Rm<E[]>::get() const {
    return ptr;
}

template <typename E>
E* Rm<E[]>::release() {
    E* tmp = ptr;
    ptr = nullptr;
    return tmp;
}

template <typename E>
void Rm<E[]>::reset(E* p) {
    delete ptr;
    ptr = p;
}

#endif //RM_H